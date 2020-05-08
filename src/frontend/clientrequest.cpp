#include "clientrequest.h"
#include "ui_clientrequest.h"

#include <QMessageBox>

#define ROLE_AVAILABLE 1
#define ROLE_TAKEN -1
#define STH_ELSE 0

ClientRequest::ClientRequest(QWidget *parent, Player *player) : QDialog(parent),
                                                                ui(new Ui::ClientRequest),
                                                                player(player)
{
    ui->setupUi(this);
    ui->ip_address_text->setText("127.0.0.1");
    ui->port_text->setText("1234");
}

ClientRequest::~ClientRequest()
{
    delete ui;
}

void ClientRequest::requestConnection(QHostAddress ip, uint port)
{
    qDebug() << "Requested new client";

    QTcpSocket *tcpClient = new QTcpSocket;
    tcpClient->setProxy(QNetworkProxy::NoProxy);
    tcpClient->connectToHost(ip, port);

    // nextPendingConnection() to accept the pending connection as a connected QTcpSocket.
    // This function returns a pointer to a QTcpSocket

    tcpServerConnection = tcpClient;

    //when connection successful, send to server message that it is connected
    connect(tcpServerConnection, SIGNAL(connected()),
            this, SLOT(clientSendMessageToServer()));

    //in case of any network error, show dialog box with error
    connect(tcpServerConnection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    //when client disconnected, show message to client
    connect(tcpServerConnection, SIGNAL(disconnected()), this, SLOT(disconnect()));
    connect(tcpServerConnection, SIGNAL(readyRead()), this, SLOT(displayServerMessage()));
}

void ClientRequest::clientSendMessageToServer()
{

    // called when the TCP client connected to the loopback server
    qDebug() << "From Client: connected";
    hide();

    g = new Game(1, 6, 6, 6, 6, 6, 6);

    pd = new PlayerDialog(this, *g, player);
    pd->setClient(this);
    pd->show();
    pd->move(0, 0);

    ui->client_request_connect->setDisabled(true);
}

void ClientRequest::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
    {
        QMessageBox::warning(this, "Server closed connection", "Enough clients already, or server has closed connections.");
        return;
    }
    qDebug() << "Network error: " << tcpServerConnection->errorString();
    QMessageBox::warning(this, "Server refused connection", "Network error. Check if server is listening, and try reconecting again");
}

void ClientRequest::disconnect()
{
    //QMessageBox::information(this, "Disconnected", "You have been disconnected");
    tcpServerConnection->disconnectFromHost();
    qDebug() << "From client: client has been disconnected";
    ui->client_request_connect->setDisabled(false);
}

void ClientRequest::displayServerMessage()
{
    QByteArray b = tcpServerConnection->readAll();
    qDebug() << "FINALLY: server sends: " << b;
    int check_value = check_role_available(b);
    QString server_string = QString::fromStdString(b.toStdString());
    QStringList parse_list = parse_key_value(server_string);
    if ((parse_list[0] == "Role") && (parse_list[1] == "not") && (parse_list[2] == "available"))
    {
        pd->enable_role_buttons(true);
        pd->show_messageBox_to_Player("Role not available", "Please choose another role");
    }
    if ((check_value == ROLE_AVAILABLE) || (check_value == STH_ELSE))
    {
        QString server_string = QString::fromStdString(b.toStdString());
        QStringList parsed_list = parse_key_value(server_string);
        if ((game_start == true) || ((parsed_list[0] == "Game") && (parsed_list[1] == "start") && parsed_list[3] == "true"))
        {
            if (parsed_list[4] == "STARTING_INVENTORY:")
            {
                inventory_ui = parsed_list[5];
                qDebug() << "Non starting players output: starting inventory: " << inventory_ui;
            }
            else
            {
                qDebug() << "Inventory parameter not received";
            }
            showGame();
            game_start = false;
        }

        //advance next week when signal from server
        if ((game_start == false) && (check_value == STH_ELSE))
        {
            //QString server_string= QString::fromStdString(b.toStdString());
            //QStringList parsed_list = parse_key_value(server_string);
            if (parsed_list[0] == "GAME" && parsed_list[1] == "OVER")
            {
                QMessageBox::information(this, "Game Over", "All rounds finish");
                tcpServerConnection->disconnectFromHost();
            }
            if (parsed_list[0] == "ADVANCE" && parsed_list[1] == "WEEK:")
            {
                QString week_s = parsed_list[2];
                int current_week = week_s.toInt(nullptr, 10);
                if (current_week == my_game_screen->getPlayer_week_in_game() + 1)
                {
                    qDebug() << "update values in UI";
                    qDebug() << "Before advance round, parsed: " << parsed_list;
                    advance_round(current_week, parsed_list);
                }
            }
        }
    }

    if (b == "Players incomplete.")
    {
        QMessageBox::information(this, "Player(/s) missing", "Game disrupted. Please restart the game again.");
    }
}

void ClientRequest::on_client_request_connect_clicked()
{
    QString ip_addr = ui->ip_address_text->text();
    QString s_port = ui->port_text->text();
    QHostAddress addr;
    uint port_no = s_port.toUInt(Q_NULLPTR, 10);
    addr.setAddress(ip_addr);
    requestConnection(addr, port_no);
}

QTcpSocket *ClientRequest::getTcpServerConnection() const
{
    return tcpServerConnection;
}

void ClientRequest::setTcpServerConnection(QTcpSocket *value)
{
    tcpServerConnection = value;
}

int ClientRequest::check_role_available(QByteArray b)
{
    QString server_string = QString::fromStdString(b.toStdString());
    QStringList parse_list = parse_key_value(server_string);
    if (parse_list[0] == "You" && parse_list[1] == "get")
    {
        // add parsing  "Game start = true" + " STARTING_INVENTORY: " + inv_s;, then set inventory for pd
        if ((parse_list[2] == "retailer") || (parse_list[2] == "retailerGame"))
        {
            g->setPRetailerId(1);
            player->setRole(RETAILER);
            playerRole = "RETAILER";
            pd->enable_role_buttons(false);

            if ((parse_list[2] == "retailerGame") && (parse_list[3] == "start"))
            {
                game_start = true;
                inventory_ui = parse_list[7];
                qDebug() << "Retailer starting inventory: " << inventory_ui;
            }
            else
            {
                pd->show_messageBox_to_Player("Retailer", "You get retailer. Waiting for other Players to join and start the game");
            }
        }
        else if ((parse_list[2] == "wholesaler") || (parse_list[2] == "wholesalerGame"))
        {
            g->setPWholesalerId(1);
            player->setRole(WHOLESALER);
            playerRole = "WHOLESALER";
            pd->enable_role_buttons(false);
            if ((parse_list[2] == "wholesalerGame") && (parse_list[3] == "start"))
            {
                game_start = true;
                inventory_ui = parse_list[7];
                qDebug() << "wholesaler starting inventory: " << inventory_ui;
            }
            else
            {
                pd->show_messageBox_to_Player("Wholesaler", "You get wholesaler. Waiting for other Players to join and start the game");
            }
        }
        else if ((parse_list[2] == "distributor") || (parse_list[2] == "distributorGame"))
        {
            g->setPDistributorId(1);
            player->setRole(DISTRIBUTOR);
            playerRole = "DISTRIBUTOR";
            pd->enable_role_buttons(false);
            if ((parse_list[2] == "distributorGame") && (parse_list[3] == "start"))
            {
                game_start = true;
                inventory_ui = parse_list[7];
                qDebug() << "distributor starting inventory: " << inventory_ui;
            }
            else
            {
                pd->show_messageBox_to_Player("Distributor", "You get distributor. Waiting for other Players to join and start the game");
            }
        }
        else if ((parse_list[2] == "factory") || (parse_list[2] == "factoryGame"))
        {
            g->setPFactId(1);
            player->setRole(FACTORY);
            playerRole = "FACTORY";
            pd->enable_role_buttons(false);
            if ((parse_list[2] == "factoryGame") && (parse_list[3] == "start"))
            {
                game_start = true;
                inventory_ui = parse_list[7];
                qDebug() << "factory starting inventory: " << inventory_ui;
            }
            else
            {
                pd->show_messageBox_to_Player("Factory", "You get factory.  Waiting for other Players to join and start the game");
            }
        }
        else if ((parse_list[0] == "Role") && (parse_list[1] == "not") && (parse_list[2] == "available"))
        {
            pd->enable_role_buttons(true);
            pd->show_messageBox_to_Player("Role not available", "Please choose another role");
            return ROLE_TAKEN;
        }
    }
    else
    {
        return STH_ELSE;
    }
    return ROLE_AVAILABLE;
}

void ClientRequest::showGame()
{
    int inv = inventory_ui.toInt();
    player->setInventory(inv);
    g->setStartingInventory(inv);
    my_game_screen = new GameScreen(this, g, player, this);

    my_game_screen->setWindowTitle(playerRole);

    my_game_screen->show();
    pd->hide();
    hide();
}

void ClientRequest::send_order(QString player_order, QString player_week)
{
    QString order_detail = playerRole + " week: " + player_week + " order: " + player_order;
    //convert qstring to qbyte and write in socket
    tcpServerConnection->write(order_detail.toLocal8Bit());
    qDebug() << order_detail;
}

QStringList ClientRequest::parse_key_value(QString parsed)
{
    QStringList json_list = parsed.split(QRegExp(" "));
    for (auto our_string : json_list)
    {
        qDebug() << our_string;
    }
    return json_list;
}

//TO-DO print check values here
void ClientRequest::advance_round(int current_week, QStringList parsed_list)
{
    my_game_screen->setPlayer_week_in_game(current_week);
    my_game_screen->enable_order_button();
    QString inventory_s = parsed_list[4];
    QString backlog_s = parsed_list[6];
    QString demand_s = parsed_list[8];
    QString delivered_s = parsed_list[10];
    QString cost_s(parsed_list[12]);
    QString received_s(parsed_list[14]);

    int inventory = inventory_s.toInt(nullptr, 10);
    int backlog = backlog_s.toInt(nullptr, 10);
    int demand = demand_s.toInt(nullptr, 10);
    int delivered = delivered_s.toInt(nullptr, 10);
    bool ok = false;
    double cost = cost_s.toDouble(&ok);
    int received = received_s.toInt(nullptr, 10);

    my_game_screen->update_ui_parameters(inventory, backlog, demand, delivered, cost, received);
}
