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

class Player {
    public:
        Player(); // Default constructor
        Player(string, vector<Territory*>, Hand*, OrdersList*, int); // Parameterized constructor
        Player(const Player &p); // Copy constructor

        ~Player(); // Destructor

        vector<Territory*> toDefend(Map* m); // Territories for player to defend
        vector<Territory*> toAttack(Map* m); // Territories for player to attack

        void issueOrder(string type); //  Create order and adds order to players order list

        int getNumberOfArmies(); // Get number of armies player has
        int getNumberOfTerritories(); // Get number of territories player owns
        void addToReinforcePool(int armies); // Add to reinforcement pool
        void removeFromReinforcePool(int armies); // Remove from reinforcement pool

        Territory* getOriginTerritory(Territory* target_territory, Map* m); // Returns a territory of the player that is adjacent to the one they would like to attack
        
        // Accessors
        void setName(string n), setTerritory(vector<Territory*> t), setHand(Hand* h), setOrder(OrdersList* o), setReinforcementPool(int armies);

        // Mutators
        void assignTerritory(Territory* t);
        void removeTerritory(int index);
        string getName();
        vector<Territory*> getTerritoryList();
        Hand* getHand();
        OrdersList* getOrder();
        int getReinforcePool();
        OrdersList* getDeployList();

        Player& operator = (const Player& player); 	// Assignment Operator
        friend ostream& operator<<(ostream& os, const Player& player); // Stream insertion operator

    private:
        string name; // Name of Player
        vector<Territory*> territories; // List of players territories
        Hand* hand; // Player hand
        OrdersList* orders; // Player list of orders
        int reinforcePool; // Number of reinforcements player has
        OrdersList* deployList; // List of deploy orders to be executed before the other orders
};