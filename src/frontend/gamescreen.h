/**
 *  @file   gamescreen.h
 *  @brief  File for UI for player in the game, and acts as user interface of client backend

 ***************************************************************************************/

#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "../backend/game.h"
#include "../backend/player.h"
#include "clientrequest.h"

#include <QDialog>
#include <QString>

using namespace std;
namespace Ui {
class GameScreen;
}

class Game;
class Player;
class ClientRequest;

/// @brief Class for the game from player's perspective
class GameScreen : public QDialog
{
    Q_OBJECT

public:
    /// @brief default ui constructor for the game screen
    /// @param parent Qt widget calling the ui
    explicit GameScreen(QWidget *parent = nullptr);

    /// @brief ui constructor for the game screen
    /// @param parent Qt widget calling the ui
    /// @param g game to which the gamescreen is assigned
    /// @param p player as an instance of the game to which the gamescreen is assigned
    /// @param c client as an instance of the connection to which the gamescreen is assigned
    GameScreen(QWidget *parent, Game *g, Player *p, ClientRequest *c);

    /// @brief default destructor
    ~GameScreen();

    /// @brief helper method to get current week
    /// @returns current week
    int getPlayer_week_in_game() const;

    /// @brief helper method to set current week
    /// @param value current week
    void setPlayer_week_in_game(int value);

    /// @brief helper method to get ui
    /// @returns game screen ui
    Ui::GameScreen *getUi() const;

    /// @brief helper method to set ui
    /// @param value game screen ui (pointer)
    void setUi(Ui::GameScreen *value);

    /// @brief set initial inventory communicated by the server
    /// @param inv string to be turned to integer of the value of the initial inventory
    void setInitialInventory(QString inv);

    /// @brief helper method to set he player order button to enabled
    void enable_order_button();

    /// @brief update the parametres that the user see for the current game according to information received and sent from last weeks
    /// @param inventory update
    /// @param backlog update
    /// @param incoming_order update
    /// @param delivered update
    /// @param week_cost update
    /// @param received update
    void update_ui_parameters(int inventory, int backlog, int incoming_order, int delivered, double week_cost, int received);

    /// @brief keep track of the updates, by update the corresponding vectors to communicate the data shown on screen
    /// @param inventories vector update
    /// @param backlogs vector update
    /// @param demands vector update
    /// @param delivered vector update
    /// @param costs vector update
    void set_vectors(vector<int> inventories,vector<int> backlogs,vector<int> demands, vector<int> delivered,vector<double> costs);

private slots:
    /// @brief action when sending an order by clicking the button
    void on_player_order_clicked();

private:
    /// @brief pointer to current ui screen
    Ui::GameScreen *ui;

    /// @brief pointer to current game
    Game* my_game;

    /// @brief pointer to current player
    Player* my_player;

    /// @brief information about player role, communicated with server
    QString player_role;

    /// @brief pointer the to socket mapped to the current screen
    ClientRequest *client_socket;

    /// @brief each screen verifies the current week in the game
    int player_week_in_game = 0;

    /// @brief variable to get assigned upon connecting to the game
    int weeks_to_play = 1;

    /// @brief set total cost inside the game scren
    double total_cost = 0.0;

    /// @brief infromation about the initial information communicated with server
    QString initial_inventory_ui;

    /// @brief gamescreen "communicates" this vector of demnds with the server
    vector<int> demands;

    /// @brief gamescreen "communicates" this vector of delivered with the server
    vector<int> delivered;

    /// @brief gamescreen "communicates" this vector of inventories with the server
    vector<int> inventories;

    /// @brief gamescreen "communicates" this vector of backlogs with the server
    vector<int> backlogs;

    /// @brief gamescreen "communicates" this vector of costs with the server
    vector<double> costs;

    /// @brief gamescreen "communicates" this vector of received with the server
    vector<int> received;
};

#endif // GAMESCREEN_H
