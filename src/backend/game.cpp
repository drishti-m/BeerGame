#include <map>
#include <vector>
#include <ctime>

#include "game.h"
#include "player.h"
#include "shipment.h"
#include "order.h"

#include <iostream>

#define G_FACTORY 1
#define G_DISTRIBUTOR 2
#define G_WHOLESALER 3
#define G_RETAILER 4
#define G_CUSTOMER 5
#define G_BREWERY 6
using namespace std;
Game::Game(int instrId)
{

    this->instrId = instrId;
}

Game::Game(int instrId, double backlogCost, double holdingCost, int orderDelay, int totalWeeks, int startInventory, int factoryDelay)
{
    setGId(instrId * 10);
    this->instrId = instrId;
    this->backorderCost = backlogCost;
    this->holdingCost = holdingCost;
    this->orderDelay = orderDelay;
    this->weeksToBePlayed = totalWeeks;
    this->startingInventory = startInventory;
    this->factoryDelay = factoryDelay;
}

void Game::startGame()
{
    Player retailer;
    retailer.setRole(G_RETAILER);
    Player wholesaler;
    wholesaler.setRole(G_WHOLESALER);
    Player distributor;
    distributor.setRole(G_DISTRIBUTOR);
    Player manufacturer;
    manufacturer.setRole(G_FACTORY);

    addPlayer(&manufacturer);
    addPlayer(&distributor);
    addPlayer(&wholesaler);
    addPlayer(&retailer);

    currentWeek = 1;

    for (int week = 0; week < weeksToBePlayed; week++)
    {
        cout << "WEEK: " << currentWeek << endl;

        for (int i = 0; i < nPlayers; i++)
        {
            int role = i + 1;

            if (role == G_FACTORY)
            {
                cout << "Factory: \n";
            }
            else if (role == G_DISTRIBUTOR)
            {
                cout << "Distributor: \n";
            }
            else if (role == G_WHOLESALER)
            {
                cout << "Wholesaler: \n";
            }
            else if (role == G_RETAILER)
            {
                cout << "Retailer: \n";
            }
            else
            {
                perror("Invalid role \n");
            }

            int outgoing_order; //, incoming_demand;
            cout << "Enter your order: \n";

            if (testing_mode == false)
            {
                cin >> outgoing_order;
            }
            else
            {
                vector<int> order_list;
                order_list = testing_input_outgoing_order[week];
                outgoing_order = order_list[i];
            }

            cout << "Outgoing order " << outgoing_order << endl;

            players[i]->placeOrder(outgoing_order);
        }

        executeOrdersForCurrentWeek();
        executeShipmentsForCurrentWeek();
        updatePlayerInventories();
        advanceWeek();

        cout << "\n\n";
    }

    for (int i = 0; i < nPlayers; i++)
    {
        total_cost += players[i]->getTotalCost();
    }
}

void Game::executeOrdersForCurrentWeek()
{
    int incoming_demand;
    for (int i = 0; i < this->nPlayers; i++)
    {
        int role = i + 1;

        if (players[i]->getRole() == G_RETAILER)
        {
            incoming_demand = getConsumerDemandForWeek(currentWeek);
            players[i]->setIncomingOrder(incoming_demand);
            //cout << "Retailer's Incoming order: " << players[i]->getIncomingOrder() << endl;
            players[i]->setDemand(incoming_demand);

            vector<int> player_demand_list = players[i]->getDemand_every_week();
            player_demand_list.push_back(incoming_demand);
            players[i]->setDemand_every_week(player_demand_list);

            //retailer receives customer's order without any delay, so gets the demand in the same time
            players[i]->receiveOrder(incoming_demand);
        }

        //set incoming orders this week for upstream player (retailer's upstream player = wholesaler)
        // factory has no upstream player. it sends to brewery (not implemented yet)
        //factory's incoming order is set by ditributor
        if (players[i]->getRole() != G_FACTORY)
        {
            if (currentWeek <= orderDelay)
            {
                //cout << "Initial value: ";
                int initial_value = 6;

                //incoming demand
                initial_value = 6;
                //incoming order will be set in fct called in executeOrder so no need to do here
                //players[i]->setIncomingOrder(initial_value);
                Order initial_orders;
                initial_orders.setNumberOfBeers(initial_value);
                initial_orders.setReceiver(getUpstream(role));
                initial_orders.executeOrder();
            }
            else

            {

                vector<Order> order_list;
                //for factory taking factoryDelay instead of orderDElay

                //adding for factory
                if (players[i]->getRole() == G_DISTRIBUTOR)
                {
                    if (currentWeek <= factoryDelay)
                    {
                        int initial_value = 0;

                        //incoming demand
                        initial_value = 0;
                        //incoming order will be set in fct called in executeOrder so no need to do here
                        //players[i]->setIncomingOrder(initial_value);
                        Order initial_orders;
                        initial_orders.setNumberOfBeers(initial_value);
                        initial_orders.setReceiver(getUpstream(role));
                        initial_orders.executeOrder();
                    }
                    else
                    {

                        order_list = ordersToBeExecuted[currentWeek - 1 - factoryDelay];
                        Order my_order;
                        my_order = order_list[role - 1];
                        my_order.setReceiver(getUpstream(role));
                        my_order.executeOrder();
                    }
                }
                else
                {
                    order_list = ordersToBeExecuted[currentWeek - 1 - orderDelay];

                    Order my_order;
                    my_order = order_list[role - 1];
                    my_order.setReceiver(getUpstream(role));
                    my_order.executeOrder();
                }
            }
        }
        else
        {
            // cout << "factory: do nth\n";
            //all values set for factory by upstream player's order;
        }
    }
    for (int i = 0; i < this->nPlayers; i++)
    {

        int role = players[i]->getRole();

        if (role == G_FACTORY)
        {
            cout << "Factory: \n";
        }
        else if (role == G_DISTRIBUTOR)
        {
            cout << "Distributor: \n";
        }
        else if (role == G_WHOLESALER)
        {
            cout << "Wholesaler: \n";
        }
        else if (role == G_RETAILER)
        {
            cout << "Retailer: \n";
        }
        else
        {
            cout << "Invalid role \n";
        }
        cout << "Incoming demand is " << players[i]->getIncomingOrder() << endl;
    }
}

int Game::getConsumerDemandForWeek(int week)
{
    int size = consumerDemandPerWeek.size();
    if (size >= week)
        return consumerDemandPerWeek[week - 1];
    else
    {
        perror("No customer demand data found for given week\n");
        return -1;
    }
}
void Game::executeShipmentsForCurrentWeek()
{
    for (int i = 0; i < this->nPlayers; i++)
    {

        //managing outgoing delivery for all players
        //check if enough inventory available to fulfill outgoing deliveries (incoming order == outgoing shipment) when order arrives and enough inventory
        if (players[i]->getAvailableShipment(players[i]->getIncomingOrder()) >= players[i]->getIncomingOrder())
        {
            // addShipment(players[i]->getRole(), players[i]->getIncomingOrder());
            players[i]->placeShipment(players[i]->getIncomingOrder());
        }
        else
        {
            players[i]->placeShipment(players[i]->getAvailableShipment(players[i]->getIncomingOrder()));

            //update backlog here in updateInventories
        }
    }

    for (int i = 0; i < this->nPlayers; i++)
    {
        int incoming_delivery;
        int role = i + 1;
        //managing incoming deliveries for all players

        //factory's incoming delivery is its' own orderplaced of delay weeks ago
        if (players[i]->getRole() == G_FACTORY)
        {

            vector<Order> order_list;
            //assuming factory gets as much incoming deliveries from brewery as it demanded delay weeks ago.

            if (currentWeek <= factoryDelay + factoryDelay)
            {
                int initial_value = 0;
                incoming_delivery = initial_value;
            }
            else
            {

                order_list = ordersToBeExecuted[currentWeek - 1 - factoryDelay - factoryDelay];
                incoming_delivery = order_list[role - 1].getNumberOfBeers();
            }

            //factory receives it's own orderPlaced as shipment
            players[i]->receiveShipment(incoming_delivery);
        }

        //retailer-> customer receiving // excluding this interaction here, others below included:
        //wholesaler-> retailer receiving
        //distributor -> wholesaler receiving
        //factory -> distributor receiving
        if (players[i]->getRole() != G_RETAILER)
        {

            if (currentWeek <= shipmentDelay)
            {
                //cout << "Initial value\n";

                //receiver_incoming_delivery
                int initial_value = 0;
                Shipment initial_shipments;
                initial_shipments.setNumberOfBeers(initial_value);
                initial_shipments.setReceiver(getDownstream(role));
                initial_shipments.executeShipment();
            }
            else
            {

                int downstream_role = players[i]->getRole();
                vector<Shipment> ship_list;

                ship_list = shipmentsToBeExecuted[currentWeek - 1 - shipmentDelay];
                Shipment my_ship;
                my_ship = ship_list[downstream_role - 1];
                my_ship.executeShipment();
            }
        }
    }

    for (int i = 0; i < this->nPlayers; i++)
    {

        int role = players[i]->getRole();
        //cout << "Shipment \n" << endl;
        if (role == G_FACTORY)
        {
            cout << "Factory: \n";
        }
        else if (role == G_DISTRIBUTOR)
        {
            cout << "Distributor: \n";
        }
        else if (role == G_WHOLESALER)
        {
            cout << "Wholesaler: \n";
        }
        else if (role == G_RETAILER)
        {
            cout << "Retailer: \n";
        }
        else
        {
            cout << "Invalid role \n";
        }
        cout << "Incoming delivery: " << players[i]->getIncomingShipment() << endl;
    }

    cout << "successfully exiting\n";
}

void Game::updatePlayerInventories()
{
    for (int i = 0; i < this->nPlayers; i++)
    {
        if (players[i]->isShipmentReceived() == true)
        {
            players[i]->increaseInventory(players[i]->getIncomingShipment());
            players[i]->setShipmentReceived(false);
        }
        int backorder = players[i]->getBackorder();
        int available_inv = players[i]->getAvailableShipment(players[i]->getIncomingOrder());
        cout << "inventory " << players[i]->getInventory() << " av shipment " << available_inv << endl;
        if (available_inv == players[i]->getIncomingOrder())
        {
            players[i]->decreaseInventory(available_inv);
            cout << "Outgoing delivery is: " << players[i]->getIncomingOrder() << endl;
        }
        else
        {
            players[i]->decreaseInventory(available_inv);
            backorder += players[i]->getIncomingOrder() - available_inv;
            players[i]->setBackorder(backorder);

            //update backlog here

            cout << "Not enough inventory, so outgoing delivery is: " << available_inv << endl;
            cout << "Backorder is now: " << players[i]->getBackorder() << endl;
        }

        double cost = players[i]->getTotalCost();

        cost = backorderCost * players[i]->getBackorder() + holdingCost * players[i]->getInventory();

        players[i]->setTotalCost(cost);

        //add to player's inventory and cost graph

        players[i]->add_inventory_to_vector(players[i]->getInventory());
        players[i]->add_cost_to_vector(players[i]->getTotalCost());
    }
}

int Game::getConsumerOrderForWeek()
{
    return consumerDemandPerWeek[currentWeek - 1];
}

int Game::advanceWeek()
{

    if (currentWeek < weeksToBePlayed)
    {
        currentWeek++;
    }
    else
    {
        cout << "game over" << endl;
    }

    return currentWeek;
}

void Game::addOrder(const int &role, int numberOfBeers)
{
    Player *receiver;
    Player *sender;
    sender = players[role - 1];
    receiver = getUpstream(role);

    //if player is factory, brewery receives factory's order
    if (role == G_FACTORY)
    {
        Player brewery; //external player
        brewery.setRole(G_BREWERY);
        receiver = &brewery;
    }

    if (receiver == NULL)
    {
        perror("pointer null\n");
    }

    Order s(this->gId, sender->getPId(), receiver->getPId(), this->currentWeek - 1, this->currentWeek - 1 + orderDelay, numberOfBeers, receiver);
    vector<Order> order_list_current_week;

    if (ordersToBeExecuted.find(this->currentWeek - 1) != ordersToBeExecuted.end())
    {
        //Key found
        order_list_current_week = ordersToBeExecuted[currentWeek - 1];
    }

    order_list_current_week.push_back(s);
    ordersToBeExecuted[currentWeek - 1] = order_list_current_week;
}

void Game::addShipment(const int &role, int numberOfBeers)
{
    Player *receiver;
    Player *sender;
    unsigned int sizes = role;
    if (players.size() < sizes)
    {
        perror("Null pointer\n");
    }
    sender = players[role - 1];

    receiver = getDownstream(role);
    //if player is retailer, customer receives shipment
    if (role == G_RETAILER)
    {
        Player customer; //external player
        customer.setRole(G_CUSTOMER);
        receiver = &customer;
    }

    if ((receiver == NULL))
    {
        perror("Null pointer\n");
    }

    Shipment s(this->gId, sender->getPId(), receiver->getPId(), this->currentWeek - 1 - orderDelay, this->currentWeek - 1, numberOfBeers, receiver);
    vector<Shipment> ship_list_current_week;

    if (shipmentsToBeExecuted.find(this->currentWeek - 1) != shipmentsToBeExecuted.end())
    {
        //Key found
        ship_list_current_week = shipmentsToBeExecuted[currentWeek - 1];
    }

    ship_list_current_week.push_back(s);
    shipmentsToBeExecuted[currentWeek - 1] = ship_list_current_week;
}

void Game::addPlayer(Player *new_player)
{
    players.push_back(new_player);
    new_player->setGame(this);
    new_player->setInventory(startingInventory);

    for (int i = 0; i < weeksToBePlayed; i++)
    {
        consumerDemandPerWeek.push_back(4);
    }
}

Player *Game::getDownstream(int role)
{
    if (role == G_RETAILER)
    {
        return NULL;
    }
    return players[role];
}

Player *Game::getUpstream(int role)
{
    if (role == G_FACTORY)
        return NULL;
    return players[role - 2];
}

std::vector<std::string> Game::generatePasswords()
{
    // set array of possible chars

    vector<string> passwords;
    string s = "";
    string alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    // for each password
    for (int j = 0; j < 4; ++j)
    {
        char c;
        s = "";
        // for 10 chars
        for (int i = 0; i < 10; ++i)
        {
            // select random char and push onto string
            c = alphanum[rand() % 62];
            s += c;
        }

        // push final password onto passwords
        passwords.push_back(s);
    }

    return passwords;
}

double Game::getTotal_cost() const
{
    return total_cost;
}

void Game::setTotal_cost(double value)
{
    total_cost = value;
}

map<int, vector<int>> Game::getTesting_input_outgoing_order() const
{
    return testing_input_outgoing_order;
}

void Game::setTesting_input_outgoing_order(const map<int, vector<int>> &value)
{
    testing_input_outgoing_order = value;
}

bool Game::getTesting_mode() const
{
    return testing_mode;
}

void Game::setTesting_mode(bool value)
{
    testing_mode = value;
}

int Game::getTotalShipmentsInWeek() const
{
    return totalShipmentsInWeek;
}

void Game::setTotalShipmentsInWeek(int value)
{
    totalShipmentsInWeek = value;
}

int Game::getTotalOrdersInWeek() const
{
    return totalOrdersInWeek;
}

void Game::setTotalOrdersInWeek(int value)
{
    totalOrdersInWeek = value;
}

/**
 *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *
  * \brief Implementation of getters and setter for this class
  *
  * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
  */

int Game::getGId() const
{
    return gId;
}

void Game::setGId(int value)
{
    gId = value;
}

unsigned int Game::getInstrId() const
{
    return instrId;
}

void Game::setInstrId(unsigned int value)
{
    instrId = value;
}

unsigned int Game::getPFactId() const
{
    return pFactId;
}

void Game::setPFactId(unsigned int value)
{
    pFactId = value;
}

unsigned int Game::getPDistributorId() const
{
    return pDistributorId;
}

void Game::setPDistributorId(unsigned int value)
{
    pDistributorId = value;
}

unsigned int Game::getPWholesalerId() const
{
    return pWholesalerId;
}

void Game::setPWholesalerId(unsigned int value)
{
    pWholesalerId = value;
}

unsigned int Game::getPRetailerId() const
{
    return pRetailerId;
}

void Game::setPRetailerId(unsigned int value)
{
    pRetailerId = value;
}

std::map<int, std::vector<Order>> Game::getOrdersToBeExecuted() const
{
    return ordersToBeExecuted;
}

void Game::setOrdersToBeExecuted(const std::map<int, std::vector<Order>> &value)
{
    ordersToBeExecuted = value;
}

std::map<int, std::vector<Shipment>> Game::getShipmentsToBeExecuted() const
{
    return shipmentsToBeExecuted;
}

void Game::setShipmentsToBeExecuted(const std::map<int, std::vector<Shipment>> &value)
{
    shipmentsToBeExecuted = value;
}

std::vector<Player *> Game::getPlayers() const
{
    return players;
}

void Game::setPlayers(const std::vector<Player *> &value)
{
    players = value;
}

std::vector<int> Game::getConsumerDemandPerWeek() const
{
    return consumerDemandPerWeek;
}

void Game::setConsumerDemandPerWeek(const std::vector<int> &value)
{
    consumerDemandPerWeek = value;
}

int Game::getOrderDelay() const
{
    return orderDelay;
}

void Game::setOrderDelay(int value)
{
    orderDelay = value;
}

int Game::getShipmentDelay() const
{
    return shipmentDelay;
}

void Game::setShipmentDelay(int value)
{
    shipmentDelay = value;
}

double Game::getHoldingCost() const
{
    return holdingCost;
}

void Game::setHoldingCost(double value)
{
    holdingCost = value;
}

double Game::getBackOrderCost() const
{
    return backorderCost;
}

void Game::setBackOrderCost(double value)
{
    backorderCost = value;
}

int Game::getStartingInventory() const
{
    return startingInventory;
}

void Game::setStartingInventory(int value)
{
    startingInventory = value;
}

int Game::getWeeksToBePlayed() const
{
    return weeksToBePlayed;
}

void Game::setWeeksToBePlayed(int value)
{
    weeksToBePlayed = value;
}

int Game::getCurrentWeek() const
{
    return currentWeek;
}

void Game::setCurrentWeek(int value)
{
    currentWeek = value;
}

int Game::getInfoCode() const
{
    return infoCode;
}

void Game::setInfoCode(int value)
{
    infoCode = value;
}

int Game::getFactoryDelay() const
{
    return factoryDelay;
}

void Game::setFactoryDelay(int value)
{
    factoryDelay = value;
}

int Game::getNOrdersReceived() const
{
    return totalOrdersInWeek;
}

void Game::setNOrdersReceived(int value)
{
    totalOrdersInWeek = value;
}

int Game::getNShipmentsReceived() const
{
    return totalShipmentsInWeek;
}

void Game::setNShipmentsReceived(int value)
{
    totalShipmentsInWeek = value;
}

int Game::getNPlayers() const
{
    return nPlayers;
}

void Game::setNPlayers(int value)
{
    nPlayers = value;
}
