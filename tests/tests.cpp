#include "gtest/gtest.h"
#include "../src/backend/game.h"
#include "../src/backend/instructor.h"
#include "../src/backend/player.h"
#include "../src/backend/playerevent.h"
#include "../src/backend/order.h"
#include "../src/backend/shipment.h"
#include "../src/frontend/mainwindow.h"
#include "../src/frontend/chooseserver.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
/**
* Player Class Tests
*/

/**
* Tests if orderplaced for player
*/

TEST(playerTest, setOrderPlacedTest)
{

    Player p;
    p.setOrderPlaced(true);
    EXPECT_EQ(true, p.isOrderPlaced());
}

TEST(playerTest, getCostTest)
{

    Player p;
    p.setCost(4.5);
    EXPECT_EQ(4.5, p.getCost());
}
/**
* Tests if shipment placed for player
*/

TEST(playerTest, setShipmentPlacedTest)
{

    Player p;
    p.setShipmentPlaced(true);
    EXPECT_EQ(true, p.isShipmentPlaced());
}
/**
* Tests the method for Player's receiveShipment.
*/

TEST(playerTest, receiveShipmentTest)
{
    Player p;
    p.receiveShipment(10);
    EXPECT_EQ(true, p.isShipmentReceived());
    EXPECT_EQ(10, p.getIncomingShipment());

    p.receiveShipment(0);

    EXPECT_EQ(false, p.isShipmentReceived());
    EXPECT_EQ(0, p.getIncomingShipment());
}
/**
* Tests the setter for Player Id.
*/

TEST(playerTest, setPIdTest)
{
    Game g;
    Player pp(&g, 1);

    EXPECT_EQ(1, pp.getRole());
    Player p;
    p.setPId(2);
    EXPECT_EQ(2, p.getPId());
}

/**
* Tests the getter for Player Id.
*/

TEST(playerTest, getPIdTest)
{

    Player p;
    p.setPId(25);
    EXPECT_EQ(25, p.getPId());
}

/**
* Tests the setter for Player Role.
*/

TEST(playerTest, setRoleTest)
{

    Player p;
    p.setRole(1);
    EXPECT_EQ(1, p.getRole());
}

/**
* Tests the getter for Player Role.
*/

TEST(playerTest, getRoleTest)
{

    Player p;
    p.setRole(2);
    EXPECT_EQ(2, p.getRole());
}

/**
* Tests the decreaseInventory() method from the Player class.
*/

TEST(playerTest, decreaseInventoryTest)
{

    Player p;
    int curr_inv = 5;
    p.setInventory(curr_inv);
    p.decreaseInventory(3);
    EXPECT_EQ(2, p.getInventory());
}

/**
* Tests the increaseInventory() method from the Player class.
*/

TEST(playerTest, increaseInventoryTest)
{

    Player p;
    int curr_inv = 3;
    p.setInventory(curr_inv);
    p.increaseInventory(3);
    EXPECT_EQ(curr_inv + 3, p.getInventory());
}

/**
* Tests the getter for Player's Inventory value.
*/

TEST(playerTest, getInventoryTest)
{

    Player p;
    p.setInventory(10000);
    EXPECT_EQ(10000, p.getInventory());
}

/**
* Tests the setter for Player's Inventory value.
*/

TEST(playerTest, setInventoryTest)
{

    Player p;
    p.setInventory(40);
    EXPECT_EQ(40, p.getInventory());
}

/**
* Tests the setter for Player's Demand value.
*/
TEST(playerTest, setDemandTest)
{

    Player p;
    p.setDemand(3);
    EXPECT_EQ(3, p.getDemand());
}

/**
* Tests the getter for Player's Demand value.
*/

TEST(playerTest, getDemandTest)
{

    Player p;
    p.setDemand(4);
    EXPECT_EQ(4, p.getDemand());
}

/**
* Tests the setter for Player's shipmentReceived value.
*/

TEST(playerTest, setshipmentReceivedTest)
{
    Player p;
    p.setShipmentReceived(true);
    EXPECT_EQ(true, p.isShipmentReceived());
}

/**
* Tests the setter for Player's Game.
*/

TEST(playerTest, setGameTest)
{
    Player p;
    Game g;
    p.setGame(&g);
    EXPECT_EQ(&g, p.getGame());
}

/**
* Tests the getter for Player's Game.
*/

TEST(playerTest, getGameTest)
{
    Player p;
    Game g;
    p.setGame(&g);
    EXPECT_EQ(&g, p.getGame());
}

/**
* Tests the setter for Player's IncomingOrder value.
*/

TEST(playerTest, setIncomingOrderTest)
{
    Player p;
    p.setIncomingOrder(10);
    EXPECT_EQ(10, p.getIncomingOrder());
}

/**
* Tests the setter for Player's IncomingShipment value.
*/

TEST(playerTest, setIncomingShipmentTest)
{
    Player p;
    p.setIncomingShipment(10);
    EXPECT_EQ(10, p.getIncomingShipment());
}

/**
* Tests the setter for Player's OutgoingShipment value.
*/

TEST(playerTest, setOutgoingShipmentTest)
{
    Player p;
    p.setOutgoingShipment(10);
    EXPECT_EQ(10, p.getOutgoingShipment());
}

/**
* Tests the setter for Player's TotalCost value.
*/

TEST(playerTest, setTotalCostTest)
{
    Player p;
    p.setTotalCost(10);
    EXPECT_EQ(10, p.getTotalCost());
}

/**
* Tests the method for Player's receiveOrder.
*/

TEST(playerTest, receiveOrderTest)
{
    Player p;
    p.receiveOrder(10);
    EXPECT_EQ(true, p.isOrderReceived());
    EXPECT_EQ(10, p.getIncomingOrder());

    p.receiveOrder(0);

    EXPECT_EQ(false, p.isOrderReceived());
}

/**
* Tests the method for Player's placeShipment.
*/
//placeShipment should call Game's addShipment method
TEST(playerTest, placeShipmentTest)
{
    Game *g = new Game;
    g->setCurrentWeek(1);
    g->setStartingInventory(15);
    Player *sender = new Player;
    Player *receiver = new Player;
    sender->setRole(1);
    receiver->setRole(2);
    g->addPlayer(sender);
    g->addPlayer(receiver);
    sender->placeShipment(5);

    EXPECT_EQ(true, sender->isShipmentPlaced());

    sender->setBackorder(5);
    sender->setInventory(3);
    sender->placeShipment(2);

    EXPECT_EQ(sender->getBackorder(), 4);

    sender->setInventory(0);
    sender->placeShipment(2);

    EXPECT_EQ(sender->isShipmentPlaced(), false);
}

/**
* Tests the method for Player's placeOrder.
*/
TEST(playerTest, placeOrderTest)
{
    Game *g = new Game;
    g->setCurrentWeek(1);
    Player *sender = new Player;
    Player *receiver = new Player;
    sender->setRole(2);
    receiver->setRole(1);
    g->addPlayer(receiver);
    g->addPlayer(sender);
    sender->placeOrder(10);

    EXPECT_EQ(true, sender->isOrderPlaced());

    sender->placeOrder(0);

    EXPECT_EQ(false, sender->isOrderPlaced());
}

/**
* Tests the getter for Player's AvailableShipment.
*/
//getAvailableShipment returns the number of beers that are available for shipment to the next Player
TEST(playerTest, getAvailableShipmentTest)
{
    Player p;
    p.setInventory(5);
    int av = p.getAvailableShipment(8);

    p.setInventory(18);
    int av2 = p.getAvailableShipment(8);
    EXPECT_EQ(5, av);
    EXPECT_EQ(8, av2);
}

/**
* Tests the getter for Player's OrderReceived.
*/

TEST(playerTest, isOrderReceivedTest)
{
    Player p;
    p.setOrderReceived(true);
    EXPECT_EQ(true, p.isOrderReceived());
}

/**
* Tests the setter for Player's OrderReceived.
*/

TEST(playerTest, setOrderReceivedTest)
{
    Player p;
    p.setOrderReceived(false);
    EXPECT_EQ(false, p.isOrderReceived());
}

/**
* Tests the getter for Player's ShipmentReceived.
*/

TEST(playerTest, isShipmentReceivedTest)
{
    Player p;
    p.setShipmentReceived(true);
    EXPECT_EQ(true, p.isShipmentReceived());
}

/**
* Tests the setter for Player's ShipmentReceived.
*/

TEST(playerTest, setShipmentReceivedTest)
{
    Player p;
    p.setShipmentReceived(false);

    EXPECT_EQ(false, p.isShipmentReceived());
}
/*
* Game Class Tests
*/

// Jose's test cases for Player class

/**
* Tests the getter for the vector of every weeks' demand
*/

TEST(playerTest, getDemandEveryWeekTest)
{
    Player p;
    vector<int> demands = {1, 9, 8};
    p.setDemand_every_week(demands);
    EXPECT_EQ(demands, p.getDemand_every_week());
}

/**
* Tests the setter for the vector of every weeks' demand
*/

TEST(playerTest, setDemandEveryWeekTest)
{
    Player p;
    vector<int> demands = {15, 2, 3};
    p.setDemand_every_week(demands);
    EXPECT_EQ(demands, p.getDemand_every_week());
}

/**
* Tests the getter for the vector of every weeks' backlog
*/

TEST(playerTest, getBacklogEveryWeekTest)
{
    Player p;
    vector<int> bgs = {1, 9, 8};
    p.setBacklog_every_week(bgs);
    EXPECT_EQ(bgs, p.getBacklog_every_week());
}

/**
* Tests the setter for the vector of every weeks' backlog
*/

TEST(playerTest, setBacklogEveryWeekTest)
{
    Player p;
    vector<int> bgs = {15, 2, 3};
    p.setBacklog_every_week(bgs);
    EXPECT_EQ(bgs, p.getBacklog_every_week());
}

/**
* Tests the getter for the vector of every weeks' inventory
*/

TEST(playerTest, getInventoryEveryWeekTest)
{
    Player p;
    vector<int> invs = {0, 1, 2};
    p.setInventory_every_week(invs);
    EXPECT_EQ(invs, p.getInventory_every_week());
}

/**
* Tests the setter for the vector of every weeks' inventory
*/

TEST(playerTest, setInventoryEveryWeekTest)
{
    Player p;
    vector<int> invs = {5, 22, 6};
    p.setInventory_every_week(invs);
    EXPECT_EQ(invs, p.getInventory_every_week());
}

TEST(playerTest, setReceivedEveryWeekTest)
{

    Player p;
    vector<int> invs = {5, 22, 6};
    p.setReceived_every_week(invs);
    EXPECT_EQ(invs, p.getReceived_every_week());
}

/**
* Tests the getter for the vector of every weeks' cost
*/

TEST(playerTest, getCostEveryWeekTest)
{
    Player p;
    vector<double> costs = {1.1, 8.9, 7.2};
    p.setCost_every_week(costs);
    EXPECT_EQ(costs, p.getCost_every_week());
}

/**
* Tests the setter for the vector of every weeks' cost
*/

TEST(playerTest, setCostEveryWeekTest)
{
    Player p;
    vector<double> costs = {0.9, 22.5, 31.3};
    p.setCost_every_week(costs);
    EXPECT_EQ(costs, p.getCost_every_week());
}

/**
* Tests the getter for the vector of every weeks' delivered
*/

TEST(playerTest, getDeliveredEveryWeekTest)
{
    Player p;
    vector<int> delivered = {0, 1, 2};
    p.setDelivered_every_week(delivered);
    EXPECT_EQ(delivered, p.getDelivered_every_week());
}

/**
* Tests the setter for the vector of every weeks' delivered
*/

TEST(playerTest, setDeliveredEveryWeekTest)
{
    Player p;
    vector<int> delivered = {5, 22, 6};
    p.setDelivered_every_week(delivered);
    EXPECT_EQ(delivered, p.getDelivered_every_week());
}

/**
* Tests the pushing back of the argument into demand vector
*/

TEST(playerTest, addDemandToVector)
{
    Player p;
    p.add_demand_to_vector(1);
    p.add_demand_to_vector(6);
    p.add_demand_to_vector(12);
    vector<int> dvector = {0, 1, 6, 12};
    EXPECT_EQ(dvector, p.getDemand_every_week());
}

/**
* Tests the pushing back of the argument into backlog vector
*/

TEST(playerTest, addBacklogToVector)
{
    Player p;
    p.add_backlog_to_vector(10);
    p.add_backlog_to_vector(76);
    p.add_backlog_to_vector(3);
    vector<int> bvector = {0, 10, 76, 3};
    EXPECT_EQ(bvector, p.getBacklog_every_week());
}

/**
* Tests the pushing back of the argument into inventory vector
*/

TEST(playerTest, addInventoryToVector)
{
    Player p;
    p.add_inventory_to_vector(4);
    p.add_inventory_to_vector(2);
    p.add_inventory_to_vector(3);
    vector<int> ivector = {0, 4, 2, 3};
    EXPECT_EQ(ivector, p.getInventory_every_week());
}

/**
* Tests the pushing back of the argument into cost vector
*/

TEST(playerTest, addCostToVector)
{
    Player p;
    p.add_cost_to_vector(4.2);
    p.add_cost_to_vector(2.2);
    p.add_cost_to_vector(3.1);
    vector<double> cvector = {0, 4.2, 2.2, 3.1};
    EXPECT_EQ(cvector, p.getCost_every_week());
}

/**
* Tests the pushing back of the argument into delivered vector
*/

TEST(playerTest, addDeliveredToVector)
{
    Player p;
    p.add_delivered_to_vector(4);
    p.add_delivered_to_vector(2);
    p.add_delivered_to_vector(3);
    vector<int> devector = {0, 4, 2, 3};
    EXPECT_EQ(devector, p.getDelivered_every_week());
}

// end Jose's test cases

TEST(gameTest, getConsumerDemandForWeekTest)
{
    Game g;
    vector<int> d = {3, 4, 5};
    g.setConsumerDemandPerWeek(d);

    EXPECT_EQ(3, g.getConsumerDemandForWeek(1));

    EXPECT_EQ(-1, g.getConsumerDemandForWeek(4));
}

TEST(gameTest, startGameTest)
{
    Game t;
    t.setTotal_cost(5.5);

    EXPECT_EQ(5.5, t.getTotal_cost());
    Game g;
    g.setWeeksToBePlayed(3);
    g.setOrderDelay(0);
    g.setFactoryDelay(1);
    g.setNPlayers(4);
    g.setFactoryDelay(0);
    g.setConsumerDemandPerWeek({3, 4, 5});
    g.setStartingInventory(10);
    g.setHoldingCost(1);
    g.setBackOrderCost(1);

    map<int, vector<int>> order_map;
    order_map[0] = {2, 3, 15, 5};
    order_map[1] = {8, 10, 5, 4};
    order_map[2] = {0, 5, 4, 2};
    g.testing_input_outgoing_order = order_map;

    g.testing_mode = true;

    g.startGame();

    EXPECT_EQ(25, g.getTotal_cost());
}

/**
* test setter for shipment delay
*/
TEST(gameTest, setShipmentDelayTest)
{

    Game g;
    g.setShipmentDelay(3);
    EXPECT_EQ(3, g.getShipmentDelay());
}

/**
* test getter for shipment delay
*/
TEST(gameTest, getShipmentDelayTest)
{

    Game g;
    g.setShipmentDelay(8);
    EXPECT_EQ(8, g.getShipmentDelay());
}

/**
* test setter for order delay
*/
TEST(gameTest, setOrderDelayTest)
{

    Game g;
    g.setOrderDelay(3);
    EXPECT_EQ(3, g.getOrderDelay());
}

/**
* test getter for order delay
*/
TEST(gameTest, getOrderDelayTest)
{

    Game g;
    g.setOrderDelay(10);
    EXPECT_EQ(10, g.getOrderDelay());
}

/**
* test setter for game ID
*/
TEST(gameTest, setGIdTest)
{

    Game g;
    g.setGId(34);
    EXPECT_EQ(34, g.getGId());
}

/**
* test getter for game ID
*/
TEST(gameTest, getGIdTest)
{

    Game g;
    g.setGId(6);
    EXPECT_EQ(6, g.getGId());
}

/**
* test setter for instructor ID
*/
TEST(gameTest, setInstrIdTest)
{

    Game g;
    g.setInstrId(20);
    EXPECT_EQ(20, g.getInstrId());
}

/**
* test getter for instructor ID
*/
TEST(gameTest, getInstrIdTest)
{

    Game g;
    g.setInstrId(2);
    EXPECT_EQ(2, g.getInstrId());
}

/**
* test setter for factory ID
*/
TEST(gameTest, setPFactIdTest)
{

    Game g;
    g.setPFactId(100);
    EXPECT_EQ(100, g.getPFactId());
}

/**
* test getter for factory ID
*/
TEST(gameTest, getPFactIdTest)
{

    Game g;
    g.setPFactId(1030);
    EXPECT_EQ(1030, g.getPFactId());
}

/**
* test getter for distributor ID
*/
TEST(gameTest, getPDistributorIdTest)
{

    Game g;
    g.setPDistributorId(56);
    EXPECT_EQ(56, g.getPDistributorId());
}

/**
* test setter for distributor ID
*/
TEST(gameTest, setPDistributorIdTest)
{

    Game g;
    g.setPDistributorId(45);
    EXPECT_EQ(45, g.getPDistributorId());
}

/**
* test getter for wholesaler ID
*/
TEST(gameTest, getPWholesalerIdTest)
{

    Game g;
    g.setPWholesalerId(56);
    EXPECT_EQ(56, g.getPWholesalerId());
}

/**
* test setter for wholesaler ID
*/
TEST(gameTest, setPWholesalerIdTest)
{

    Game g;
    g.setPWholesalerId(12);
    EXPECT_EQ(12, g.getPWholesalerId());
}

/**
* test setter for retailer ID
*/
TEST(gameTest, setPRetailerIdTest)
{

    Game g;
    g.setPRetailerId(24);
    EXPECT_EQ(24, g.getPRetailerId());
}

/**
* test getter for retailer ID
*/
TEST(gameTest, getPRetailerIdTest)
{

    Game g;
    g.setPRetailerId(24);
    EXPECT_EQ(24, g.getPRetailerId());
}

/**
* test advanceWeek method
*/
TEST(gameTest, advanceWeekTest)
{

    Game g;
    int currweek = g.getCurrentWeek();
    EXPECT_EQ(currweek + 1, g.advanceWeek());
}

/**
* test setter for weeks to be played
*/
TEST(gameTest, setWeeksToBePlayedTest)
{

    Game g;
    g.setWeeksToBePlayed(2);
    EXPECT_EQ(2, g.getWeeksToBePlayed());
}

/**
* test getter for weeks to be played
*/
TEST(gameTest, getWeeksToBePlayedTest)
{

    Game g;
    EXPECT_EQ(26, g.getWeeksToBePlayed()); //checking default value
    g.setWeeksToBePlayed(2);
    EXPECT_EQ(2, g.getWeeksToBePlayed());
}

/**
* test setter for information sharing code
*/
TEST(gameTest, setInfoCodeTest)
{

    Game g;
    g.setInfoCode(3);
    EXPECT_EQ(3, g.getInfoCode());
}

/**
* test getter for information sharing code
*/
TEST(gameTest, getInfoCodeTest)
{

    Game g;
    g.setInfoCode(3);
    EXPECT_EQ(3, g.getInfoCode());
}

/**
* test setter for holding cost
*/
TEST(gameTest, setHoldingCostTest)
{

    Game g;
    g.setHoldingCost(6.3);
    EXPECT_EQ(6.3, g.getHoldingCost());
}

/**
* test getter for holding cost
*/
TEST(gameTest, getHoldingCostTest)
{

    Game g;
    EXPECT_EQ(0.5, g.getHoldingCost()); //checking default value
    g.setHoldingCost(9);
    EXPECT_EQ(9, g.getHoldingCost());
}

/**
* test setter for starting inventory
*/
TEST(gameTest, setStartingInventoryTest)
{

    Game g;
    g.setStartingInventory(4);
    EXPECT_EQ(4, g.getStartingInventory());
}

/**test getter for starting inventory
*
*/
TEST(gameTest, getStartingInventoryTest)
{

    Game g;
    EXPECT_EQ(12, g.getStartingInventory()); //checking default value
    g.setStartingInventory(14);
    EXPECT_EQ(14, g.getStartingInventory());
}

/**
* test getter for backorder cost
*/
TEST(gameTest, getBackOrderCostTest)
{

    Game g;
    g.setBackOrderCost(5.7);
    EXPECT_EQ(5.7, g.getBackOrderCost());
}

/**
* test getter for current week
*/
TEST(gameTest, getCurrentWeekTest)
{

    Game g;
    EXPECT_EQ(0, g.getCurrentWeek()); //checking default value
    g.setCurrentWeek(5);
    EXPECT_EQ(5, g.getCurrentWeek());
}

/**
* test setter for current week
*/
TEST(gameTest, setCurrentWeekTest)
{

    Game g;
    g.setCurrentWeek(1);
    EXPECT_EQ(1, g.getCurrentWeek());
}
/**
* Test generation of passwords
*/
TEST(gameTest, generatePasswordsTest)
{
    Game g;

    // set list of possible chars
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string alphan(alphanum);

    // get generated passwods
    vector<string> passwords = g.generatePasswords();

    // assert there are 4 passwords
    EXPECT_EQ(passwords.size(), 4);

    // assert each password is 10 chars long
    for (int i = 0; i < 4; i++)
    {
        EXPECT_EQ(passwords[i].length(), 10);
    }

    // assert that each password contains only allowed chars
    for (string const &s : passwords)
    {
        for (char const &c : s)
        {
            EXPECT_NE(alphan.find(c), string::npos);
        }
    }
}
/*
TEST(gameTest, showGameStatusTest)
{
    Game g;
    g.setNPlayers(4);
    g.setGId(101);
    g.setCurrentWeek(1);

    Game e;
    e.setNPlayers(4);
    e.setGId(567);
    e.setCurrentWeek(1);

    Instructor i;
    i.setGame(g);
    i.setGame(e);

    i.showGameStatus();

    vector<Game> games = i.getGame();
    vector<int> gIDs;
    vector<int> currentWeeks;
    for (unsigned long i = 0; i < games.size(); i++)
    {
        int id = games[i].getGId();
        int current_week = games[i].getCurrentWeek();

        gIDs.push_back(id);
        currentWeeks.push_back(current_week);
    }

    EXPECT_EQ(2, gIDs.size());
    EXPECT_EQ(2, currentWeeks.size());
}*/
/**
* Tests the setter for Game's NumberOfPlayers.
*/

TEST(gameTest, setNPlayersTest)
{
    Game p;
    p.setNPlayers(3);
    EXPECT_EQ(3, p.getNPlayers());
}

TEST(gameTest, setFactoryDelayTest)
{
    Game p;
    p.setFactoryDelay(4);
    EXPECT_EQ(4, p.getFactoryDelay());
}
/**
* Tests the setter for Game's Players.
*/

TEST(gameTest, setPlayersTest)
{
    Player *p = new Player;
    Player *q = new Player;

    Game g;
    g.setPlayers({p, q});

    EXPECT_EQ(2, g.getPlayers().size());
}

/**
* Tests the method for Game's executeOrdersForCurrentWeek.
*/
//In executeOrdersForCurrentWeek, the Order objects in the map ordersToBeExecuted are executed (the method
// executeOrder for each object is called)
TEST(gameTest, executeOrdersForCurrentWeekTest)
{
    Game g;
    g.setNPlayers(4);
    g.setCurrentWeek(1);
    g.setShipmentDelay(0);
    g.setOrderDelay(0);
    g.setFactoryDelay(0);
    g.setConsumerDemandPerWeek({3});

    Player r, w, d, f;
    f.setRole(1);
    d.setRole(2);
    w.setRole(3);
    r.setRole(4);
    g.addPlayer(&f);
    g.addPlayer(&d);
    g.addPlayer(&w);
    g.addPlayer(&r);
    f.placeOrder(2);
    d.placeOrder(4);
    w.placeOrder(5);
    r.placeOrder(2);

    g.executeOrdersForCurrentWeek();
    EXPECT_EQ(3, r.getIncomingOrder());
    EXPECT_EQ(2, w.getIncomingOrder());
    EXPECT_EQ(5, d.getIncomingOrder());
    EXPECT_EQ(4, f.getIncomingOrder());

    g.setCurrentWeek(1);
    g.setOrderDelay(2);
    g.executeOrdersForCurrentWeek();

    EXPECT_EQ(6, w.getIncomingOrder());

    Game h;
    h.setCurrentWeek(1);
    h.setFactoryDelay(1);
    Player ff;
    ff.setRole(2);
    h.addPlayer(&ff);

    h.executeOrdersForCurrentWeek();
    EXPECT_EQ(0, ff.getIncomingOrder());
}

/**
* Tests the method for Game's executeShipmentsForCurrentWeek.
*/
//In executeShipmentsForCurrentWeek, the Shipment objects in the map setShipmentsToBeExecuted are executed (the method
// executeShipment for each object is called)
TEST(gameTest, executeShipmentsForCurrentWeekTest)
{
    Game g;
    g.setNPlayers(4);
    g.setCurrentWeek(1);
    g.setShipmentDelay(0);
    g.setOrderDelay(0);
    g.setFactoryDelay(0);
    g.setConsumerDemandPerWeek({3});
    g.setStartingInventory(15);

    Player r, w, d, f;
    f.setRole(1);
    d.setRole(2);
    w.setRole(3);
    r.setRole(4);

    f.setIncomingOrder(4);
    d.setIncomingOrder(5);
    w.setIncomingOrder(2);
    r.setIncomingOrder(3);
    g.addPlayer(&f);
    g.addPlayer(&d);
    g.addPlayer(&w);
    g.addPlayer(&r);

    f.placeOrder(2);
    d.placeOrder(4);
    w.placeOrder(5);
    r.placeOrder(2);

    w.setInventory(1);

    g.executeShipmentsForCurrentWeek();

    EXPECT_EQ(1, r.getIncomingShipment());
    EXPECT_EQ(5, w.getIncomingShipment());
    EXPECT_EQ(4, d.getIncomingShipment());
    EXPECT_EQ(2, f.getIncomingShipment());

    g.setShipmentDelay(3);
    g.executeShipmentsForCurrentWeek();

    EXPECT_EQ(false, w.isShipmentReceived());

    Game h;
    h.setFactoryDelay(1);

    Player ff;
    h.addPlayer(&ff);
    h.executeShipmentsForCurrentWeek();
    EXPECT_EQ(0, ff.getIncomingShipment());
}

TEST(gameTest, getConsumerOrderForWeekTest)
{

    Game g;
    g.setConsumerDemandPerWeek({1, 2});
    g.setCurrentWeek(1);

    EXPECT_EQ(1, g.getConsumerOrderForWeek());
    EXPECT_EQ(2, (g.getConsumerDemandPerWeek()).size());
}

TEST(gameTest, getNOrdersReceivedTest)
{
    Game g;
    g.setNOrdersReceived(50);
    EXPECT_EQ(50, g.getNOrdersReceived());
    EXPECT_EQ(50, g.getTotalOrdersInWeek());
}

TEST(gameTest, getNShipmentsReceivedTest)
{
    Game g;
    g.setNShipmentsReceived(4);
    EXPECT_EQ(4, g.getNShipmentsReceived());

    EXPECT_EQ(4, g.getTotalShipmentsInWeek());
}

TEST(gameTest, setTotalShipmentsInWeekTest)
{
    Game g;
    g.setTotalShipmentsInWeek(5);

    EXPECT_EQ(5, g.getTotalShipmentsInWeek());
}

TEST(gameTest, getTotalOrderedInweekTest)
{
    Game g;
    g.setTotalOrdersInWeek(6);
    EXPECT_EQ(6 + 0, g.getTotalOrdersInWeek());
}

TEST(gameTest, testingModesTest)
{
    Game g;
    g.setTesting_mode(false);

    EXPECT_EQ(false, g.getTesting_mode());

    vector<int> vec = {1, 2, 3, 4};
    map<int, vector<int>> t_map;
    t_map[0] = vec;
    g.setTesting_input_outgoing_order(t_map);
    EXPECT_EQ(t_map, g.getTesting_input_outgoing_order());
}

TEST(gameTest, gameInsTest)
{
    Game g(5);
    EXPECT_EQ(5, g.getInstrId());
}

TEST(gameTest, gameParamTest)
{
    Game g(1, 1, 1, 1, 1, 1, 1);

    EXPECT_EQ(1, g.getBackOrderCost());
}

/**
* Tests the method for Game's updatePlayerInventories.
*/

TEST(gameTest, updatePlayerInventoriesTest)
{
    Game g;
    g.setStartingInventory(10);
    g.setNPlayers(4);

    Player r, w, d, f;
    f.setRole(1);
    d.setRole(2);
    w.setRole(3);
    r.setRole(4);
    f.setBackorder(0);
    f.setShipmentReceived(true);
    d.setShipmentReceived(true);
    w.setShipmentReceived(true);
    r.setShipmentReceived(true);
    f.setIncomingShipment(4);
    d.setIncomingShipment(5);
    w.setIncomingShipment(2);
    r.setIncomingShipment(3);
    g.addPlayer(&f);
    g.addPlayer(&d);
    g.addPlayer(&w);
    g.addPlayer(&r);

    g.updatePlayerInventories();

    EXPECT_EQ(14, f.getInventory());

    f.setIncomingOrder(2);
    d.setIncomingOrder(3);
    w.setIncomingOrder(4);
    r.setIncomingOrder(4);

    g.updatePlayerInventories();

    EXPECT_EQ(10 + 4 - 2, f.getInventory());
    EXPECT_EQ(10 + 5 - 3, d.getInventory());
    EXPECT_EQ(10 + 2 - 4, w.getInventory());
    EXPECT_EQ(10 + 3 - 4, r.getInventory());

    EXPECT_EQ(0, f.getBackorder());

    f.setInventory(2);
    f.setIncomingShipment(0);
    f.setIncomingOrder(5);

    EXPECT_EQ(2, f.getInventory());
    g.updatePlayerInventories();
    EXPECT_EQ(0, f.getInventory());
    EXPECT_EQ(3, f.getBackorder());
}

/**
* Tests the method for Game's addOrder.
*/
// In addOrder, an object of class Order is created and put into the map setOrdersToBeExecuted
TEST(gameTest, addOrderTest)
{
    Game g;
    Player sender, receiver;
    g.setCurrentWeek(1);
    g.setOrderDelay(0);
    g.setShipmentDelay(0);
    sender.setRole(2);
    receiver.setRole(1);
    g.addPlayer(&receiver);
    g.addPlayer(&sender);
    g.addOrder(sender.getRole(), 6);
    map<int, vector<Order>> map_order = g.getOrdersToBeExecuted();
    vector<Order> order_list_current_week = map_order[0];
    Order sender_order = order_list_current_week[0];
    EXPECT_EQ(1, g.getOrdersToBeExecuted().size());
    EXPECT_EQ(6, sender_order.getNumberOfBeers());
}

/**
* Tests the method for Game's addShipment.
*/
// In addShipment, an object of class Shipment is created and put into the map setShipmentsToBeExecuted
TEST(gameTest, addShipmentTest)
{
    Game g;
    g.setOrderDelay(0);
    g.setShipmentDelay(0);
    g.setCurrentWeek(1);
    Player f, d;
    f.setRole(1);
    d.setRole(2);

    g.addPlayer(&f);
    g.addPlayer(&d);
    g.addShipment(f.getRole(), 6);

    map<int, vector<Shipment>> map_ship = g.getShipmentsToBeExecuted();
    vector<Shipment> ship_list_current_week = map_ship[0];
    Shipment sender_ship = ship_list_current_week[0];

    EXPECT_EQ(1, g.getShipmentsToBeExecuted().size());
    EXPECT_EQ(6, sender_ship.getNumberOfBeers());

    Player r;
    r.setRole(4);

    g.addPlayer(&r);
    g.addShipment(r.getRole(), 4);

    map_ship = g.getShipmentsToBeExecuted();

    ship_list_current_week = map_ship[0];
    sender_ship = ship_list_current_week[1];

    EXPECT_EQ(4, sender_ship.getNumberOfBeers());

    Player wrong;
    wrong.setRole(5);

    EXPECT_DEATH(g.addShipment(wrong.getRole(), 5), "Null pointer\n");
}

TEST(gameTest, setShipmentsToBeExecutedTest)
{
    Game g;
    Shipment s;

    vector<Shipment> s_list;
    s_list.push_back(s);
    map<int, vector<Shipment>> map_ship;
    map_ship[0] = s_list;

    g.setShipmentsToBeExecuted(map_ship);

    EXPECT_EQ(1, g.getShipmentsToBeExecuted().size());
}

TEST(gameTest, setOrdersToBeExecutedTest)
{
    Game g;
    Order s;

    vector<Order> o_list;
    o_list.push_back(s);
    map<int, vector<Order>> map_order;
    map_order[0] = o_list;

    g.setOrdersToBeExecuted(map_order);

    EXPECT_EQ(1, g.getOrdersToBeExecuted().size());
}
/**
* Tests the method for Game's addPlayer.
*/

TEST(gameTest, addPlayerTest)
{
    Player p;
    Game g;

    g.addPlayer(&p);

    EXPECT_EQ(1, g.getPlayers().size());
    EXPECT_EQ(&p, (g.getPlayers())[0]);

    g.addPlayer(&p);

    EXPECT_EQ(2, g.getPlayers().size());
}

/**
* Tests the getter for Game's Downstream.
*/

TEST(gameTest, getDownstreamTest)
{
    Game g;
    Player f, d, w, r;
    f.setRole(1);
    d.setRole(2);
    w.setRole(3);
    r.setRole(4);

    g.addPlayer(&f);
    g.addPlayer(&d);
    g.addPlayer(&w);
    g.addPlayer(&r);

    Player *downstream = g.getDownstream(w.getRole());
    EXPECT_EQ(&r, downstream);

    downstream = g.getDownstream(r.getRole());

    EXPECT_EQ(NULL, downstream);
}

/**
* Tests the getter for Game's Upstream.
*/

TEST(gameTest, getUpstreamTest)
{
    Game g;
    Player f, d;
    f.setRole(1);
    d.setRole(2);

    g.addPlayer(&f);
    g.addPlayer(&d);

    Player *upstream = g.getUpstream(f.getRole());

    EXPECT_EQ(NULL, upstream);

    upstream = g.getUpstream(d.getRole());

    EXPECT_EQ(&f, upstream);
}

/**
* Tests the method for Order's executeOrder.
*/

TEST(orderTest, executeOrderTest)
{
    Player receiver;
    Order o(1, 1, 2, 1, 1, 5, &receiver);
    o.executeOrder();

    EXPECT_EQ(5, receiver.getIncomingOrder());

    Order l;
    l.setNumberOfBeers(20);
    EXPECT_EQ(20, l.getNumberOfBeers());
}

/**
* Tests the method for Shipment's executeShipment.
*/

TEST(shipmentTest, executeShipmentTest)
{
    Player receiver;

    Shipment s(1, 1, 2, 1, 1, 5, &receiver);
    s.executeShipment();

    EXPECT_EQ(5, receiver.getIncomingShipment());

    Shipment l;

    l.setNumberOfBeers(20);
    EXPECT_EQ(20, l.getNumberOfBeers());
}

/**
* Tests the getter for PlayerEvent's Game ID.
*/

TEST(playerEventTest, getGIdTest)
{
    PlayerEvent e;

    e.setGId(2);

    EXPECT_EQ(2, e.getGId());

    Player receiver;

    PlayerEvent x(5, 1, 2, 3, 5, 10, &receiver);

    EXPECT_EQ(&receiver, x.getReceiver());
}

/**
* Tests the Setter for PlayerEvent's Game ID.
*/

TEST(playerEventTest, setGIdTest)
{
    PlayerEvent e;

    e.setGId(2);

    EXPECT_EQ(2, e.getGId());
}

/**
* Tests the getter for PlayerEvent's FromPlayerId.
*/

TEST(playerEventTest, getFromPlayerIdTest)
{
    PlayerEvent e;

    e.setFromPlayerId(2);

    EXPECT_EQ(2, e.getFromPlayerId());
}

/**
* Tests the getter for PlayerEvent's ToPlayerId.
*/

TEST(playerEventTest, getToPlayerIdTest)
{
    PlayerEvent e;

    e.setToPlayerId(2);

    EXPECT_EQ(2, e.getToPlayerId());
}

/**
* Tests the getter for PlayerEvent's OrderedInWeek.
*/

TEST(playerEventTest, getOrderedInWeekTest)
{
    PlayerEvent e;

    e.setOrderedInWeek(2);

    EXPECT_EQ(2, e.getOrderedInWeek());
}

/**
* Tests the getter for PlayerEvent's ShippedInWeek.
*/

TEST(playerEventTest, getShippedInWeekTest)
{
    PlayerEvent e;
    e.setShippedInWeek(4);

    EXPECT_EQ(4, e.getShippedInWeek());
}

/**
* Tests the getter for PlayerEvent's NumberOfBeers.
*/

TEST(playerEventTest, getNumberOfBeersTest)
{
    PlayerEvent e;

    e.setNumberOfBeers(2);

    EXPECT_EQ(2, e.getNumberOfBeers());
    Player p;
    PlayerEvent f(1, 1, 1, 1, 1, 1, &p);

    EXPECT_EQ(1, f.getFromPlayerId());
    //int fromPlayerId, int toPlayerId, int orderWeek, int shipWeek, int no_beers, Player *receiver)
}

/**
* Tests the getter for PlayerEvent's Receiver.
*/

TEST(playerEventTest, getReceiverTest)
{
    PlayerEvent e;
    Player p;
    e.setReceiver(&p);

    EXPECT_EQ(&p, e.getReceiver());
}

TEST(instructorTest, instructorDefaultTest)
{
    Instructor i;
    EXPECT_EQ(0, i.getInstrId());
}
TEST(instructorTest, createGameTest)
{
    Instructor i;
    i.createGame();
    EXPECT_EQ(1, i.getGames().size());

    Instructor ii;
    ii.createGames(3);
    EXPECT_EQ(3, ii.getGames().size());
}

TEST(instructorTest, setGamesTest)
{
    Instructor i;
    std::vector<Game *> games_list;
    Game *g = new Game(1, 2, 2, 2, 26, 12, 2);
    games_list.push_back(g);
    i.setGames(games_list);

    EXPECT_EQ(1, (i.getGames()).size());
}

TEST(instructorTest, setInstrIdTest)
{

    Instructor i;
    i.setInstrId(2020);
    EXPECT_EQ(2020, i.getInstrId());
}

TEST(instructorTest, getInstrIdTest)
{

    Instructor i;
    i.setInstrId(30);
    EXPECT_EQ(30, i.getInstrId());
}

TEST(instructorTest, setInstrEmailTest)
{

    Instructor i;
    i.setInstrEmail("hi.there@jacobs-university.de");
    EXPECT_EQ("hi.there@jacobs-university.de", i.getInstrEmail());
}

TEST(instructorTest, getInstrEmailTest)
{

    Instructor i;
    i.setInstrEmail("hi.again@jacobs-university.de");
    std::string email = "hi.again@jacobs-university.de";
    EXPECT_EQ(email, i.getInstrEmail());
}

TEST(instructorTest, setInstrPasswordTest)
{

    Instructor i;
    i.setInstrPassword("superstrongpassword");
    EXPECT_EQ("superstrongpassword", i.getInstrPassword());
}

TEST(instructorTest, getInstrPasswordTest)
{

    Instructor i;
    i.setInstrPassword("weakpassword");
    EXPECT_EQ("weakpassword", i.getInstrPassword());
}

TEST(frontend, instructordialog)
{
	MainWindow w;
	Instructor i;
	InstructorDialog *ind = new InstructorDialog(&w, &i);
	EXPECT_EQ(ind->validation_check(), true);
	delete ind;
}

TEST(frontend, gamescreen)
{
	MainWindow w;
	Game g;
	Player p;
	PlayerDialog *pld = new PlayerDialog(&w, g, &p);
	ClientRequest *clr = new ClientRequest(&w, &p);

	GameScreen *gs = new GameScreen(&w, &g, &p, clr);
	gs->update_ui_parameters(1, 2, 3, 4, 5, 6);

	gs->setPlayer_week_in_game(26);
	EXPECT_EQ(gs->getPlayer_week_in_game(), 26);



	delete gs;
	delete pld;
	delete clr;
}



TEST(frontend, playerdialog)
{
	MainWindow w;
	Game g;
	Player p;
	PlayerDialog *pld = new PlayerDialog(&w, g, &p);
	ClientRequest *clr = new ClientRequest(&w, &p);
	pld->setClient(clr);
	EXPECT_EQ(pld->getClient(), clr);
	pld->setPlayer(&p);
	EXPECT_EQ(pld->getPlayer(), &p);
	pld->enable_role_buttons(true);

	delete pld;
	delete clr;
}

TEST(frontend, clientrequest)
{

	ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());


	MainWindow w;
	Player p;
	//PlayerDialog *pld = new PlayerDialog(&w, g, &p);
    Game gu;
    chooseServer *che = new chooseServer(&w, &gu);

	ClientRequest *clr = new ClientRequest(&w, &p);
    QHostAddress addr;
    addr.setAddress("127.0.0.3");
    QString port = "8888";
    uint port_no = port.toUInt(Q_NULLPTR, 10);



   
    che->startListening(addr, port_no);
    clr->requestConnection(addr, port_no);
    clr->clientSendMessageToServer();

    che->tcpServerConnection = new QTcpSocket();
    che->tcpServerConnection->setProxy(QNetworkProxy::NoProxy);
    che->tcpServerConnection->connectToHost(addr, port_no);
    che->tcpClients.push_back(che->tcpServerConnection);
    clr->setTcpServerConnection(che->tcpServerConnection);
    EXPECT_EQ(che->tcpServerConnection, clr->getTcpServerConnection());

    QString b = "7";
    //EXPECT_EQ(clr->check_role_available(b), 1);
    clr->showGame();
    clr->send_order(b, b);
    QStringList c = {"7"};
    EXPECT_EQ(clr->parse_key_value(b), c);

    QStringList my_list = {"1", "2", "3", "4", "5", "1", "2", "3", "4", "5", "1", "2", "3", "4", "5"};
    clr->advance_round(1, my_list);
    clr->displayServerMessage();
    clr->disconnect();
    
    delete che;
    delete clr;

    std::cout.rdbuf(p_cout_streambuf);
    EXPECT_EQ(oss.str(), "");
   
}


TEST(frontend, chooseserver)
{
    //char beergame[] = {'g','a','m','e'};
    //char *argv[] = {beergame};
    //int argc = 1 ;
    //QApplication a(argc, argv);
    MainWindow w;
    Game gu;
    chooseServer *che = new chooseServer(&w, &gu);
    QString x = "Retailer chosen";
    QByteArray q = x.toLocal8Bit();

    QHostAddress addr;
    addr.setAddress("127.0.0.3");
    QString port = "8888";
    uint port_no = port.toUInt(Q_NULLPTR, 10);

    che->startListening(addr, port_no);

    che->tcpServerConnection = new QTcpSocket();
    che->tcpServerConnection->setProxy(QNetworkProxy::NoProxy);
    che->tcpServerConnection->connectToHost(addr, port_no);
    che->tcpClients.push_back(che->tcpServerConnection);

    EXPECT_EQ(che->check_unique_player_role(q), true);
    x = "Wholesaler chosen";
    q = x.toLocal8Bit();
    EXPECT_EQ(che->check_unique_player_role(q), true);
    che->unique_wholesaler_id = 1;
    EXPECT_EQ(che->check_unique_player_role(q), true);
    x = "Distributor chosen";
    q = x.toLocal8Bit();
    EXPECT_EQ(che->check_unique_player_role(q), true);
    che->unique_distributor_id = 1;
    EXPECT_EQ(che->check_unique_player_role(q), true);
    x = "Factory chosen";
    q = x.toLocal8Bit();
    EXPECT_EQ(che->check_unique_player_role(q), true);
    che->unique_factory_id = 1;
    EXPECT_EQ(che->check_unique_player_role(q), true);
    x = "Something stupid";
    q = x.toLocal8Bit();
    EXPECT_EQ(che->check_unique_player_role(q), false);

    QString surprise = "weeks: 4 orderds: 10";
    QStringList first_list_of_surpises = {"weeks:", "4", "orderds:", "10"};
    EXPECT_EQ(che->parse_key_value(surprise), first_list_of_surpises);
    QStringList second_list_of_surpises = surprise.split(QRegExp(" "));
    EXPECT_EQ(che->parse_key_value(surprise), second_list_of_surpises);


    QStringList retailer_u = {"RETAILER", "a", "4", "c", "12"};
    EXPECT_EQ(che->update_order_info(retailer_u), false);

    QStringList wholesaler_u = {"WHOLESALER", "a", "4", "c", "6"};
    EXPECT_EQ(che->update_order_info(wholesaler_u), false);

    QStringList distrib_u = {"DISTRIBUTOR", "a", "4", "c", "5"};
    EXPECT_EQ(che->update_order_info(distrib_u), false);

    QStringList fact_u = {"FACTORY", "a", "4", "c", "100"};
    EXPECT_EQ(che->update_order_info(fact_u), true);


    che->create_players_game(); // updates current week, setting it to 1
    EXPECT_EQ(gu.getCurrentWeek(), 1);

    ostringstream oss;
    streambuf* p_cout_streambuf = std::cout.rdbuf();
    cout.rdbuf(oss.rdbuf());
    che->process_orders_this_week(); // we cannot test void functions, but can test output messages
    std::cout.rdbuf(p_cout_streambuf);
    EXPECT_EQ(oss.str(), "Proess Factory: 0\nProcess Distributor: 0\nProcess Wholesaler: 0\nProcess Retailer: 0\nsuccessfully exiting\n");
    EXPECT_EQ(gu.getCurrentWeek(), 2); // process order method should call advance week which increments current week

    che->tcpServerConnection->write("Namaste London");

    QTcpSocket *nextClient = new QTcpSocket();
    nextClient->setProxy(QNetworkProxy::NoProxy);
    nextClient->connectToHost(addr, port_no);
    nextClient->write("Hello");

    che->all_orders_done_for_this_week = true;
    che->updateServerProgress();

    che->tcpServerConnection->disconnectFromHost();
    che->tcpServer.close();


    delete che->tcpServerConnection;
    delete nextClient;
    delete che;
}

/**
* Runs all the Google Tests.
*/

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
