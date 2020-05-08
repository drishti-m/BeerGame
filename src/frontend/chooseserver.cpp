#include "chooseserver.h"
#include "ui_chooseserver.h"
#include <QMessageBox>
#include <QRegExp>
#include <QObject>

#define G_FACTORY 0
#define G_DISTRIBUTOR 1
#define G_WHOLESALER 2
#define G_RETAILER 3
#define G_CUSTOMER 4
#define G_BREWERY 5

chooseServer::chooseServer(QWidget *parent, Game *game) : QDialog(parent),
                                                          ui(new Ui::chooseServer), my_game(game)
{
    ui->setupUi(this);
    ui->ip_address_text->setText("127.0.0.1");
    ui->port_text->setText("1234");
    ui->stop_server->setDisabled(true);
    tcpServer.setMaxPendingConnections(4);
}

chooseServer::~chooseServer()
{
    delete ui;
}

bool chooseServer::check_unique_player_role(QByteArray b)
{
    if (b == "Retailer chosen")
    {
        if (unique_retailer_id == 0)
        {
            unique_retailer_id = 1;
            qDebug() << "retailer";
            if ((tcpServerConnection) && (tcpServerConnection->isOpen()))
            {
                tcpServerConnection->write("You get retailer");
                role_socket_map["RETAILER"] = tcpServerConnection;
            }
        }
        else
        {
            if ((tcpServerConnection) && (tcpServerConnection->isOpen()))
                tcpServerConnection->write("Role not available");
        }
    }
    else if (b == "Wholesaler chosen")
    {
        if (unique_wholesaler_id == 0)
        {
            unique_wholesaler_id = 1;

            if (tcpServerConnection->isOpen())
            {
                tcpServerConnection->write("You get wholesaler");
                role_socket_map["WHOLESALER"] = tcpServerConnection;
            }
        }
        else
        {
            tcpServerConnection->write("Role not available");
        }
    }
    else if (b == "Distributor chosen")
    {
        if (unique_distributor_id == 0)
        {
            unique_distributor_id = 1;
            tcpServerConnection->write("You get distributor");
            role_socket_map["DISTRIBUTOR"] = tcpServerConnection;
        }
        else
        {
            tcpServerConnection->write("Role not available");
        }
    }
    else if (b == "Factory chosen")
    {
        if (unique_factory_id == 0)
        {
            unique_factory_id = 1;
            tcpServerConnection->write("You get factory");
            role_socket_map["FACTORY"] = tcpServerConnection;
        }
        else
        {
            tcpServerConnection->write("Role not available");
        }
    }
    else
    {
        return false;
    }
    // start the game only iff all players are (successfully) connected
    if ((unique_factory_id == 1) && (unique_retailer_id == 1) && (unique_wholesaler_id == 1) && (unique_distributor_id == 1))
    {
        for (auto client : tcpClients)
        {
            if (client->isOpen())
            {
                int inventory = my_game->getStartingInventory();
                QString inv_s = QString::number(inventory);
                QString inv_details = " STARTING_INVENTORY: " + inv_s;
                client->write("Game start = true");
                client->write(inv_details.toLocal8Bit());
            }
        }
        game_ready_to_start = true;
        create_players_game();
    }
    return true;
}

QStringList chooseServer::parse_key_value(QString parsed)
{
    QStringList json_list = parsed.split(QRegExp(" "));
    for (auto our_string : json_list)
    {
        qDebug() << our_string;
    }
    return json_list;
}

bool chooseServer::update_order_info(QStringList s)
{
    QString role = s[0];
    QString week_s = s[2];
    QString order_s = s[4];
    int current_week = week_s.toInt(nullptr, 10);
    int order = order_s.toInt(nullptr, 10);

    if (role == "RETAILER")
    {
        retailer_order = true;
        role_outgoing_order_map[RETAILER] = order;
    }
    else if (role == "WHOLESALER")
    {
        wholesaler_order = true;
        role_outgoing_order_map[WHOLESALER] = order;
    }
    else if (role == "DISTRIBUTOR")
    {
        distributor_order = true;
        role_outgoing_order_map[DISTRIBUTOR] = order;
    }
    else if (role == "FACTORY")
    {
        factory_order = true;
        role_outgoing_order_map[FACTORY] = order;
    }

    if ((retailer_order == true) && (wholesaler_order == true) && (distributor_order == true) && (factory_order == true))
    {
        qDebug() << "all orders received: Week: " << week_s;
        all_outgoing_orders_map[current_week] = role_outgoing_order_map;
        qDebug() << "retailer: " << role_outgoing_order_map[RETAILER];
        qDebug() << "wholesaler: " << role_outgoing_order_map[WHOLESALER];
        qDebug() << "distributor: " << role_outgoing_order_map[DISTRIBUTOR];
        qDebug() << "factory: " << role_outgoing_order_map[FACTORY];
        return true;
    }
    else
    {
        return false;
    }
}

void chooseServer::process_orders_this_week()
{
    if (my_game->getCurrentWeek() >= my_game->getWeeksToBePlayed())
    {
        for (auto client : tcpClients)
        {
            client->write("GAME OVER");
        }
    }
    else
    {
        vector<Player *> players = my_game->getPlayers();
        map<int, int> outgoing_orders_this_week = all_outgoing_orders_map[my_game->getCurrentWeek() - 1];
        for (int i = 0; i < 4; i++)
        {
            int role = i;
            int outgoing_order;
            if (role == G_FACTORY)
            {
                cout << "Proess Factory: ";
                outgoing_order = outgoing_orders_this_week[FACTORY];
                cout << outgoing_order << endl;
            }
            else if (role == G_DISTRIBUTOR)
            {
                cout << "Process Distributor: ";
                outgoing_order = outgoing_orders_this_week[DISTRIBUTOR];
                cout << outgoing_order << endl;
            }
            else if (role == G_WHOLESALER)
            {
                cout << "Process Wholesaler: ";
                outgoing_order = outgoing_orders_this_week[WHOLESALER];
                cout << outgoing_order << endl;
            }
            else if (role == G_RETAILER)
            {
                cout << "Process Retailer: ";
                outgoing_order = outgoing_orders_this_week[RETAILER];
                cout << outgoing_order << endl;
            }
            else
            {
                perror("Invalid role \n");
                cout << "Nothing process\n";
                outgoing_order = 0;
            }
            players[i]->placeOrder(outgoing_order);
        }
        my_game->executeOrdersForCurrentWeek();
        my_game->executeShipmentsForCurrentWeek();
        my_game->updatePlayerInventories();
        my_game->advanceWeek();
        int week = my_game->getCurrentWeek() - 1; //week starts from 0
        qDebug() << "server side: coming week: " << week;
        int inventory, backlog, demand, delivered, received;
        double cost;
        //convert qstring to qbyte and write in socket
        for (auto client : tcpClients)
        {
            if ((client->isOpen()) && (client != nullptr))
            {
                if (client == role_socket_map["RETAILER"])
                {
                    temp_inventory = (players[G_RETAILER]->getInventory_every_week());
                    temp_backlog = (players[G_RETAILER]->getBacklog_every_week());
                    temp_demand = (players[G_RETAILER]->getDemand_every_week());
                    temp_delivered = (players[G_RETAILER]->getDelivered_every_week());
                    temp_cost = (players[G_RETAILER]->getCost_every_week());
                    temp_received = (players[G_RETAILER]->getReceived_every_week());
                    qDebug() << "retailer data taken";
                }
                else if (client == role_socket_map["WHOLESALER"])
                {
                    temp_inventory = (players[G_WHOLESALER]->getInventory_every_week());
                    temp_backlog = (players[G_WHOLESALER]->getBacklog_every_week());
                    temp_demand = (players[G_WHOLESALER]->getDemand_every_week());
                    temp_delivered = (players[G_WHOLESALER]->getDelivered_every_week());
                    temp_cost = (players[G_WHOLESALER]->getCost_every_week());
                    temp_received = (players[G_WHOLESALER]->getReceived_every_week());
                    qDebug() << "wholesaler data taken";
                }
                else if (client == role_socket_map["DISTRIBUTOR"])
                {
                    temp_inventory = (players[G_DISTRIBUTOR]->getInventory_every_week());
                    temp_backlog = (players[G_DISTRIBUTOR]->getBacklog_every_week());
                    temp_demand = (players[G_DISTRIBUTOR]->getDemand_every_week());
                    temp_delivered = (players[G_DISTRIBUTOR]->getDelivered_every_week());
                    temp_cost = (players[G_DISTRIBUTOR]->getCost_every_week());
                    temp_received = (players[G_DISTRIBUTOR]->getReceived_every_week());
                    qDebug() << "distributor data taken";
                }
                else if (client == role_socket_map["FACTORY"])
                {
                    temp_inventory = (players[G_FACTORY]->getInventory_every_week());
                    temp_backlog = (players[G_FACTORY]->getBacklog_every_week());
                    temp_demand = (players[G_FACTORY]->getDemand_every_week());
                    temp_delivered = (players[G_FACTORY]->getDelivered_every_week());
                    temp_cost = (players[G_FACTORY]->getCost_every_week());
                    temp_received = (players[G_FACTORY]->getReceived_every_week());
                    qDebug() << "factory data taken";
                }
                else
                {
                    qDebug() << "socket address != players...exiting";
                    return;
                }
                inventory = temp_inventory[week];
                backlog = temp_backlog[week];
                demand = temp_demand[week];
                delivered = temp_delivered[week];
                cost = temp_cost[week];
                received = temp_received[week];
                qDebug() << "taken players data";
                QString week_signal = "ADVANCE WEEK: " + QString::number(week);
                client->write(week_signal.toLocal8Bit());

                week_signal = " INVENTORY: " + QString::number(inventory);
                client->write(week_signal.toLocal8Bit());
                week_signal = " BACKLOG: " + QString::number(backlog);
                client->write(week_signal.toLocal8Bit());
                week_signal = " DEMAND: " + QString::number(demand);
                client->write(week_signal.toLocal8Bit());
                week_signal = " DELIVERED: " + QString::number(delivered);
                client->write(week_signal.toLocal8Bit());
                week_signal = " COST: " + QString::number(cost);
                client->write(week_signal.toLocal8Bit());
                week_signal = " RECEIVED: " + QString::number(received);
                client->write(week_signal.toLocal8Bit());
                qDebug() << "order detail stream written";
            }
        }
        all_orders_done_for_this_week = false;
    }
}

void chooseServer::create_players_game()
{
    //Create Players and add to game
    retailer = new Player(my_game, G_RETAILER + 1);
    wholesaler = new Player(my_game, G_WHOLESALER + 1);
    distributor = new Player(my_game, G_DISTRIBUTOR + 1);
    factory = new Player(my_game, G_FACTORY + 1);

    my_game->addPlayer(factory);
    my_game->addPlayer(distributor);
    my_game->addPlayer(wholesaler);
    my_game->addPlayer(retailer);

    my_game->setCurrentWeek(1);
}

void chooseServer::on_server_connect_clicked()
{
    QString ip_addr = ui->ip_address_text->text();
    QString s_port = ui->port_text->text();
    QHostAddress addr;
    uint port_no = s_port.toUInt(Q_NULLPTR, 10);
    addr.setAddress(ip_addr);
    startListening(addr, port_no);
    //check if server port, address set up as expected
    qDebug() << "server port set up as: " << tcpServer.serverPort() << " address: " << tcpServer.serverAddress();

    ui->stop_server->setDisabled(false);
    ui->server_connect->setDisabled(true);

    connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void chooseServer::startListening(QHostAddress ip_addr, uint port_no)
{
    bytesWritten = 0;
    bytesReceived = 0;
    while (!tcpServer.isListening() && !tcpServer.listen(ip_addr, port_no))
    {
        qDebug() << "From server: Error listening..";
        return;
    }
}

void chooseServer::acceptConnection()
{
    // nextPendingConnection() to accept the pending connection as a connected QTcpSocket.
    // This function returns a pointer to a QTcpSocket
    if (no_connections < 4)
    {
        tcpServerConnection = tcpServer.nextPendingConnection();
        tcpClients.push_back(tcpServerConnection);

        connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(displayError(QAbstractSocket::SocketError)));
        connect(tcpServerConnection, SIGNAL(disconnected()), this, SLOT(disconnect()));
        connect(tcpServerConnection, SIGNAL(readyRead()),
                this, SLOT(updateServerProgress()));
        connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(displayError(QAbstractSocket::SocketError)));

        no_connections += 1;
        //qDebug() << "connected clients: " << no_connections;
        QMessageBox::information(this, "New client", "New client connection added");
    }
    else
    {
        qDebug() << "From server: not accepting more clients..";
        tcpServer.close();
    }
}

void chooseServer::updateServerProgress()
{
    for (auto client : tcpClients)
    {
        bytesReceived += (int)client->bytesAvailable();
        QByteArray b = client->readAll();
        if (!b.isEmpty())
        {
            bool role_message = check_unique_player_role(b);
            if (role_message == true)
            {
                qDebug() << "Unique role chosen";
            }
            //QMessageBox::information(this, "Msg from client", b);
            QString client_string = QString::fromStdString(b.toStdString());
            QStringList parsed_list = parse_key_value(client_string);
            if (parsed_list[1] == "week:" && parsed_list[3] == "order:")
            {
                bool temp_val = update_order_info(parsed_list);
                if (temp_val == true)
                {
                    all_orders_done_for_this_week = true;
                }
            }
            //qDebug() << "From server: Received " << client->bytesAvailable() << " bytes..";
        }
    }

    if (all_orders_done_for_this_week == true)
    {
        wholesaler_order = false;
        retailer_order = false;
        factory_order = false;
        distributor_order = false;

        //qDebug() << "Processing orders for the week";
        process_orders_this_week();
    }
}

void chooseServer::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << "From server: Network error: " << tcpServerConnection->errorString();

    for (auto client: tcpClients){
        if (client && client->isOpen())
            client->close();
    }
  //  tcpServerConnection->close();

    // Calling close() makes QTcpServer stop listening for incoming connections.
    tcpServer.close();
}

void chooseServer::disconnect()
{
    qDebug() << "From server: Client disconnected.";
    no_connections -= 1;
    //    tcpClient.disconnectFromHost();
    if (no_connections < 0)
    {
        no_connections = 0;
    }
    qDebug() << "From server: No of clients now: " << no_connections;

    if (((unique_factory_id == 1) || (unique_retailer_id == 1) || (unique_wholesaler_id == 1) || (unique_distributor_id == 1)) && (no_connections < 4))
    {
        for (auto client : tcpClients)
        {
            if ((client!= nullptr) && (client->isOpen()))
            {
                client->write("Players incomplete.");
            }
        }
        QMessageBox::information(this, "Player/s disconnected", "Closing the server. Please restart to play again.");
        // tcpServer.close();

}
       // this->close();

}

void chooseServer::on_stop_server_clicked()
{
    //can stop server connection only when it is connected
    tcpServer.close();
    QMessageBox::information(this, "Server closed", "Server connection for this app will now be closed. Please run the server application again if you wish to re-open server connection.");
    qDebug() << "From server: server closed..";
    for (auto client : tcpClients)
    {
        if ((client->isOpen()) && (client != nullptr))
        {
            qDebug() << "From server: client present.. about to disconnect";
            client->disconnectFromHost();
            client->close();
            //tcpServerConnection->close();
        }
    }
    ui->stop_server->setDisabled(true);
    no_connections = 0;
    ui->server_connect->setDisabled(true);

    this->close();
}
