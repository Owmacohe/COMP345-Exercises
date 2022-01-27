
#pragma once
#include <vector>
#include <iostream>
using namespace std;

class OrdersList {
	// POINTER TO VECTOR which contains Order object (also pointers) *************
	public: 
		std::vector<Order>* playerOrderList; // Vector is similar to an ArrayList from Java. Non contiguous memory cells. Access with index.

	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	OrdersList();

	// Copy Constructor ************* 
	OrdersList(OrdersList& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~OrdersList();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const OrdersList &D);

	// stream insertion operator that outputs the Order List's vector
	friend std::ostream& operator<<(ostream& description, OrdersList ordersList);

	// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order
	void add(Order order);

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void remove(int i);

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void move(int i, int j);


};

class Order {
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Order();

	// Copy Constructor ************* 
	Order(Order& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Order();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Order &D);

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Deploy : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Deploy();

	// Copy Constructor ************* 
	Deploy(Deploy& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Deploy();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Deploy deploy);

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Deploy &D);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment, will include the destructor of the Order
};

class Advance : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Advance();

	// Copy Constructor ************* 
	Advance(Advance& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Advance();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Advance &D);

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Advance advance);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Bomb : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Bomb();

	// Copy Constructor ************* 
	Bomb(Bomb& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Bomb();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Bomb &D);

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Bomb bomb);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Blockade : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Blockade();

	// Copy Constructor ************* 
	Blockade(Blockade& original);

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Blockade &D);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Blockade();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Blockade blockade);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Airlift : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Airlift();

	// Copy Constructor ************* 
	Airlift(Airlift& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Airlift();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Airlift &D);

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Airlift airflit);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Negotiate : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Negotiate();

	// Copy Constructor ************* 
	Negotiate(Negotiate& original);

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Negotiate();

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void operator = (const Negotiate &D);

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Negotiate negotiate);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};