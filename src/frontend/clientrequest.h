/**
 *  @file   clientrequest.h
 *  @brief  File for requesting server acccess from client side, and managing client interactions

 ***************************************************************************************/

#ifndef CLIENTREQUEST_H
#define CLIENTREQUEST_H

#include <QDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <vector>
#include <QNetworkProxy>

#include "../backend/player.h"
#include "../backend/game.h"
#include "playerdialog.h"
#include "gamescreen.h"


class Player;
class Game;
class PlayerDialog;
class GameScreen;

namespace Ui {
class ClientRequest;
}

/// @brief Class for requesting server acccess from client side
class ClientRequest : public QDialog
{
    Q_OBJECT

public:
    /// @brief constructor
    /// @param parent Widget which called the current window
    /// @param player Client instance requesting the access
    explicit ClientRequest(QWidget *parent, Player *player);

    /// @brief default destructor (deletes ui)
    ~ClientRequest();

    /// @brief try to get tcp connection
    /// @returns socket where the client is about to connect
    QTcpSocket *getTcpServerConnection() const;

    /// @brief establish tcp connection
    /// @param value information about the socket to which connection is requested
    void setTcpServerConnection(QTcpSocket *value);

    /// @brief receive message from server to check if role is available
    /// @param b message received from server
    /// @returns integer used as boolean for every role to determine if it is available
    int check_role_available(QByteArray b);

    /// @brief upon successful login into the server, we already assign the player to the game here, but still the game does not start
    void showGame();

    /// @brief send order, this method remained from the previous run, as we integrated a new window for the game
    /// @param x say from which player
    /// @param w say for which week and what is the order
    void send_order(QString x, QString w);

    /// @brief parse messages from server
    /// @param server_string message received from server
    /// @returns message split to json list
    QStringList parse_key_value(QString server_string);

    /// @brief update the game to next round
    /// @param current_week integer corresponding to current week in the game
    /// @param parsed_list data about current run, yet to be mapped to the week
    void advance_round(int current_week, QStringList parsed_list);


private:
    /// @brief default client request Ui
    Ui::ClientRequest *ui;

public slots:
    /// @brief request connection to server from instructor
    /// @param ip address to where we request connection
    /// @param port number of the ip connection to where we request connection
    void requestConnection(QHostAddress ip , uint port);

    /// @brief client starts sending at the acceptance of a connection request
    void clientSendMessageToServer();


    /// @brief slot for client error messsage
    /// @param socketError default socket error variable container
    void displayError(QAbstractSocket::SocketError socketError);

    /// @brief disconnect from game, by disconnecting from host(server)
    void disconnect();

    /// @brief show received from server messages
    void displayServerMessage();

private slots:
    /// @brief request connection button to checks if a client can connect, if yes connects
    void on_client_request_connect_clicked();

private:
    /// @brief QTcpServer class provides a TCP-based server
    QTcpServer tcpServer;

    /// @brief vector storing the socket of each player
    std::vector <QTcpSocket*> tcpClients;

    /// @brief pointer to QTcpSocket class that provides a TCP-based server connection
    QTcpSocket* tcpServerConnection;

    /// @brief bytes used for debugging to verify the connection between server and clients, prepared to be sent
    int bytesToWrite;

    /// @brief bytes used for debugging to verify the connection between server and clients, sent to server
    int bytesWritten;

    /// @brief bytes used for debugging to verify the connection between server and clients, received from client
    int bytesReceived;

    /// @brief each client resides locally the information about the number of connections
    int no_connections = 0;

    /// @brief The pointer of the player linked with the player dialog
    Player *player;

    /// @brief The pointer of the game linked with the player dialog
    Game *g;

    /// @brief The pointer of the player dialog that is requested
    PlayerDialog *pd;

    /// @brief role to be assigned up to the player choice
    QString playerRole= "none";

    /// @brief The pointer of the gamescreen dialog that is requested
    GameScreen *my_game_screen;

    /// @brief need to keep track when game is about to start
    bool game_start = false;

    /// @brief inventory in the stage when the game has not yet started
    QString inventory_ui = "0";
};

#endif // CLIENTREQUEST_H
