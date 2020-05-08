/**
 *  @file   playerevent.cpp
 *  @brief  Settings of the playerevent, which are set by the player in the game play
 ***************************************************************************************/

#include "playerevent.h"
#include "player.h"

/**
 * \brief Default constructor for PlayerEvent
*/
PlayerEvent::PlayerEvent()
{
    eventId = gId = numberOfBeers = orderedInWeek = shippedInWeek = toPlayerId = fromPlayerId = 0;
}

/**
 * \brief Parametric constructor for PlayerEvent
 * \param gid game ID
*/
PlayerEvent::PlayerEvent(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver)
{
    this->gId = gid;
    this->fromPlayerId = fromPlayerId;
    this->toPlayerId = toPlayerId;
    this->orderedInWeek = orderWeek;
    this->shippedInWeek = shipWeek;
    this->numberOfBeers = no_beers;
    this->receiver = receiver;
}

PlayerEvent::~PlayerEvent()
{
}
