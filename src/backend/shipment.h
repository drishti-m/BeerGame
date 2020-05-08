/** 
 *  @file   shipment.h
 *  @brief  Settings of the shipment, which are set by the player in the game play
 ***************************************************************************************/

#ifndef SHIPMENT_H
#define SHIPMENT_H

#include "playerevent.h"
#include "player.h"

/// @brief  Settings of the shipment, which are set by the player in the game play
class Shipment : public PlayerEvent
{
public:
    /**
     * \brief Default Constructor for Shipment class, sets the default values for game class
    */
    Shipment();

    /**
     * \brief Parametric Constructor for Shipment class, sets the default values for game class
    */

    Shipment(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver);

    /**
     * \brief distructor for Shipment class
    */
    ~Shipment();

    /**
     * \brief method for executing shipment
    */
    void executeShipment();
};

#endif // SHIPMENT_H
