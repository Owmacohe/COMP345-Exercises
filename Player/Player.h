#pragma once

#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Hand;
class OrdersList;
class Territory;

class Player {
    public:
        Player(); // Default constructor
        Player(string, vector<Territory*>, Hand*, OrdersList*, int); // Parameterized constructor
        Player(const Player &p); // Copy constructor

        ~Player(); // Destructor

        vector<Territory*> toDefend(); // Territories for player to defend
        vector<Territory*> toAttack(); // Territories for player to attack

        void issueOrder(string); //  Create order and adds order to players order list

        // Accessors
        void setName(string n), setTerritory(vector<Territory*> t), setHand(Hand* h), setOrder(OrdersList* o), setArmies(int a);

        // Mutators
        string getName();
        vector<Territory*> getTerritory();
        Hand* getHand();
        OrdersList* getOrder();
        int getArmies();

        Player& operator = (const Player& player); 	// Assignment Operator
        friend ostream& operator<<(ostream& os, const Player& player); // Stream insertion operator

    private:
        string name; // Name of Player
        vector<Territory*> territories; // List of players territories
        Hand* hand; // Player hand
        OrdersList* orders; // Player list of orders

        //added with a2
        int num_armies;
        //probably have to created a class reinforcement pool to hold armies, and have each player have a reinforcement pool
        //check until reinforcement pool is empty then all armies are either attacking or defending
};