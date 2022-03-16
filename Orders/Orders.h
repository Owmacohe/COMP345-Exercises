#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;

class GameEngine;

class Order /*:public Iloggable, public Subject*/ {
public:
    // Constructor
    Order();
    Order(bool v, string s);
    Order(const Order& o);
    virtual ~Order();

    // Accessors
    virtual string getDescription();
    bool getValidated();
    static GameEngine* getGameEngine();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);
    static void setGameEngine(GameEngine* gamePlaying);

    // Assignment operator
    Order& operator = (const Order& D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Order& order);

    // Pure virtual validate function;
    virtual void validate() = 0;

    //Pure virtual execute function
    virtual void execute() = 0;


    // From Iloggable
     string stringToLog();
    // From Subject but no need to overload it
    //void notify(Iloggable* il);

    bool validated;
    string description;
    static GameEngine* game;
};


class Deploy : public Order {

public:
    // Constructor
    Deploy();
    Deploy(Player* p);
    Deploy(const Deploy& original);

    //Destructor
    ~Deploy();

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Player* getPlayerIssuing();
    int getNumToDeploy();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Deploy& operator = (const Deploy& D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Deploy& deploy);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
    string stringToLog();
    string validateResult;

private:
    Player* playerIssuing;
    Territory* target;
    int numToDeploy;
};

class Advance : public Order {

public:
    // Constructor
    Advance();
    Advance(Player* p);
    Advance(const Advance& original);

    //Destructor
    ~Advance();

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Territory* getOrigin();
    Player* getPlayerIssuing();
    int getNumToAdvance();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Advance& operator = (const Advance& d);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Advance& advance);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
    string validateResult;
    string stringToLog();

private:
    Player* playerIssuing;
    Territory* origin;
    Territory* target;
    int numToAdvance;
};

class Airlift : public Order {
public:
    // Constructor
    Airlift();
    Airlift(Player* p);
    Airlift(const Airlift& original);

    //Destructor
    ~Airlift();

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Territory* getOrigin();
    Player* getPlayerIssuing();
    int getNumToAirlift();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Airlift& operator = (const Airlift &D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Airlift& airflit);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
    string stringToLog();

private:
    Player* playerIssuing;
    Territory* target;
    Territory* origin;
    int numToAirlift;
};

class Bomb : public Order {
public:
    // Constructor
    Bomb();
    Bomb(Player* p);
    Bomb(const Bomb& original);

    //Destructor
    ~Bomb();

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Territory* getOrigin();
    Player* getPlayerIssuing();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Bomb& operator = (const Bomb& D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Bomb& bomb);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
     string stringToLog();

private:
    Player* playerIssuing;
    Territory* origin;
    Territory* target;
};

class Blockade : public Order {
public:
    Blockade();
    Blockade(Player* p);
    Blockade(const Blockade& original);

    //Destructor
    ~Blockade();

    // Accessors
    string getDescription();
    bool getValidated();
    Player* getPlayerIssuing();
    Territory* getTarget();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Blockade& operator = (const Blockade& D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Blockade& blockade);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
     string stringToLog();

private:
    Player* playerIssuing;
    Territory* target;
};

class Negotiate : public Order {
public:
    // Constructor
    Negotiate();
    Negotiate(Player* p);
    Negotiate(const Negotiate& original);

    //Destructor
    ~Negotiate();

    // Accessors
    string getDescription();
    bool getValidated();
    Player* getPlayerIssuing();
    Player* getTargetPlayer();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    // Assignment operator
    Negotiate& operator = (const Negotiate& D);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const Negotiate& negotiate);

    //Method to validate if an order is valid
    void validate();

    //Method to execute the order
    void execute();

    // From Iloggable
     string* validateResult;
     string stringToLog();

private:
    Player* playerIssuing;
    Player* targetPlayer;

};

class OrdersList : /*public Iloggable, public Subject*/ {
public:
    // Constructor
    OrdersList();
    OrdersList(vector<Order*> vo);
    OrdersList(const OrdersList& original);

    // Destructor
    virtual ~OrdersList();

    // Accessors
    vector<Order*> getOrderList();

    // Mutators
    void setOrderList(vector<Order*> vo);

    // Assignment operator
    OrdersList operator = (const OrdersList& original);

    // Stream insertion operator
    friend ostream& operator<<(ostream& os, const OrdersList& ordersList);

    // Method used to add an order of the OrderList.
    void addOrder(Order* order);

    // Remove Method used to remove an order of the OrderList.
    void remove(int i);

    // Move Method used to move an order at index i into the position of index j.
    void move(int i, int j);

    // From Iloggable
    string stringToLog();
    vector<Order*> playerOrderList;
};

/**************



Deploy(bool v, string s, Player* p, Territory* t);  // Parameterized constructor
Deploy(Player* p, Territory* t);  // Parameterized constructor For IssueOrders Phase

Advance(bool v, string s, Player* p, Territory* t, Territory* o);  // Parameterized constructor
Advance(Player* p, Territory* t, Territory* o);  // Parameterized constructor For IssueOrders Phase

Airlift(bool v, string s, Player* p, Territory* o, Territory* t, int armies);  // Parameterized constructor
Airlift(Player* p, Territory* o, Territory* t, int numOfArmies);  // Parameterized constructor For IssueOrders Phase

Bomb(bool v, string s, Player* p, Territory* o, Territory* t);  // Parameterized constructor
Bomb(Player* p, Territory* o, Territory* t);  // Parameterized constructor For IssueOrders Phase

Blockade(Player* p, Territory* t);  // Parameterized constructor for IssueOrders Phase
Blockade(bool v, string s, Player* p, Territory* t);  // Parameterized constructor

Negotiate(Player* p1, Player* p2);  // Parameterized constructor (Player only)
Negotiate(bool v, string s, Player* p1, Player* p2);  // Parameterized constructor

void addOrder(Order order); // Add Method used to add an order of the OrderList.
void addOrder(string order); // Add Method used to add an order of the OrderList.
 *************/