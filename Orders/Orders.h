#pragma once
#include <vector>
#include <iostream>
#include "LoggingObserver/LoggingObserver.h"

using namespace std;

class Order : public Iloggable, Subject {
	public:
		bool validated;
		string description;
		Order(); // Default constructor
		Order(bool v, string s); // Parameterized constructor
		Order(Order& o); // Copy constructor
		~Order(); // Destructor
		
		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Order& operator = (const Order& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Order& order); // Stream insertion operator

		bool validate();
		bool execute(); // Implementation next assignment

        // From Iloggable
        string stringToLog();
};

class Deploy : public Order{
	public:
		Deploy(); // Default constructor
		Deploy(bool v, string s);  // Parameterized constructor
		Deploy(Deploy& original); // Copy constructor
		~Deploy(); // Destructor

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Deploy& operator = (const Deploy& D); 	// Assignment operator
		friend ostream& operator<<(ostream& os, const Deploy& deploy); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Advance : public Order{
	public:
		Advance(); // Default constructor
		Advance(bool v, string s);  // Parameterized constructor
		Advance(Advance& original); // Copy constructor
		~Advance(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Advance& operator = (const Advance& d); // Assignment operator
		friend ostream& operator<<(ostream& os, const Advance& advance); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Bomb : public Order{
	public:
		Bomb(); // Default constructor
		Bomb(bool v, string s);  // Parameterized constructor
		Bomb(Bomb& original); // Copy constructor
		~Bomb(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Bomb& operator = (const Bomb& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Bomb& bomb); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Blockade : public Order{
	public:
		Blockade();  // Default constructor
		Blockade(bool v, string s);  // Parameterized constructor
		Blockade(Blockade& original); // Copy constructor
		~Blockade(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Blockade& operator = (const Blockade& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Blockade& blockade); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Airlift : public Order{
	public:
		Airlift();  // Default constructor
		Airlift(bool v, string s);  // Parameterized constructor
		Airlift(Airlift& original); // Copy constructor
		~Airlift(); // Destructor 
		
		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Airlift& operator = (const Airlift &D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Airlift& airflit); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Negotiate : public Order{
	public:
		Negotiate();  // Default constructor
		Negotiate(bool v, string s);  // Parameterized constructor
		Negotiate(Negotiate& original); // Copy constructor
		~Negotiate(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Negotiate& operator = (const Negotiate& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Negotiate& negotiate); // Stream insertion operator
		string validate();
		bool execute(); // Implementation next assignment
};

class Reinforcement : public Order{
	public:
		Reinforcement();  // Default constructor
		Reinforcement(bool v, string s);  // Parameterized constructor
		Reinforcement(Reinforcement& original); // Copy constructor
		~Reinforcement(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Reinforcement& operator = (const Reinforcement& D); // Assignment operator
		friend ostream& operator<<(ostream& os, const Reinforcement& reinforcement); // Stream insertion operator

		string validate();
		bool execute(); // Implementation next assignment
};

class Diplomacy : public Order{
	public:
		Diplomacy();  // Default constructor
		Diplomacy(bool v, string s);  // Parameterized constructor
		Diplomacy(Diplomacy& original); // Copy constructor
		~Diplomacy(); // Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Diplomacy& operator = (const Diplomacy& D); // Assignment operator 
		friend ostream& operator<<(ostream& description, const Diplomacy& diplomacy);

		string validate();
		bool execute(); // Implementation next assignment
};

class OrdersList {
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
};