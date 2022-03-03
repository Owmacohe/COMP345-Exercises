#pragma once

#include <list>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Hand;
class OrdersList;
class Territory;

//added with a2
class Army {
    public:

        Army(); // Default constructor
        Army(int, Territory* = NULL); // Parameterized constructor
        Army(const Army &a); // Copy constructor

        ~Army(); // Destructor

        // Mutators
        int getA_Num();
        Territory* getLocated();

        // Accessors
        void setA_Num(int n), setLocated(Territory* t);

        
        Army& operator = (const Army& Army); 	// Assignment Operator
        friend ostream& operator<<(ostream& os, const Army& Army); // Stream insertion operator

    private:
        Territory* located; // Where army is located
        int a_num; // Number of army
};

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

        void addArmy(const Army &a); // Method to add army to array of pointers
        void removeArmy(const Army &a); // Method to remove army from array of pointers

    private:
        string name; // Name of Player
        vector<Territory*> territories; // List of players territories
        Hand* hand; // Player hand
        OrdersList* orders; // Player list of orders

        //added with a2
        int num_armies; // Total number of armies player has
        int num_reinforcement; // Number of reinforment armies player has

        Army *armies; // Array of army pointers that are defending or attacking
};