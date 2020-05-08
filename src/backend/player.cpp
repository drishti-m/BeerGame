#include <string>
#include <vector>
#include <time.h>

//#include "game.h"
#include "player.h"
//#include "order.h"
//#include "shipment.h"

//#include "../frontend/playerdialog.h"
// #include "ui_playerdialog.h"

using namespace std;

Player::Player(Game *game, int role)
{
    setPId(game->getGId() + role);
    //this->pId = getPId();
    this->game = game;
    this->role = role;
    this->inventory = game->getStartingInventory();
}

void Player::setUi(Ui::PlayerDialog *ui)
{
    this->playerui = ui;
}

void Player::placeOrder(int numberOfBeers)
{

    game->addOrder(this->role, numberOfBeers);

    //cout << "order added to game\n";

    if (numberOfBeers > 0)
    {
        orderPlaced = true;
    }
    else
    {
        orderPlaced = false;
    }
}

void Player::placeShipment(int no_Beers)
{

    int total_demands;
    if (backorder > 0)
    {
        total_demands = no_Beers + backorder;
    }
    else
    {
        total_demands = no_Beers;
    }

    if (getAvailableShipment(total_demands) == total_demands)
    {
        outgoingShipment = total_demands;
        backorder = 0;
    }
    else
    {
        outgoingShipment = getAvailableShipment(total_demands);
        backorder = total_demands - outgoingShipment;
    }

    game->addShipment(role, outgoingShipment);

    if (outgoingShipment > 0)
    {
        shipmentPlaced = true;
    }
    else
    {
        shipmentPlaced = false;
    }

    //add to delivered graph and backorder
    add_delivered_to_vector(outgoingShipment);
    add_backlog_to_vector(backorder);
}

int Player::getAvailableShipment(int d)
{

    int available_ship = inventory - d;
    if (available_ship < 0)
    {
        // backorder += d - inventory;
        available_ship = inventory;
    }
    else
    {
        available_ship = d;
    }

    return available_ship;
}

void Player::receiveShipment(int receivedBeers)
{
    if (receivedBeers > 0)
    {
        shipmentReceived = true;
    }
    else
    {
        shipmentReceived = false;
    }

    incomingShipment = receivedBeers;

    add_received_to_vector(incomingShipment);
}

void Player::receiveOrder(int orderedBeers)
{
    incomingOrder = orderedBeers;

    if (orderedBeers > 0)
    {
        orderReceived = true;
    }
    else
    {
        orderReceived = false;
    }

    add_demand_to_vector(orderedBeers);
}

void Player::decreaseInventory(int numberOfBeers)
{
    inventory = inventory - numberOfBeers;
}

void Player::increaseInventory(int numberOfBeers)
{
    inventory += numberOfBeers;
}

vector<int> Player::getDemand_every_week() const
{
    return demand_every_week;
}

void Player::setDemand_every_week(const vector<int> &value)
{
    demand_every_week = value;
}

vector<int> Player::getBacklog_every_week() const
{
    return backlog_every_week;
}

void Player::setBacklog_every_week(const vector<int> &value)
{
    backlog_every_week = value;
}

vector<int> Player::getInventory_every_week() const
{
    return inventory_every_week;
}

void Player::setInventory_every_week(const vector<int> &value)
{
    inventory_every_week = value;
}

vector<double> Player::getCost_every_week() const
{
    return cost_every_week;
}

void Player::setCost_every_week(const vector<double> &value)
{
    cost_every_week = value;
}

vector<int> Player::getDelivered_every_week() const
{
    return delivered_every_week;
}

void Player::setDelivered_every_week(const vector<int> &value)
{
    delivered_every_week = value;
}

void Player::add_received_to_vector(int x)
{
    received_every_week.push_back(x);
}

void Player::add_demand_to_vector(int x)
{
    demand_every_week.push_back(x);
}

void Player::add_delivered_to_vector(int x)
{
    delivered_every_week.push_back(x);
}

void Player::add_backlog_to_vector(int x)
{
    backlog_every_week.push_back(x);
}

void Player::add_inventory_to_vector(int x)
{
    inventory_every_week.push_back(x);
}

void Player::add_cost_to_vector(double x)
{
    cost_every_week.push_back(x);
}

vector<int> Player::getReceived_every_week() const
{
    return received_every_week;
}

void Player::setReceived_every_week(const vector<int> &value)
{
    received_every_week = value;
}

/**
 *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *
  * \brief Implementation of getters and setter for this class
  *
  * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  */

Game *Player::getGame() const
{
    return game;
}

void Player::setGame(Game *value)
{
    game = value;
}

Ui::PlayerDialog *Player::getPlayerui() const
{
    return playerui;
}

void Player::setPlayerui(Ui::PlayerDialog *value)
{
    playerui = value;
}

int Player::getPId() const
{
    return pId;
}

void Player::setPId(int value)
{
    pId = value;
}

int Player::getRole() const
{
    return role;
}

void Player::setRole(int value)
{
    role = value;
}

int Player::getInventory() const
{
    return inventory;
}

void Player::setInventory(int value)
{
    inventory = value;
}

int Player::getBackorder() const
{
    return backorder;
}

void Player::setBackorder(int value)
{
    backorder = value;
}

int Player::getIncomingOrder() const
{
    return incomingOrder;
}

void Player::setIncomingOrder(int value)
{
    incomingOrder = value;
}

int Player::getIncomingShipment() const
{
    return incomingShipment;
}

void Player::setIncomingShipment(int value)
{
    incomingShipment = value;
}

int Player::getOutgoingShipment() const
{
    return outgoingShipment;
}

void Player::setOutgoingShipment(int value)
{
    outgoingShipment = value;
}

int Player::getDemand() const
{
    return demand;
}

void Player::setDemand(int value)
{
    demand = value;
}

double Player::getCost() const
{
    return cost;
}

void Player::setCost(double value)
{
    cost = value;
}

double Player::getTotalCost() const
{
    return totalCost;
}

void Player::setTotalCost(double value)
{
    totalCost = value;
}

bool Player::isOrderReceived() const
{
    return orderReceived;
}

void Player::setOrderReceived(bool value)
{
    orderReceived = value;
}

bool Player::isShipmentReceived() const
{
    return shipmentReceived;
}

void Player::setShipmentReceived(bool value)
{
    shipmentReceived = value;
}

bool Player::isOrderPlaced() const
{
    return orderPlaced;
}

void Player::setOrderPlaced(bool value)
{
    orderPlaced = value;
}

bool Player::isShipmentPlaced() const
{
    return shipmentPlaced;
}

void Player::setShipmentPlaced(bool value)
{
    shipmentPlaced = value;
}
