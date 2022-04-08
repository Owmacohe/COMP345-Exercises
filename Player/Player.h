#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;


class Hand;
class OrdersList;
class Territory;
class Map;
class Order;

class PlayerStrategies;

class Player {
public:
    // Default constructor
    Player();

    // Parameterized constructor
    Player(string, vector<Territory*>, Hand*, OrdersList*, int);
    Player(string name);
    Player(PlayerStrategies* ps);
    Player(PlayerStrategies* ps, string name);

    // Copy constructor
    Player(const Player &p);

    // Destructor
    ~Player();

//    vector<Territory*> toDefend(Map* m); // Territories for player to defend
//    vector<Territory*> toAttack(Map* m); // Territories for player to attack
//
//    void issueOrder(string type); //  Create order and adds order to players order list

    // Add to reinforcement pool
    void addToReinforcePool(int armies);

    // Remove from reinforcement pool
    void removeFromReinforcePool(int armies);

    // Check if player owns a territory by name
    Territory*  checkTerritoryOwn(string name);

    // Returns a territory of the player that is adjacent to the one they would like to attack
    Territory* getOriginTerritory(Territory* target_territory, Map* m);

    // Add a territory to player territories list
    void assignTerritory(Territory* t);

    // Remove a territory from a player territories list by index
    void removeTerritory(int index);

    // Add order to player order list
    void addOrderList(Order* o);

    // Accessors
    void setName(string n);
    void setHand(Hand* h);
    void setReinforcementPool(int armies);
    void setTerritory(vector<Territory*> t);
    void setOrder(OrdersList* o);
    void setStrategy(PlayerStrategies* ps);

    // Mutators
    string getName();
    Hand* getHand();
    int getReinforcePool();
    int getNumberOfArmies();
    int getNumberOfTerritories(); // Get number of territories player owns
    OrdersList* getOrder();
    OrdersList* getDeployList();
    PlayerStrategies* getPlayerStrategy();
    vector<Territory*> getTerritoryList();

    // Operator overloading
    Player& operator = (const Player& player);
    friend ostream& operator<<(ostream& os, const Player& player);

    // Assignment 3
    vector<Territory*> toDefend(); // Territories for player to defend
    vector<Territory*> toAttack(); // Territories for player to attack
    void issueOrder(string input); //  Create order and adds order to players order list

private:
    // Name of Player
    string name;

    // Player hand
    Hand* hand;

    // Number of reinforcements player has
    int reinforcePool;

    // List of players territories
    vector<Territory*> territories;

    // Player list of orders
    OrdersList* orders;

    // List of deploy orders to be executed before the other orders
    OrdersList* deployList;

    // Strategy pattern implementation
    PlayerStrategies* playerStrategy;
};