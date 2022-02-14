#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Order {
	public:
		bool validated;
		string description;
		Order();  // Default Constructor
		Order(bool v, string s);  // Parameterized Constructor
		Order(Order& o); // Copy Constructor
		~Order(); // Default Destructor
		
		// Accessors
		string getDescription(); bool getValidated();
		// Mutators
		void setDescription(string d); void setValidated(bool v);

		Order& operator = (const Order& D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Order& order); // stream insertion operator

		bool validate();
		bool execute(); //Implementation next assignment
};

class Deploy : public Order{
	public:
		Deploy(); // Default Constructor
		Deploy(bool v, string s);  // Parameterized Constructor
		Deploy(Deploy& original); // Copy Constructor
		~Deploy(); // Default Destructor

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Deploy& operator = (const Deploy& D); 	// Assignment Operator
		friend ostream& operator<<(ostream& os, const Deploy& deploy); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute(); // Complete Implementation next assignment
};


class Advance : public Order{
	public:
		Advance(); // Default Constructor
		Advance(bool v, string s);  // Parameterized Constructor
		Advance(Advance& original); // Copy Constructor
		~Advance(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Advance& operator = (const Advance& d); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Advance& advance); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Bomb : public Order{
	public:
		Bomb(); // Default Constructor
		Bomb(bool v, string s);  // Parameterized Constructor
		Bomb(Bomb& original); // Copy Constructor
		~Bomb(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Bomb& operator = (const Bomb& D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Bomb& bomb); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Blockade : public Order{
	public:
		Blockade();  // Default Constructor
		Blockade(bool v, string s);  // Parameterized Constructor
		Blockade(Blockade& original); // Copy Constructor
		~Blockade(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Blockade& operator = (const Blockade& D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Blockade& blockade); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Airlift : public Order{
	public:
		Airlift();  // Default Constructor
		Airlift(bool v, string s);  // Parameterized Constructor
		Airlift(Airlift& original); // Copy Constructor
		~Airlift(); // Default Destructor 
		
		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Airlift& operator = (const Airlift &D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Airlift& airflit); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Negotiate : public Order{
	public:
		Negotiate();  // Default Constructor
		Negotiate(bool v, string s);  // Parameterized Constructor
		Negotiate(Negotiate& original); // Copy Constructor
		~Negotiate(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Negotiate& operator = (const Negotiate& D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Negotiate& negotiate); // stream insertion operator
		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Reinforcement : public Order{
	public:
		Reinforcement();  // Default Constructor
		Reinforcement(bool v, string s);  // Parameterized Constructor
		Reinforcement(Reinforcement& original); // Copy Constructor
		~Reinforcement(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Reinforcement& operator = (const Reinforcement& D); // Assignment Operator
		friend ostream& operator<<(ostream& os, const Reinforcement& reinforcement); // stream insertion operator

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class Diplomacy : public Order{
	public:
		Diplomacy();  // Default Constructor
		Diplomacy(bool v, string s);  // Parameterized Constructor
		Diplomacy(Diplomacy& original); // Copy Constructor
		~Diplomacy(); // Default Destructor 

		string getDescription(); bool getValidated(); // Accessors
		void setDescription(string d); void setValidated(bool v); // Mutators

		Diplomacy& operator = (const Diplomacy& D); // Assignment Operator 
		friend ostream& operator<<(ostream& description, const Diplomacy& diplomacy);

		string validate();  // Complete Implementation next assignment
		bool execute();  // Complete Implementation next assignment
};

class OrdersList {
	public: 
		vector<Order*> playerOrderList;
		bool allOrdersValidated;

		OrdersList(); // Default Constructor
		OrdersList(vector<Order*> vo, bool aov); // Parameterized Constructor
		OrdersList(OrdersList& original);  // Copy Constructor
		~OrdersList(); // Default Destructor 

		vector<Order*> getOrderList(); bool getAllOrdersValidated(); // Accessors
		void setOrderList(vector<Order*> vo); void setAllOrdersValidated(bool v); // Mutators

		OrdersList operator = (const OrdersList& original); // Assignment Operator
		friend ostream& operator<<(ostream& os, const OrdersList& ordersList); // stream insertion operator

		void addOrder(Order order); // Add Method used to add an order of the OrderList.
		void addOrder(Order* order); // Add Method used to add an order of the OrderList.
		void addOrder(string order); // Add Method used to add an order of the OrderList.
		void remove(int i); // Remove Method used to remove an order of the OrderList.
		void move(int i, int j); // Move Method used to move an order at index i into the position of index j.
};