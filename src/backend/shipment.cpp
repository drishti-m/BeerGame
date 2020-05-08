#include "shipment.h"

Shipment::Shipment()
{
}

Shipment::Shipment(int gid, int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver) : PlayerEvent(gid, fromPlayerId, toPlayerId, orderWeek, shipWeek, no_beers, receiver)
{
}

Shipment::~Shipment()
{
}

void Shipment::executeShipment()
{
    receiver->receiveShipment(numberOfBeers);
}











