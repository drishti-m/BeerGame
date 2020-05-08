/** 
 *  @file   instructor.h
 *  @brief  Defines the Instructor
 ************************************/

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <vector>
#include <string>

#include "game.h"
#include "../frontend/instructordialog.h"
#include "../frontend/ui_instructordialog.h"

/// @brief Class for defining an instructor, his ID, email, password and list of games
class Instructor
{
public:
  /// @brief Vector storing unique ID values
  std::vector<int> IIDS;

  /// @brief Default Constructor
  Instructor()
  {
    setInstrId(0);
  }

  /// @brief Destructor
  ~Instructor()
  {
    IIDS.erase(std::remove(IIDS.begin(), IIDS.end(), instrId), IIDS.end());
  }

  /// @brief create game and apply all the game setting that were given in the instructor dialog
  int createGame();

  /// @brief create a certain amount of games
  /// @param numberOfGames number of games
  /// @returns vector of games
  std::vector<Game *> createGames(int numberOfGames);

private:
  Ui::InstructorDialog *ui;
  QWidget *parent_ui;

  /// @brief The instructor Id
  int instrId;

  /// @brief The Instructor's Email
  std::string instrEmail;

  /// @brief The Instructor's Password
  std::string instrPassword;

  /// @brief The Instructor's list of games
  std::vector<Game *> games;

public:
  /**
     *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
     *
      * \brief Implementation of getters and setter for this class
      *
      * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      */

  int getInstrId() const;
  void setInstrId(int value);

  std::string getInstrEmail() const;
  void setInstrEmail(const std::string &value);

  std::string getInstrPassword() const;
  void setInstrPassword(const std::string &value);

  std::vector<Game *> getGames() const;
  void setGames(const std::vector<Game *> &value);
};

#endif // INSTRUCTOR_H
