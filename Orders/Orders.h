#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../LoggingObserver/LoggingObserver.h"

using namespace std;

class GameEngine;
class Player;
class Territory;

/****************************** Order *******************************/
class Order :public Iloggable, public Subject {
public:
    Order(); // Default Constructor
    Order(bool v, string s); // parameterized Constructor
    Order(const Order& o); // Copy Constructor
    virtual ~Order(); // Destructor
    Order& operator = (const Order& D);    // Assignment operator
    friend ostream& operator<<(ostream& os, const Order& order);   // Stream insertion operator

    // Accessors
    virtual string getDescription();
    bool getValidated();
    static GameEngine* getGameEngine();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);
    static void setGameEngine(GameEngine* gamePlaying);

    virtual void validate() = 0; // Pure virtual validate function;
    virtual void execute() = 0; //Pure virtual execute function

    // From Iloggable
     string stringToLog() override;

    bool validated; // Status of validation54
    string description; // Description of the Order
    static GameEngine* game; // Game Engine pointer for Order subclasses execution and validation
};

/****************************** Deploy *******************************/
class Deploy : public Order {

public:
    Deploy(); // Constructor
    Deploy(Player* p); // parameterized Constructor
    Deploy(Player* p, Territory* target);
    Deploy(const Deploy& original);  // Copy Constructor
    ~Deploy();  //Destructor
    Deploy& operator = (const Deploy& D); // Assignment operator
    friend ostream& operator<<(ostream& os, const Deploy& deploy); // Stream insertion operator

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Player* getPlayerIssuing();
    int getNumToDeploy();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    void validate();     //Method to validate if an order is valid
    void execute();     //Method to execute the order

    // From Iloggable
    string stringToLog();

private:
    Player* playerIssuing; // Player issuing the current Order subclass object
    Territory* target; // Territory targeted by the Order subclass object
    int numToDeploy; // Number of armies to Deploy to the target territory
};

/****************************** Advance *******************************/
class Advance : public Order {

public:
    Advance(); // Constructor
    Advance(Player* p);  // Parameterized Constructor
    Advance(Player* p, Territory* origin, Territory* target);
    Advance(const Advance& original);  // Copy Constructor
    ~Advance(); //Destructor
    Advance& operator = (const Advance& d);  // Assignment operator
    friend ostream& operator<<(ostream& os, const Advance& advance);  // Stream insertion operator

    int deathCalculation(int qty, double probability);
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

    void validate();  //Method to validate if an order is valid
    void execute();  //Method to execute the order

    // From Iloggable
    string validateResult;

    string stringToLog(); // Method to determine the effect of the Advance order after validation

private:
    Player* playerIssuing; // Player issuing the current Order subclass object
    Territory* origin; // Territory where the Order subclass object takes origin from
    Territory* target; // Territory targeted by the Order subclass object
    int numToAdvance; // Number of Armies to Advance
};

/****************************** Airlift *******************************/

class Airlift : public Order {
public:
    Airlift();  // Constructor
    Airlift(Player* p); // Parameterized Constructor
    Airlift(Player* p, Territory* origin, Territory* target);
    Airlift(const Airlift& original); // Copy Constructor
    ~Airlift();  //Destructor
    Airlift& operator = (const Airlift &D);  // Assignment operator
    friend ostream& operator<<(ostream& os, const Airlift& airflit);    // Stream insertion operator

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

    void validate();  //Method to validate if an order is valid
    void execute();   //Method to execute the order

    // From Iloggable
    string stringToLog();

private:
    Player* playerIssuing; // Player issuing the current Order subclass object
    Territory* target; // Territory targeted by the Order subclass object
    Territory* origin; // Territory where the Order subclass object takes origin from
    int numToAirlift; // Number of Armies to Airlift from the origin to the target

};

/****************************** Bomb *******************************/

class Bomb : public Order {
public:
    Bomb();  // Constructor
    Bomb(Player* p); // Parameterized Constructor
    Bomb(Player* p, Territory* origin, Territory* target);
    Bomb(const Bomb& original);  // Copy Constructor
    ~Bomb();   //Destructor
    Bomb& operator = (const Bomb& D);  // Assignment operator
    friend ostream& operator<<(ostream& os, const Bomb& bomb);  // Stream insertion operator

    // Accessors
    string getDescription();
    bool getValidated();
    Territory* getTarget();
    Territory* getOrigin();
    Player* getPlayerIssuing();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);


    void validate(); //Method to validate if an order is valid
    void execute();  //Method to execute the order

    // From Iloggable
     string stringToLog();

private:
    Player* playerIssuing;  // Player issuing the current Order subclass object
    Territory* origin; // Territory where the Order subclass object takes origin from
    Territory* target; // Territory targeted by the Order subclass object

};

/****************************** Blockade *******************************/

class Blockade : public Order {
public:
    Blockade(); // Constructor
    Blockade(Player* p); // Parameterized Constructor
    Blockade(Player* p, Territory* target);
    Blockade(const Blockade& original); // Copy Constructor
    ~Blockade();   //Destructor
    Blockade& operator = (const Blockade& D);   // Assignment operator
    friend ostream& operator<<(ostream& os, const Blockade& blockade);  // Stream insertion operator

    // Accessors
    string getDescription();
    bool getValidated();
    Player* getPlayerIssuing();
    Territory* getTarget();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    void validate();  //Method to validate if an order is valid
    void execute();   //Method to execute the order

    // From Iloggable
     string stringToLog();

private:
    Player* playerIssuing; // Player issuing the current Order subclass object
    Territory* target; // Territory targeted by the Order subclass object

};

/****************************** Negotiate *******************************/

class Negotiate : public Order {
public:
    Negotiate();  // Constructor
    Negotiate(Player* p); // Parameterized Constructor
    Negotiate(Player* p, Player* target);
    Negotiate(const Negotiate& original); // Copy Constructor
    ~Negotiate(); //Destructor
    Negotiate& operator = (const Negotiate& D);  // Assignment operator
    friend ostream& operator<<(ostream& os, const Negotiate& negotiate);  // Stream insertion operator

    // Accessors
    string getDescription();
    bool getValidated();
    Player* getPlayerIssuing();
    Player* getTargetPlayer();

    // Mutators
    void setDescription(string d);
    void setValidated(bool v);

    void validate();  //Method to validate if an order is valid
    void execute();   //Method to execute the order

    // From Iloggable
     string stringToLog();

private:
    Player* playerIssuing; // Player issuing the current Order subclass object
    Player* targetPlayer; // Player targeted by the current Order subclass object
};

/****************************** OrdersList *******************************/
class OrdersList :public Iloggable, public Subject {

public:
    OrdersList();  // Constructor
    OrdersList(vector<Order*> vo); // Parameterized Constructor
    OrdersList(const OrdersList& original); // Copy Constructor
    virtual ~OrdersList();     // Destructor
    vector<Order*> getOrderList();  // Accessors
    void setOrderList(vector<Order*> vo);  // Mutators

    OrdersList operator = (const OrdersList& original);   // Assignment operator
    friend ostream& operator<<(ostream& os, const OrdersList& ordersList);   // Stream insertion operator

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
