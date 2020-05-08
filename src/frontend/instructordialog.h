/** 
 *  @file   instructordialog.h
 *  @brief  This is the window of the game that pops up for instructor after login.
 ***************************************************************************************/

#ifndef INSTRUCTORDIALOG_H
#define INSTRUCTORDIALOG_H

#include <QDialog>

#include "../backend/instructor.h"
#include "../backend/game.h"

class Instructor;
namespace Ui
{
class InstructorDialog;
}

/// @brief Class for setting the window for instructor in Beer Game
class InstructorDialog : public QDialog
{
    Q_OBJECT

public:

    /// @brief The ui of window
    Ui::InstructorDialog *ui;

    /// @brief Standard pointer to the parent ui
    QWidget *parent;

    /// @brief Construct a instructor dialog
    /// @param parent  The parent ui for the class
    /// @param instructor  The corresponding instructor who opened the window
    explicit InstructorDialog(QWidget *parent, Instructor *instructor);

    /// Default destructor
    ~InstructorDialog();

    /// @brief Method to verify that the parametres of the game are correct
    /// @returns true if validation is successful, false else
    bool validation_check();

    /// @brief Pointer of the instructor linked with this instructordialog
    Instructor *instructor;

private slots:
    /// @brief Method that runs when the create game button is clicked
    void on_createGame_clicked();

    /// @brief Method that runs when the exit game button is clicked
    void on_exit_clicked();

    /// @brief Method that runs when the reset stats game button is clicked, resets default values to parametres
    void on_resetdef_clicked();
};

#endif // INSTRUCTORDIALOG_H
