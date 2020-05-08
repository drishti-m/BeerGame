/**
 *  @file   chooseserver.h
 *  @brief  File for giving server acccess to clients and manage client requests

 ***************************************************************************************/

#ifndef CHOOSESERVER_H
#define CHOOSESERVER_H

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <vector>
#include <QNetworkProxy>
#include <map>

#include "../backend/game.h"

class Game;

namespace Ui
{
class chooseServer;
}

/// @brief Class for setting up the server as an instructor
class chooseServer : public QDialog
{
    Q_OBJECT

public:
    /// @brief Construct a window to set uo the game server
    /// @param parent  The parent ui for the class
    /// @param game  Game that was created from the instructor passed
    explicit chooseServer(QWidget *parent, Game *game);

    /// @brief Default Destructor of a window to set uo the game server
    ~chooseServer();

    /// @brief QTcpServer class provides a TCP-based server.
    QTcpServer tcpServer;

    /// @brief A vector storing every client's connection
    std::vector<QTcpSocket *> tcpClients;

    /// @brief connection status of the server
    QTcpSocket *tcpServerConnection = nullptr;

    /// @brief check whether all orders are done for the current week
    bool all_orders_done_for_this_week = false;

    /// @brief check whether the retailer role is taken
    int unique_retailer_id = 0;

    /// @brief check whether the distributor role is taken
    int unique_distributor_id = 0;

    /// @brief check whether the factory role is taken
    int unique_factory_id = 0;

    /// @brief check whether the wholesaler role is taken
    int unique_wholesaler_id = 0;

    /// @brief check if everyone has assigned role in current server, and then we notify the system to prepare the game to start
    bool game_ready_to_start = false;

    /// @brief Method that goes through each role and check if it is taken
    /// @param b comes as a message from the client side
    /// @returns true if a role has not yet been taken (is unique), else false
    bool check_unique_player_role(QByteArray b);

    /// @brief assign 1:1 mapping between role and "node" in the server, i.e. ensure every player is unique
    std::map<QString, QTcpSocket *> role_socket_map;

    /// @brief assign 1:1 mapping, here key=week, value = {role: order}
    std::map<int, std::map<int, int>> all_outgoing_orders_map;

    /// @brief map used to process the orders of each role (role, order)
    std::map<int, int> role_outgoing_order_map;

    /// @brief Method to process information from client
    /// @param x message sent by the client
    /// @returns set(list) of messages
    QStringList parse_key_value(QString x);

    /// @brief Method to send information to client about current week
    /// @param s message to be sent
    /// @returns set(list) of messages
    bool update_order_info(QStringList s);

    /// @brief check whether the retailer has made their order (transaction verification)
    bool retailer_order = false;

    /// @brief check whether the wholesaler has made their order (transaction verification)
    bool wholesaler_order = false;

    /// @brief check whether the distributor has made their order (transaction verification)
    bool distributor_order = false;

    /// @brief check whether the factory has made their order (transaction verification)
    bool factory_order = false;

    /// @brief store each week's inventory
    vector<int> temp_inventory;

    /// @brief store each week's becklog
    vector<int> temp_backlog;

    /// @brief store each week's demand
    vector<int> temp_demand;

    /// @brief store each week's delivered count
    vector<int> temp_delivered;

    /// @brief store each week's cost
    vector<double> temp_cost;

    /// @brief store each week's received count
    vector<int> temp_received;

    /// @brief literally process the orders of each player and send them to server
    void process_orders_this_week();

    /// @brief once everyone is ready to play, game starts
    void create_players_game();

private slots:
    /// @brief start server on custom IP address and port number
    void on_server_connect_clicked();

    /// @brief stop current server
    void on_stop_server_clicked();

private:
    /// @brief default Ui constructor
    Ui::chooseServer *ui;

public slots:
    /// @brief upon clicking the connect to server button, the server waits for a client connection
    void startListening(QHostAddress ip_addr, uint port_no);

    /// @brief server accepts a request from a client
    void acceptConnection();

    /// @brief inside the game check if the orders are successful and progress the weeks
    void updateServerProgress();

    /// @brief show potential error situations
    /// @param socketError default TCP error message
    void displayError(QAbstractSocket::SocketError socketError);

    /// @brief remove each player and stop server
    void disconnect();

private:
    /// @brief bytes used for debugging to verify the connection between server and clients, prepared to be sent
    int bytesToWrite;

    /// @brief bytes used for debugging to verify the connection between server and clients, sent to client
    int bytesWritten;

    /// @brief bytes used for debugging to verify the connection between server and clients, received from client
    int bytesReceived;

    /// @brief keep track of number of connections. Goes up to 4, when all players are connected
    int no_connections = 0;

    /// @brief Player class where the specific retailer is going to be passed for the specific game
    Player *retailer;

    /// @brief Player class where the specific wholesaler is going to be passed for the specific game
    Player *wholesaler;

    /// @brief Player class where the specific distributor is going to be passed for the specific game
    Player *distributor;

    /// @brief Player class where the specific factory is going to be passed for the specific game
    Player *factory;

    /// @brief Game class where the specific game is going to be passed with players assigned
    Game *my_game;
};

#endif // CHOOSESERVER_H
