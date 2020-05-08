/** 
 *  @file   order.h
 *  @brief  Settings of the order, which are set by the player in the game play
 ***************************************************************************************/

#ifndef ORDER_H
#define ORDER_H

#include "playerevent.h"
#include "player.h"

class Player;

/// @brief  Settings of the order, which are set by the player in the game play
class Order : public PlayerEvent
{
public:
    /**
     * \brief Default Constructor for Order class, sets the default values for game class
    */
    Order();
    // probably needs a Test Case
    /**
     * \brief Parametric Constructor for Order class, sets the default values for game class
    */
    Order(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver);
    /**
     * \brief destructor for Order class
    */
    ~Order();
    /**
     * \brief method for executing orders
    */
    void executeOrder();
};
#endif //ORDER_H
