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

        vector<Territory*> toDefend(Map m); // Territories for player to defend
        vector<Territory*> toAttack(Map m); // Territories for player to attack

        void issueOrder(string); //  Create order and adds order to players order list

        int getNumberOfArmies(); // Get number of armies player has
        int getNumberOfTerritories(); // Get number of territories player owns

        void addToReinforcePool(int armies); // Add to reinforcement pool
        void removeFromReinforcePool(int armies); // Remove from reinforcement pool
        // Accessors
        void setName(string n), setTerritory(vector<Territory*> t), setHand(Hand* h), setOrder(OrdersList* o), setReinforcementPool(int armies);

        // Mutators
        string getName();
        vector<Territory*> getTerritory();
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
        int reinforcePool;
        OrdersList* deployList;

};