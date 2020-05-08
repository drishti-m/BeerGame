/** 
 *  @file   game.h
 *  @brief  Settings of the game, which are set and can be changed by the instructor
 ***************************************************************************************/

#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>

#include "order.h"
#include "shipment.h"
#include "player.h"
#include "playerevent.h"

class Player;
class Shipment;
class Order;

/// @brief Class for setting and configuring the constraints of the Beer Game
class Game
{
public:
  /// @brief Vector storing unique ID values
  std::vector<int> GIDS;

  /// @brief Default Constructor
  Game(){
    gId = instrId = pFactId = pDistributorId = pWholesalerId = pRetailerId = 0;
    orderDelay = shipmentDelay = 2;
    holdingCost = 0.5;
    backorderCost = 1.0;
    startingInventory = 12;
    weeksToBePlayed = 26;
    currentWeek = 0;
    infoCode = 0;
    factoryDelay = 1;
    nPlayers = 0;
    consumerDemandPerWeek.assign(26, 4);
  }

  /// @brief Destructor
  ~Game()
  {
    //GIDS.erase(std::remove(GIDS.begin(), GIDS.end(), gId), GIDS.end());
  }

  /// @brief Construct game object with a given instructor id.
  ///
  /// @param instrId  Instructor ID
  ///
  Game(int instrId);

  /// @brief Construct game object with a different given parameters
  ///
  /// @param instrId  Instructor ID
  /// @param backlogCost Cost for the one backlog item
  /// @param holdingCost Cost for holding one item
  /// @param orderDelay Order Delay
  /// @param totalWeeks Total amount of weeks to be played in the game
  /// @param startInventory Initial amount of inventory
  /// @param factoryDelay Factory Delay
  Game(int instrId, double backlogCost, double holdingCost, int orderDelay, int totalWeeks, int startInventory, int factoryDelay);

  /// @brief Orders and Shipments for Week 1 and Week 2
  void startGame();

  /// @brief Execute orders for the current week
  void executeOrdersForCurrentWeek();

  /// @brief Ship orders for the current week
  void executeShipmentsForCurrentWeek();

  /// @brief Update Player Inventories
  void updatePlayerInventories();

  /// @brief get consumer order for week
  /// @return consumer's order for a certain week
  int getConsumerOrderForWeek();

  /// @brief Move onto the next week and executeWeekTransactions
  /// @return current week number
  int advanceWeek();

  /// @brief add order to a certain week. Store it in the vector to be executed
  /// @param role role in integer
  /// @param numberOfBeers order
  void addOrder(const int &role, int numberOfBeers);

  /// @brief add shipment to a certain week. Store it in the vector to be executed
  /// @param role player role
  /// @param numberOfBeers shipment number beers
  void addShipment(const int &role, int numberOfBeers);

  /// @brief add a new player
  /// @param *player pointer to the player
  void addPlayer(Player *player);

  /// @brief get a certain player
  /// @param role Factory, Distributor, Wholesaler, Retailer
  /// @return the player (role) who is predecessor in the chain
  Player *getDownstream(int role);

  /// @brief get a certain player
  /// @param role Factory, Distributor, Wholesaler, Retailer
  /// @return the player (role) who is successor in the chain
  Player *getUpstream(int role);

  /// @brief randomly generate password containing characters and some other symbols
  /// @return generated password
  std::vector<std::string> generatePasswords();

private:
  /// @brief The game id
  int gId;
  /// @brief The game's intructor's id
  unsigned int instrId = 0;
  /// @brief The game's factory player id
  unsigned int pFactId = 0;
  /// @brief The game's distributor player id
  unsigned int pDistributorId = 0;
  /// @brief The game's wholesaler player id
  unsigned int pWholesalerId = 0;
  /// @brief The game's retailer player id
  unsigned int pRetailerId = 0;

  /// @brief Vector of orders to be executed
  std::map<int, std::vector<Order>> ordersToBeExecuted;

  /// @brief Vector of shipments to be executed
  std::map<int, std::vector<Shipment>> shipmentsToBeExecuted;

  /// @brief Vector of players
  std::vector<Player *> players;

  /// @brief Vector of consumer demands
  std::vector<int> consumerDemandPerWeek = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

  /// @brief Order Delay
  int orderDelay = 2;

  /// @brief Shipment Delay
  int shipmentDelay = 2;

  /// @brief Holding Cost
  double holdingCost = 0.5;

  /// @brief Backorder Cost
  double backorderCost = 1;

  /// @brief Starting Inventory
  int startingInventory = 12;

  /// @brief Weeks to be played
  int weeksToBePlayed = 26;

  /// @brief Current Week number
  int currentWeek = 0;

  /// @brief Info code
  int infoCode = 0;

  /// @brief Factory Delay
  int factoryDelay = 1;

  /// @brief Total orders in week
  int totalOrdersInWeek = 0;

  /// @brief Total shipments in weel
  int totalShipmentsInWeek = 0;

  /// @brief Number of players
  int nPlayers = 4;

  /**
    * \brief Attribute for total cost of supply chain in one game
    */
  double total_cost = 0.0;

public:
  /**
     * \brief Map with key as week no, and value as Vector of int to test the game for a given set of inputs for outgoing order
    */
  map<int, vector<int>> testing_input_outgoing_order;

  bool testing_mode = false;
  /**
     *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
     * 
      * \brief Implementation of getters and setter for this class
      * 
      * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
      */

  int getNPlayers() const;
  void setNPlayers(int value);
  int getNShipmentsReceived() const;
  void setNShipmentsReceived(int value);
  int getNOrdersReceived() const;
  void setNOrdersReceived(int value);
  int getFactoryDelay() const;
  void setFactoryDelay(int value);
  int getInfoCode() const;
  void setInfoCode(int value);
  int getCurrentWeek() const;
  void setCurrentWeek(int value);
  int getWeeksToBePlayed() const;
  void setWeeksToBePlayed(int value);
  int getStartingInventory() const;
  void setStartingInventory(int value);
  double getBackOrderCost() const;
  void setBackOrderCost(double value);
  double getHoldingCost() const;
  void setHoldingCost(double value);
  int getShipmentDelay() const;
  void setShipmentDelay(int value);
  int getOrderDelay() const;
  void setOrderDelay(int value);
  std::vector<int> getConsumerDemandPerWeek() const;
  void setConsumerDemandPerWeek(const std::vector<int> &value);
  std::vector<Player *> getPlayers() const;
  void setPlayers(const std::vector<Player *> &value);
  std::map<int, std::vector<Shipment>> getShipmentsToBeExecuted() const;
  void setShipmentsToBeExecuted(const std::map<int, std::vector<Shipment>> &value);
  std::map<int, std::vector<Order>> getOrdersToBeExecuted() const;
  void setOrdersToBeExecuted(const std::map<int, std::vector<Order>> &value);
  unsigned int getPRetailerId() const;
  void setPRetailerId(unsigned int value);
  unsigned int getPWholesalerId() const;
  void setPWholesalerId(unsigned int value);
  unsigned int getPDistributorId() const;
  void setPDistributorId(unsigned int value);
  unsigned int getPFactId() const;
  void setPFactId(unsigned int value);
  unsigned int getInstrId() const;
  void setInstrId(unsigned int value);
  int getGId() const;
  void setGId(int value);
  int getTotalOrdersInWeek() const;
  void setTotalOrdersInWeek(int value);
  int getTotalShipmentsInWeek() const;
  void setTotalShipmentsInWeek(int value);
  bool getTesting_mode() const;
  void setTesting_mode(bool value);
  map<int, vector<int>> getTesting_input_outgoing_order() const;
  void setTesting_input_outgoing_order(const map<int, vector<int>> &value);
  double getTotal_cost() const;
  void setTotal_cost(double value);
  int getConsumerDemandForWeek(int week);
};
#endif // GAME_H
