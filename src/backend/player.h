/** 
 *  @file   player.h
 *  @brief  Abstract class for different roles
 ******************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "game.h"
#include "../frontend/playerdialog.h"
#include "../frontend/ui_playerdialog.h"

#define CONSUMER 0
#define RETAILER 1
#define WHOLESALER 2
#define DISTRIBUTOR 3
#define FACTORY 4
using namespace std;

class Game;
const std::string GLOBAL_PLAYERS[] = {
    "Consumer",
    "Retailer",
    "Wholesaler",
    "Distributor",
    "Factory"};

/// @brief Class for roles like Factory, Distributor, Wholesaler, Retailer
class Player
{
public:
  /// @brief Vector storing unique ID values
  std::vector<int> PIDS;

  /// @brief Default Constructor
  Player(){
    pId = role = 0;
    inventory = 12;
    backorder = incomingOrder = incomingShipment = outgoingShipment = 0;
    cost = totalCost = 0.0;
    orderReceived = shipmentReceived = orderPlaced = shipmentPlaced = false;
    demand = 0;
    game = nullptr;
  }

  /// @brief Destructor
  ~Player()
  {
  }

  /// @brief Construct player object with a given game instance and role.
  ///
  /// @param *game pointer to the game
  /// @param role Factory, Distributor, Wholesaler, Retailer
  ///
  Player(Game *game, int role);

  /// @brief set UI
  void setUi(Ui::PlayerDialog *ui);

  /// @brief update player UI
  void updatePlayerUi();

  // To be implemented

  /// @brief place order with a certain number of beers
  /// @param numberOfBeers number of beers
  void placeOrder(int numberOfBeers);

  /// @brief place shipment with a certain number of beers
  /// @param numberOfBeers number of beers
  void placeShipment(int numberOfBeers);

  /// @brief get available shipment
  /// @param numberOfBeers number of beers
  int getAvailableShipment(int numberOfBeers);

  /// @brief receive shipment
  /// @param numberOfBeers number of beers
  void receiveShipment(int numberOfBeers);

  /// @brief receive order
  /// @param numberOfBeers number of beers
  void receiveOrder(int numberOfBeers);

  /// @brief decrease inventory by a certain number of beers
  /// @param numberOfBeers number of beers
  void decreaseInventory(int numberOfBeers);

  /// @brief increase inventory by a certain number of beers
  /// @param numberOfBeers number of beers
  void increaseInventory(int numberOfBeers);

  /**
     * \brief Getter method for the vector demand per week
     * \return vector of demands
    */
  vector<int> getDemand_every_week() const;
  /**
     * \brief Setter method for the vector demand per week
     * \param value vector of demands
    */
  void setDemand_every_week(const vector<int> &value);

  /**
     * \brief Getter method for the vector backlog per week
     * \return value vector of backlogs
    */
  vector<int> getBacklog_every_week() const;
  /**
     * \brief Setter method for the vector backlog per week
     * \param value vector of backlogs
    */
  void setBacklog_every_week(const vector<int> &value);

  /**
     * \brief Getter method for the vector inventories per week
     * \return vector of inventories
    */
  vector<int> getInventory_every_week() const;
  /**
     * \brief Setter method for the vector inventory per week
     * \param value vector of inventory
    */
  void setInventory_every_week(const vector<int> &value);

  /**
     * \brief Getter method for the vector cost per week
     * \return vector of costs
    */
  vector<double> getCost_every_week() const;
  /**
     * \brief Setter method for the vector cost per week
     * \param value vector of costs
    */
  void setCost_every_week(const vector<double> &value);

  /**
     * \brief Getter method for the vector delivered per week
     * \return vector of delivered
    */
  vector<int> getDelivered_every_week() const;
  /**
     * \brief Setter method for the vector delivered per week
     * \param value vector of delivered
    */
  void setDelivered_every_week(const vector<int> &value);

  /**
     * \brief Pushes argument x onto vector of shipments
     * \param x receiving shipment to be added
    */
  void add_received_to_vector(int x);

  /**
     * \brief Pushes argument x onto vector of demands
     * \param x demand to be added
    */
  void add_demand_to_vector(int x);

  /**
     * \brief Pushes argument x onto vector of delivered
     * \param x delivery to be added
    */
  void add_delivered_to_vector(int x);

  /**
     * \brief Pushes argument x onto vector of backlogs
     * \param x backlog to be added
    */
  void add_backlog_to_vector(int x);

  /**
     * \brief Pushes argument x onto vector of inventories
     * \param x inventory to be added
    */
  void add_inventory_to_vector(int x);

  /**
     * \brief Pushes argument x onto vector of costs
     * \param x cost to be added
    */
  void add_cost_to_vector(double x);

private:
  /**
    * \brief Attribute for Player Id that keeps track of the player's shipments as week progresses
    */
  vector<int> received_every_week = {0};

  /**
    * \brief Attribute for Player Id that keeps track of the player's demand as week progresses
    */

  vector<int> demand_every_week = {0};

  /**
    * \brief Attribute for Player Id that keeps track of the player's deliveries as week progresses
    */

  vector<int> delivered_every_week = {0};

  /**
    * \brief Attribute for Player Id that keeps track of the player's backlog as week progresses
    */

  vector<int> backlog_every_week = {0};

  /**
    * \brief Attribute for Player Id that keeps track of the player's inventory as week progresses
    */

  vector<int> inventory_every_week = {0};

  /**
    * \brief Attribute for Player Id that keeps track of the player's costs as week progresses
    */

  vector<double> cost_every_week = {0.0};
  /// @brief pointer to the game
  Game *game;
  /// @brief player ui
  Ui::PlayerDialog *playerui;

  /// @brief player id
  int pId = 0;

  /// @brief role
  int role;

  /// @brief inventory
  int inventory = 12;

  /// @brief back order
  int backorder = 0;

  /// @brief incoming order
  int incomingOrder = 0;

  /// @brief incoming shipment
  int incomingShipment = 0;

  /// @brief outgoing shipment
  int outgoingShipment = 0;

  /// @brief demand
  int demand = 0;

  /// @brief cost
  double cost = 0;

  /// @brief total cost
  double totalCost = 0;

  /// @brief order received
  bool orderReceived = false;

  /// @brief shipment received
  bool shipmentReceived = false;

  /// @brief order placed
  bool orderPlaced = false;

  /// @brief shipment placed
  bool shipmentPlaced = false;

public:
  /**
   *  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   *
    * \brief Implementation of getters and setter for this class
    *
    * $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
    */

  Game *getGame() const;
  void setGame(Game *value);
  Ui::PlayerDialog *getPlayerui() const;
  void setPlayerui(Ui::PlayerDialog *value);
  int getPId() const;
  void setPId(int value);
  int getRole() const;
  void setRole(int value);
  int getInventory() const;
  void setInventory(int value);
  int getBackorder() const;
  void setBackorder(int value);
  int getIncomingOrder() const;
  void setIncomingOrder(int value);
  int getIncomingShipment() const;
  void setIncomingShipment(int value);
  int getOutgoingShipment() const;
  void setOutgoingShipment(int value);
  int getDemand() const;
  void setDemand(int value);
  double getCost() const;
  void setCost(double value);
  double getTotalCost() const;
  void setTotalCost(double value);
  bool isOrderReceived() const;
  void setOrderReceived(bool value);
  bool isShipmentReceived() const;
  void setShipmentReceived(bool value);
  bool isOrderPlaced() const;
  void setOrderPlaced(bool value);
  bool isShipmentPlaced() const;
  void setShipmentPlaced(bool value);

  vector<int> getReceived_every_week() const;
  void setReceived_every_week(const vector<int> &value);
};

#endif // PLAYER_H
