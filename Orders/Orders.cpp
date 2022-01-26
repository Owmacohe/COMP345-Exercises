#include "Orders.h"


#pragma once
#include <vector>
#include <iostream>
using namespace std;

class OrdersList {
	public: 
		std::vector<Order> playerOrderList; // Vector is similar to an ArrayList fro Java. Non contiguous memory cells. Access with index.

	// Default Constructor
	OrdersList();

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void remove(int i);

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void move(int i, int j);

};

class Order {
	// Default Constructor
	Order();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Deploy : public Order{
	// Default Constructor
	Deploy();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Advance : public Order{
	// Default Constructor
	Advance();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Bomb : public Order{
	// Default Constructor
	Bomb();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Blockade : public Order{
	// Default Constructor
	Blockade();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Airlift : public Order{
	// Default Constructor
	Airlift();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Negotiate : public Order{
	// Default Constructor
	Negotiate();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Order order);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};