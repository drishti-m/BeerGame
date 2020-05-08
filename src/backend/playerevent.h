/** 
 *  @file   playerevent.h
 *  @brief  Settings of the playerevent, which are set by the player in the game play
 ***************************************************************************************/

#include "player.h"

#ifndef PLAYEREVENT_H
#define PLAYEREVENT_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Player;

using namespace std;
class PlayerEvent
{
public:
    /**
     * \brief Default constructor for PlayerEvent
    */
    PlayerEvent();

    /**
     * \brief Parametric constructor for PlayerEvent
    */
    PlayerEvent(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver);

    /**
     * \brief distructor for order
    */
    virtual ~PlayerEvent();

    /**
     * \brief Method to execute order
    */
    void executeOrder();

    /**
     * \brief Setter method for the event Id
     * \param n seeting value for eventId
    */
    void setEventId(int n) { eventId = n; }

    /**
     * \brief Setter method for the Game Id
     * \param n seeting value for Game Id
    */
    void setGId(int n) { gId = n; }

    /**
     * \brief Setter method for the number of beers
     * \param n seeting value for NumberOfBeers
    */
    void setNumberOfBeers(int n) { numberOfBeers = n; }

    /**
     * \brief Setter method for the number of beers ordered in a week
     * \param n seeting value for OrderedInWeek
    */
    void setOrderedInWeek(int n) { orderedInWeek = n; }

    /**
     * \brief Setter method for no of beers shipped in a week
     * \param n seeting value for ShippedInWeek
    */
    void setShippedInWeek(int n) { shippedInWeek = n; }

    /**
     * \brief Setter method for receiver of event
     * \param n_player setting value for receiver
    */
    void setReceiver(Player *n_player) { receiver = n_player; }

    /**
     * \brief Setter method for the Player Id of destination player of the order
     * \param n seeting value for player Id
    */
    void setToPlayerId(int n) { toPlayerId = n; }

    /**
     * \brief Setter method for the Player Id of source player of the order
     * \param n seeting value for player Id
    */
    void setFromPlayerId(int n) { fromPlayerId = n; }

    /**
     * \brief Getter method for Player event ID
     * \return eventId
    */
    int getEventId() const { return eventId; }

    /**
     * \brief Getter method for Game ID
     * \return GameID
    */
    int getGId() const { return gId; }

    /**
     * \brief Getter method for number of beers in that order
     * \return numberOfBeers
    */
    int getNumberOfBeers() const { return numberOfBeers; }

    /**
     * \brief Getter method for week in which order was ordered
     * \return orderdInWeek
    */
    int getOrderedInWeek() const { return orderedInWeek; }

    /**
     * \brief Getter method for number of beers shipped in a week
     * \return beers shipped in the week
    */
    int getShippedInWeek() const { return shippedInWeek; }

    /**
     * \brief Getter method for receiver of the event
     * \return receiver
    */
    Player *getReceiver() const { return receiver; }

    /**
     * \brief Getter method for player source ID for the order
     * \return source player ID
    */
    int getFromPlayerId() const { return fromPlayerId; }

    /**
     * \brief Getter method for destinatiion player ID of the order
     * \return destination player ID
    */
    int getToPlayerId() const { return toPlayerId; }
    
protected:
    /**
    * \brief Attribute for player event ID
    */
    int eventId;

    /**
    * \brief Attribute for Game Id
    */
    int gId;

    /**
    * \brief Attribute for describing number of beers for the order
    */
    int numberOfBeers;

    /**
    * \brief Attribute for orderes for a week
    */
    int orderedInWeek;

    /**
    * \brief Attribute for orders shipped in a week
    */
    int shippedInWeek;

    /**
    * \brief Attribute for receiver of order
    */
    Player *receiver;

    /**
    * \brief Attribute for describing the destination player of order
    */
    int toPlayerId;

    /**
    * \brief Attribute for describing the source player of order
    */
    int fromPlayerId;
};

#endif // PLAYEREVENT_H
