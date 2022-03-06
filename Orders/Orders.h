#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

class Order : public Iloggable, public Subject {
	public:
		bool validated;
		string description;
		Order(); // Default constructor
		Order(bool v, string s); // Parameterized constructor
		Order(Order& o); // Copy constructor
		~Order(); // Destructor
		
		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators
        static void setGameEngine(GameEngine* gamePlaying); //Audrey: since it's working with a static var. The method should also be static ?

		Order& operator = (const Order& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Order& order); // Stream insertion operator

		bool validate();
		bool virtual execute(); // ADDED THIS TO MAKE IT AN ABSTRACT CLASS

        // From Iloggable
        string stringToLog();
        // From Subject but no need to overload it
        //void notify(Iloggable* il);

    public:
    bool validated;
    string description;
    Player* playerIssuing;
    static GameEngine* game;
};

class Deploy : public Order {
	public:
		Deploy(); // Default constructor
		Deploy(bool v, string s);  // Parameterized constructor
		Deploy(Deploy& original); // Copy constructor
		~Deploy(); // Destructor

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Deploy& operator = (const Deploy& D); 	// Assignment operator
		friend ostream& operator<<(ostream& os, const Deploy& deploy); // Stream insertion operator

		bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

};

class Advance : public Order {
	public:
		Advance(); // Default constructor
		Advance(bool v, string s);  // Parameterized constructor
		Advance(Advance& original); // Copy constructor
		~Advance(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Advance& operator = (const Advance& d); // Assignment operator
		friend ostream& operator<<(ostream& os, const Advance& advance); // Stream insertion operator

        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

};

class Bomb : public Order {
	public:
		Bomb(); // Default constructor
		Bomb(bool v, string s);  // Parameterized constructor
		Bomb(Bomb& original); // Copy constructor
		~Bomb(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Bomb& operator = (const Bomb& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Bomb& bomb); // Stream insertion operator

        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

    public:
    Territory* origin;
    Territory* target;

    static GameEngine* game;
    virtual GameEngine* getGameEngine() { return game;}
    GameEngine* Bomb::game = new GameEngine();

};


class Blockade : public Order {
	public:
		Blockade();  // Default constructor
		Blockade(bool v, string s);  // Parameterized constructor
		Blockade(Blockade& original); // Copy constructor
		~Blockade(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Blockade& operator = (const Blockade& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Blockade& blockade); // Stream insertion operator

        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

};

class Airlift : public Order {
	public:
		Airlift();  // Default constructor
		Airlift(bool v, string s);  // Parameterized constructor
		Airlift(Airlift& original); // Copy constructor
		~Airlift(); // Destructor 
		
		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Airlift& operator = (const Airlift &D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Airlift& airflit); // Stream insertion operator

        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

};

class Negotiate : public Order {
	public:
		Negotiate();  // Default constructor
		Negotiate(bool v, string s);  // Parameterized constructor
		Negotiate(Negotiate& original); // Copy constructor
		~Negotiate(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Negotiate& operator = (const Negotiate& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Negotiate& negotiate); // Stream insertion operator
        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();

};

class Reinforcement : public Order {
	public:
		Reinforcement();  // Default constructor
		Reinforcement(bool v, string s);  // Parameterized constructor
		Reinforcement(Reinforcement& original); // Copy constructor
		~Reinforcement(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Reinforcement& operator = (const Reinforcement& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Reinforcement& reinforcement); // Stream insertion operator

        bool validate();
		bool execute();

        // From Iloggable
        string stringToLog();
};

class OrdersList : public Iloggable, Subject {
	public: 
		vector<Order*> playerOrderList;
		bool allOrdersValidated;

		OrdersList(); // Default constructor
		OrdersList(vector<Order*> vo, bool aov); // Parameterized constructor
		OrdersList(OrdersList& original);  // Copy constructor
		~OrdersList(); // Destructor 

		vector<Order*> getOrderList(); bool getAllOrdersValidated(); // Accessors
		void setOrderList(vector<Order*> vo); void setAllOrdersValidated(bool v); // Mutators

		OrdersList operator = (const OrdersList& original); // Assignment operator
		friend ostream& operator<<(ostream& os, const OrdersList& ordersList); // Stream insertion operator

		void addOrder(Order order); // Add Method used to add an order of the OrderList.
		void addOrder(Order* order); // Add Method used to add an order of the OrderList.
		void addOrder(string order); // Add Method used to add an order of the OrderList.
		void remove(int i); // Remove Method used to remove an order of the OrderList.
		void move(int i, int j); // Move Method used to move an order at index i into the position of index j.

        // From Iloggable
        string stringToLog();
};