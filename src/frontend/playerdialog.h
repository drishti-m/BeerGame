/** 
 *  @file   playerdialog.h
 *  @brief  This is the window of the game that pops up for player after login.
 ***************************************************************************************/

#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <vector>
#include "../backend/player.h"
#include "../backend/game.h"
#include "clientrequest.h"

class Game;
class Player;
class ClientRequest;

namespace Ui
{
class PlayerDialog;
}
/// @brief Class for setting the window for players in Beer Game
class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Class for setting the window for players in Beer Game
    ClientRequest *client = nullptr;

    /// @brief Class for establishing the socket connection
    QTcpSocket *connection;

    /// @brief helping function to pop a message box
    /// @param title of the message
    /// @param body of the message
    void show_messageBox_to_Player(QString title, QString body);

    /// @brief determine whether a role is available
    /// @param val indicate if the role is available
    void enable_role_buttons(bool val);

    /// @brief Construct a player dialog
    /// @param parent  The parent ui for the class
    /// @param game  The game pointer of the player's game
    /// @param player  The pointer of the player linked with the player dialog
    PlayerDialog(QWidget *parent, Game &game, Player *player);

    /// @brief Construct a player dialog
    /// @param parent  The parent ui for the class
    /// @param game  The game pointer of the player's game
    /// @param allPlayers  The vector of pointers of the players linked with the player dialog
    explicit PlayerDialog(QWidget *parent, Game &game, std::vector<Player *> allPlayers);

    /// Default destructor
    ~PlayerDialog();

    /// @brief Method to set the player class ui with plyerdialog's ui
    void setPlayerUI();

    /// @brief Method to get the Player linked with the Playerdialog
    Player *getPlayer() const;

    /// @brief Method to set the Player linked with the Playerdialog
    void setPlayer(Player *value);

    /// @brief Helper Method to set the UI's images
    void setChooseImages();

    /// @brief Helper Method to get the player dialog's Ui
    /// @returns the player dialog
    Ui::PlayerDialog *getUi() const;

    /// @brief Helper Method to set the player dialog's Ui
    /// @param value the player dialog
    void setUi(Ui::PlayerDialog *value);

    /// @brief Helper Method to get the client request dialog's Ui
    /// @returns the request dialog
    ClientRequest *getClient() const;

    /// @brief Helper Method to set the client request dialog's Ui
    /// @param value the request dialog
    void setClient(ClientRequest *value);

private slots:

    /// @brief Method for role selection retailer (button) for player in their interface
    void on_retailer_btn_clicked();

    /// @brief Method for role selection wholesaler (button) for player in their interface
    void on_wholesaler_btn_clicked();

    /// @brief Method for role selection distributor (button) for player in their interface
    void on_distributor_btn_clicked();

    /// @brief Method for role selection factory (button) for player in their interface
    void on_factory_btn_clicked();

private:
    /// @brief The ui of the main window
    Ui::PlayerDialog *ui;

    /// @brief The game pointer of the player's game
    Game &game;

    /// @brief The pointer of the player linked with the player dialog
    Player *player;

    /// @brief The vector of pointers of the players linked with the player dialog
    std::vector<Player *> allPlayers;
};

#endif // PLAYERDIALOG_H
