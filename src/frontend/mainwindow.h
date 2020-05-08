/** 
 *  @file   mainwindow.h
 *  @brief  This is the main window of the game that pops up initially.
 ***************************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "instructordialog.h"
#include "clientrequest.h"
#include "../backend/player.h"
#include "../backend/instructor.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Player;
class Instructor;

/// @brief Class for setting the main window/login window of Beer Game
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Construct a main window.
    /// @param parent  The parent ui for the class
    MainWindow(QWidget *parent = nullptr);
    
    /// @brief Default destructor 
    ~MainWindow();

private slots:
    /// @brief Login button for player/instructor login to their interface
    void on_pushButton_Login_clicked();


private:
    /// @brief The ui of the main window
    Ui::MainWindow *ui;
    /// @brief The pointer to the instructor dialog
    InstructorDialog *id;

    /// @brief The pointer to the client request dialog
    ClientRequest *cr;

    /// @brief The pointer to the player dialog
    PlayerDialog *myplayer;

    /// @brief The pointer to the player class
    Player *player;

    /// @brief The pointer to the instructor class
    Instructor *instructor;
};
#endif // MAINWINDOW_H
