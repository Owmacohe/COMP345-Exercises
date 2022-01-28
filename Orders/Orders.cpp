#include "Orders.h"
using namespace std;

	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	OrdersList::OrdersList(){
		std::vector<Order>* playerOrderList = new vector<Order>;
	};

	// Copy Constructor ************* 
	OrdersList::OrdersList(OrdersList& original){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	OrdersList::~OrdersList(){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void OrdersList:: operator = (const OrdersList &D){};

	// stream insertion operator that outputs the Order List's vector SYNTAX ERROR< WILL RECHECK AFTER FRIEND COURSE 
	//OrdersList::friend std::ostream& operator<<(ostream& description, OrdersList ordersList){};

	// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order 
	void OrdersList::add(Order order){};

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void OrdersList::remove(int i){};

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void OrdersList::move(int i, int j){};



	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Order::Order(){};

	// Copy Constructor ************* 
	Order::Order(Order& original){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	Order::~Order(){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void Order::operator = (const Order &D){};

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	//friend std::ostream& operator<<(ostream& description, Order order){};

	bool Order::validate(){};
	//Implementation next assignment

	bool Order::execute(){};
	//Implementation next assignment



	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Deploy::Deploy(){};

	// Copy Constructor ************* 
	Deploy::Deploy(Deploy& original){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	Deploy::~Deploy(){};

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	//Deploy::friend std::ostream& operator<<(ostream& description, Deploy deploy){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void Deploy::operator = (const Deploy &D){};

	bool Deploy::validate(){};
	//Implementation next assignment

	bool Deploy::execute(){};
	//Implementation next assignment, will include the destructor of the Order



	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Advance::Advance(){};

	// Copy Constructor ************* 
	Advance::Advance(Advance& original){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	Advance::~Advance(){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void Advance::operator = (const Advance &D){};

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	Advance::friend std::ostream& operator<<(ostream& description, Advance advance){};

	bool Advance::validate(){};
	//Implementation next assignment

	bool Advance::execute(){};
	//Implementation next assignment



	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Bomb::Bomb(){};

	// Copy Constructor ************* 
	Bomb::Bomb(Bomb& original){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	Bomb::~Bomb(){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void Bomb::operator = (const Bomb &D){};

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	//Bomb::friend std::ostream& operator<<(ostream& description, Bomb bomb){};

	bool Bomb::validate(){};
	//Implementation next assignment

	bool Bomb::execute(){};
	//Implementation next assignment



	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	Blockade::Blockade(){};

	// Copy Constructor ************* 
	Blockade::Blockade(Blockade& original){};

	// Assignment Operator overloading, will have the same behavior as the copy constructor
	void Blockade::operator = (const Blockade &D){};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	Blockade::~Blockade(){};

	// stream insertion operator that output strings description of order and effect of the order if correctly executed
	//Blockade::friend std::ostream& operator<<(ostream& description, Blockade blockade){};

	bool Blockade::validate(){};
	//Implementation next assignment

	bool Blockade::execute(){};
	//Implementation next assignment

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