#pragma once

#include <iostream>
using namespace std;

#include <list>
#include <vector>
#include <string>

class Hand;
class OrdersList;
class Map;

class Player {
    public:
        Player(); // Default constructor
        Player(string, vector<Territory*>, Hand*, OrdersList*); // Parameterized constructor
        Player(const Player &p); // Copy constructor

        ~Player(); // Destructor

        vector<Territory*> toDefend(); // Territories for player to defend
        vector<Territory*> toAttack(); // Territories for player to attack

        void issueOrder(); //  Create order and adds order to players order list

        // Accessors
        void setName(string n), setTerritory(vector<Territory*> t), setHand(Hand* h), setOrder(OrdersList* o);

        // Mutators
        string getName();
        vector<Territory*> getTerritory();
        Hand* getHand();
        OrdersList* getOrder();

        Player& operator = (const Player& player); 	// Assignment Operator
        friend ostream& operator<<(ostream& os, Player& player); // Stream insertion operator
        
    private:
        string name; // Name of Player
        vector<Territory*> territories; // List of players territories
        Hand* hand; // Player hand
        OrdersList* orders; // Player list of orders
};