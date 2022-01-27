#include "Orders.h"

class OrdersList {
	// VECTOR OR ORDER POINTERS????? *************
	public: 
		std::vector<Order> playerOrderList; // Vector is similar to an ArrayList from Java. Non contiguous memory cells. Access with index.

	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	OrdersList();

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~OrdersList();

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void remove(int i);

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void move(int i, int j);

	// stream insertion operator that outputs the Order List's vector
	friend std::ostream& operator<<(ostream& description, Order order);
};

class Order {
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Order();

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Order();

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

		// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Deploy();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Deploy deploy);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};

class Advance : public Order{
	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Advance();

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Advance();

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

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Bomb();

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

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Airlift();

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

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	~Negotiate();

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	friend std::ostream& operator<<(ostream& description, Negotiate negotiate);

	bool validate();
	//Implementation next assignment

	bool execute();
	//Implementation next assignment
};