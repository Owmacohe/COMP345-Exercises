
#pragma once
#include <vector>
#include <iostream>
using namespace std;


class Order {
	public:
	bool* validated;

	public:
	Order();  // Default Constructor
	Order(bool* validated);  // Parameterized Constructor
	Order(Order& original); // Copy Constructor
	~Order(); // Default Destructor

	Order& operator = (const Order& D); // Assignment Operator 
	friend ostream& operator<<(ostream& os, Order& order); // stream insertion operator 

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
	
};

class Deploy : public Order{
	
	Deploy(); // Default Constructor
	Deploy(Deploy& original); // Copy Constructor
	~Deploy(); // Default Destructor

	Deploy& operator = (const Deploy& D); 	// Assignment Operator 
	friend ostream& operator<<(ostream& os, const Deploy& deploy); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};


class Advance : public Order{
	
	Advance(); // Default Constructor
	Advance(Advance& original); // Copy Constructor
	~Advance(); // Default Destructor 
	
	Advance& operator = (const Advance& D); // Assignment Operator 
	friend ostream& operator<<(ostream& os, Advance& advance); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Bomb : public Order{
	Bomb(); // Default Constructor
	Bomb(Bomb& original); // Copy Constructor
	~Bomb(); // Default Destructor 

	Bomb& operator = (const Bomb& D); // Assignment Operator 
	friend ostream& operator<<(ostream& os, Bomb& bomb); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Blockade : public Order{
	Blockade();  // Default Constructor
	Blockade(Blockade& original); // Copy Constructor
	~Blockade(); // Default Destructor 

	Blockade& operator = (const Blockade& D); // Assignment Operator 
	friend ostream& operator<<(ostream& os, Blockade& blockade); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Airlift : public Order{
	Airlift();  // Default Constructor
	Airlift(Airlift& original); // Copy Constructor
	~Airlift(); // Default Destructor 
	
	Airlift& operator = (const Airlift &D); // Assignment Operator 
	friend ostream& operator<<(ostream& os, Airlift& airflit); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Negotiate : public Order{
	Negotiate();  // Default Constructor
	Negotiate(Negotiate& original); // Copy Constructor
	~Negotiate(); // Default Destructor 

	Negotiate& operator = (const Negotiate& D); // Assignment Operator
	friend ostream& operator<<(ostream& os, Negotiate& negotiate); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Reinforcement : public Order{
	Reinforcement();  // Default Constructor
	Reinforcement(Reinforcement& original); // Copy Constructor
	~Reinforcement(); // Default Destructor 

	Reinforcement& operator = (const Reinforcement& D); // Assignment Operator
	friend ostream& operator<<(ostream& os, Reinforcement& reinforcement); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class Diplomacy : public Order{
	Diplomacy();  // Default Constructor
	Diplomacy(Diplomacy& original); // Copy Constructor
	~Diplomacy(); // Default Destructor 

	Diplomacy& operator = (const Diplomacy& D); // Assignment Operator
	friend ostream& operator<<(ostream& description, Diplomacy& diplomacy); // stream insertion operator  

	bool validate(); //Implementation next assignment
	bool execute(); //Implementation next assignment
};

class OrdersList {

	public: 
	vector<Order*> playerOrderList;

	public:
	OrdersList(); // Default Constructor
	OrdersList(OrdersList& original);  // Copy Constructor
	~OrdersList(); // Default Destructor 

	OrdersList& operator = (const OrdersList& original); // Assignment Operator
	friend ostream& operator<<(ostream& os, OrdersList& ordersList); // stream insertion operator
	
	void addOrder(Order order); // Add Method used to add an order of the OrderList.
	void remove(int i); // Remove Method used to remove an order of the OrderList.
	void move(int i, int j); // Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.

};