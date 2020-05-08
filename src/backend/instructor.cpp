#include <string>
#include <vector>

#include "game.h"
#include "instructor.h"
#include "../frontend/instructordialog.h"
#include "../frontend/ui_instructordialog.h"
#include "../frontend/playerdialog.h"

int Instructor::createGame()
{
    Game *newgame = new Game(1, 1.0, 1.0, 2, 26, 12, 1);
    games.push_back(newgame);
    // Creating four players
    Player *consumer = new Player(newgame, CONSUMER);
    Player *retailer = new Player(newgame, RETAILER);
    Player *wholesaler = new Player(newgame, WHOLESALER);
    Player *distributor = new Player(newgame, DISTRIBUTOR);
    Player *factory = new Player(newgame, FACTORY);

    newgame->addPlayer(consumer);
    newgame->addPlayer(retailer);
    newgame->addPlayer(wholesaler);
    newgame->addPlayer(distributor);
    newgame->addPlayer(factory);

    return 0;
}

std::vector<Game *> Instructor::createGames(int numberOfGames)
{
    for (int i = 0; i < numberOfGames; i++)
    {
        this->createGame();
    }
    return games;
}

/**
 *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *
  * \brief Implementation of getters and setter for this class
  *
  * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  */

int Instructor::getInstrId() const
{
    return instrId;
}

void Instructor::setInstrId(int value)
{
    if (value == -1)
    {
        value++;
    } // -1 is used as "unset value", no player can have it!
    /*
    if (instrId != -1){ // meaning setter was already used on this player, re-set
        IIDS.erase(std::remove(IIDS.begin(), IIDS.end(), instrId), IIDS.end());
    }
    */
    for (auto it : IIDS)
    { // Finding unique value of a instr ID
        while (value == it)
        {
            value++;
        }
    }
    instrId = value;
    IIDS.push_back(instrId); // Add the ID to the unique vector
}

std::string Instructor::getInstrEmail() const
{
    return instrEmail;
}

void Instructor::setInstrEmail(const std::string &value)
{
    instrEmail = value;
}

std::string Instructor::getInstrPassword() const
{
    return instrPassword;
}

void Instructor::setInstrPassword(const std::string &value)
{
    instrPassword = value;
}

std::vector<Game *> Instructor::getGames() const
{
    return games;
}

void Instructor::setGames(const std::vector<Game *> &value)
{
    games = value;
}
