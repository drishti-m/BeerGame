#include "playerevent.h"
#include "order.h"
#include "player.h"

Order::Order()
{
}

Order::Order(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver) : PlayerEvent(gid, fromPlayerId, toPlayerId, orderWeek, shipWeek, no_beers, receiver)
{
}
Order::~Order()
{
}

void Order::executeOrder()
{
    //Receiver receives the order that the sender sent (orderDelay) weeks ago
    // this should work once player methods are implemented: update 3
    receiver->receiveOrder(this->numberOfBeers);
}
