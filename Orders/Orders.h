#pragma once

#include <vector>
#include <string>
#include <iostream>
//#include "../LoggingObserver/LoggingObserver.h"
using namespace std;

class Territory;
class Player;
class GameEngine;

class Order /*:public Iloggable, public Subject*/ {
public:
    Order(); // Default constructor
    Order(bool v, string s, Player* p); // Parameterized constructor
    Order(Order& o); // Copy constructor
    virtual ~Order(); // Destructor
		
    string getDescription(); bool getValidated(); // Accessors
    static GameEngine* getGameEngine();
    void setDescription(string d); void setValidated(bool v); // Mutators
    static void setGameEngine(GameEngine* gamePlaying);

    Order& operator = (const Order& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Order& order); // Stream insertion operator

    virtual void validate(); // ADDED THIS TO MAKE IT AN ABSTRACT CLASS - not required in assignment but makes sense
                               // validate() return string for compatibility with Loggable

    virtual void execute() = 0; // CHANGE RETURN TYPE BOOL->VOID Assignment requirement: execute is a pure virtual method


    // From Iloggable
    string stringToLog();
    // From Subject but no need to overload it
    //void notify(Iloggable* il);

    bool validated;
    string description;
    Player* playerIssuing;
    static GameEngine* game;
};


class Deploy : public Order {
public:
    Deploy(); // Default constructor
    Deploy(bool v, string s, Player* p, Territory* t);  // Parameterized constructor
    Deploy(Player* p, Territory* t);  // Parameterized constructor For IssueOrders Phase
    Deploy(Deploy& original); // Copy constructor
    ~Deploy(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Deploy& operator = (const Deploy& D); 	// Assignment operator
    friend ostream& operator<<(ostream& os, const Deploy& deploy); // Stream insertion operator

    void validate();
    void execute();
    Territory* target;
    int numToDeploy;

    // From Iloggable
    string stringToLog();
    string validateResult;

};

class Advance : public Order {
public:
    Advance(); // Default constructor
    Advance(bool v, string s, Player* p, Territory* t, Territory* o);  // Parameterized constructor
    Advance(Player* p, Territory* t, Territory* o);  // Parameterized constructor For IssueOrders Phase
    Advance(Advance& original); // Copy constructor
    ~Advance(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    friend int getToMoveArmies();

    Advance& operator = (const Advance& d); // Assignment operator
    friend ostream& operator<<(ostream& os, const Advance& advance); // Stream insertion operator

    void validate();
    void execute();
    Territory* target;
    Territory* origin;
    int numToAdvance;

    // From Iloggable
    string validateResult;
    string stringToLog();

};

class Airlift : public Order {
public:
    Airlift();  // Default constructor
    Airlift(bool v, string s, Player* p, Territory* o, Territory* t, int armies);  // Parameterized constructor
    Airlift(Player* p, Territory* o, Territory* t, int numOfArmies);  // Parameterized constructor For IssueOrders Phase
    Airlift(Airlift& original); // Copy constructor
    ~Airlift(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Airlift& operator = (const Airlift &D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Airlift& airflit); // Stream insertion operator

    void validate();
    void execute();
    Territory* target;
    Territory* origin;
    int numOfArmies;

    // From Iloggable
     string stringToLog();
};

class Bomb : public Order {
public:
    Bomb(); // Default constructor
    Bomb(bool v, string s, Player* p, Territory* o, Territory* t);  // Parameterized constructor
    Bomb(Player* p, Territory* o, Territory* t);  // Parameterized constructor For IssueOrders Phase
    Bomb(Bomb& original); // Copy constructor
    ~Bomb(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Bomb& operator = (const Bomb& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Bomb& bomb); // Stream insertion operator

    void validate();
    void execute();

    // From Iloggable
     string stringToLog();

    Territory* origin;
    Territory* target;

};

class Blockade : public Order {
public:
    Blockade();  // Default constructor
    Blockade(Player* p, Territory* t);  // Parameterized constructor for IssueOrders Phase
    Blockade(bool v, string s, Player* p, Territory* t);  // Parameterized constructor
    Blockade(Blockade& original); // Copy constructor
    ~Blockade(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Blockade& operator = (const Blockade& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Blockade& blockade); // Stream insertion operator

    void validate();
    void execute();

    // From Iloggable
     string stringToLog();

    Territory* target;
};


class Negotiate : public Order {
public:
    Negotiate();  // Default constructor
    Negotiate(Player* p1, Player* p2);  // Parameterized constructor (Player only)
    Negotiate(bool v, string s, Player* p1, Player* p2);  // Parameterized constructor
    Negotiate(Negotiate& original); // Copy constructor
    ~Negotiate(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Negotiate& operator = (const Negotiate& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Negotiate& negotiate); // Stream insertion operator

    void validate();
    void execute();

    // From Iloggable
     string* validateResult;
     string stringToLog();

    Player* targetPlayer;

};

class Reinforcement : public Order {
public:
    Reinforcement();  // Default constructor
    Reinforcement(bool v, string s, Player* p);  // Parameterized constructor
    Reinforcement(Reinforcement& original); // Copy constructor
    ~Reinforcement(); // Destructor

    string getDescription(); bool getValidated(); // Accessors
    void setDescription(string d); void setValidated(bool v); // Mutators

    Reinforcement& operator = (const Reinforcement& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Reinforcement& reinforcement); // Stream insertion operator

    void validate();
    void execute();

    // From Iloggable
    // string stringToLog();
};

class OrdersList /*: public Iloggable, Subject*/ {
public:
    vector<Order*> playerOrderList;
    bool aov;   // TODO ??? For AllOrdersValidated Method

    OrdersList(); // Default constructor
    OrdersList(vector<Order*> vo); // Parameterized constructor
    OrdersList(OrdersList& original);  // Copy constructor
    virtual ~OrdersList(); // Destructor

    vector<Order*> getOrderList(); bool getAllOrdersValidated(); // Accessors
    void setOrderList(vector<Order*> vo); void setAllOrdersValidated(bool v); // Mutators

    OrdersList operator = (const OrdersList& original); // Assignment operator
    friend ostream& operator<<(ostream& os, const OrdersList& ordersList); // Stream insertion operator

//    void addOrder(Order order); // Add Method used to add an order of the OrderList.
    void addOrder(Order* order); // Add Method used to add an order of the OrderList.
    void addOrder(string order); // Add Method used to add an order of the OrderList.
    void remove(int i); // Remove Method used to remove an order of the OrderList.
    void move(int i, int j); // Move Method used to move an order at index i into the position of index j.

    // From Iloggable
    string stringToLog();
};


