#include "Orders.h"
using namespace std;

	Order::Order(){validated = false; description = "";}  // Default Constructor

	Order::Order(bool v, string s): validated(v), description(s){};  // Parameterized Constructor

	Order::Order(Order& original){validated = original.validated; description = original.description;} // Copy Constructor

	Order::~Order(){} // Default Destructor TODO not sure if no memory leak

	// Accessors
	string Order::getDescription(){return description;}
	bool Order::getValidated(){return validated;}

	// Mutators
	void Order::setDescription(string d){this->description = d;}
	void Order::setValidated(bool v){this->validated = v;}

	Order& Order::operator = (const Order& order){this->validated = new bool(order.validated); this->description = new string(order.description);}

	ostream& operator<<(ostream& os, Order& order){
		os << order.description << " validation: " << order.validated << endl;
		return os;
	};

	bool Order::validate(){}; 	//Implementation next assignment
	bool Order::execute(){}; 	//Implementation next assignment


	Deploy::Deploy(){}; // Default Constructor

	Deploy::Deploy(Deploy& original) : Order(original){};  // Copy Constructor

	Deploy::~Deploy(){delete validated;} // Default Destructor TODO not sure if no memory leak

	Deploy& Deploy::operator = (const Deploy& deploy){};

 	ostream& operator<<(ostream& os, Deploy& deploy){};

	bool Deploy::validate(){}; //Implementation next assignment
	bool Deploy::execute(){}; //Implementation next assignment


	Advance::Advance(){};
	Advance::Advance(Advance& original){};
	Advance::~Advance(){};
	void Advance::operator = (const Advance& advance){};
	ostream& operator<<(ostream& os, Advance& advance){};
	bool Advance::validate(){}; //Implementation next assignment
	bool Advance::execute(){}; //Implementation next assignment




	Bomb::Bomb(){};
	Bomb::Bomb(Bomb& original){};
	Bomb::~Bomb(){};
	void Bomb::operator = (const Bomb& bomb){};
	ostream& operator<<(ostream& os, Bomb& bomb){};
	bool Bomb::validate(){}; //Implementation next assignment
	bool Bomb::execute(){}; //Implementation next assignment
	


	Blockade::Blockade(){};
	Blockade::Blockade(Blockade& original){};
	Blockade::~Blockade(){};
	void Blockade::operator = (const Blockade& blockade){};
	ostream& operator<<(ostream& os, Blockade& blockade){};
	bool Blockade::validate(){}; //Implementation next assignment
	bool Blockade::execute(){}; //Implementation next assignment



	Airlift::Airlift(){};
	Airlift::Airlift(Airlift& original){};
	Airlift::~Airlift(){};
	void Airlift::operator = (const Airlift& airlift){};
	ostream& operator<<(ostream& os, Airlift& airflit);
	bool Airlift::validate(){}; //Implementation next assignment
	bool Airlift::execute(){}; //Implementation next assignment


	Negotiate::Negotiate(){};
	Negotiate::Negotiate(Negotiate& original){};
	Negotiate::~Negotiate(){};
	void Negotiate::operator = (const Negotiate &negotiate){};
	ostream& operator<<(ostream& os, Negotiate& negotiate);
	bool Negotiate::validate(){}; //Implementation next assignment
	bool Negotiate::execute(){}; //Implementation next assignment

	Diplomacy::Diplomacy(){};
	Diplomacy::Diplomacy(Diplomacy& original){};
	Diplomacy::~Diplomacy(){};
	void Diplomacy::operator = (const Diplomacy &diplomacy){};
	ostream& operator<<(ostream& os, Diplomacy& negotiate);
	bool Diplomacy::validate(){}; //Implementation next assignment
	bool Diplomacy::execute(){}; //Implementation next assignment

		Reinforcement::Reinforcement(){};
	Reinforcement::Reinforcement(Reinforcement& original){};
	Reinforcement::~Reinforcement(){};
	void Reinforcement::operator = (const Reinforcement& reinforcement){};
	ostream& operator<<(ostream& os, Reinforcement& reinforcement);
	bool Reinforcement::validate(){}; //Implementation next assignment
	bool Reinforcement::execute(){}; //Implementation next assignment

	// Default Constructor ************* HAVE TO ADD MEMORY ALLOCATION
	OrdersList::OrdersList(){
		std::vector<Order*> playerOrderList;
	};

	// Copy Constructor ************* 
	OrdersList::OrdersList(OrdersList &original){
		for(auto i=original.playerOrderList.cbegin(); i<= original.playerOrderList.cend(); ++i){
			this->playerOrderList.push_back(original.playerOrderList[i]);
		}
		playerOrderList = original.playerOrderList;
	};

	// Default Destructor ************* HAVE TO ADD MEMORY DE-ALLOCATION
	OrdersList::~OrdersList(){
		// Iterate through all pointed orders and delete each of them *************

		// then delete the vector
		this->playerOrderList.clear();
	};

	// Assignment Operator overloading, will have the same behavior as the copy constructor. Deep copy of Vector through = operator.
	OrdersList& OrdersList:: operator = (const OrdersList &originalOrderList){
		this->playerOrderList = originalOrderList.playerOrderList;
	};

	// stream insertion operator that outputs the Order List's vector 
	ostream& operator<<(ostream& os, OrdersList ordersList){
		int a = 1;
		os << "Order List:\n"; 
		for (auto i= ordersList.playerOrderList.cbegin(); i<= ordersList.playerOrderList.cend(); ++i){
			cout << a << " : " << ordersList.playerOrderList[i] << endl;
			a++;
		}
		return os;
	}

	// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order 
	void OrdersList::addOrder(Order order){};

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void OrdersList::remove(int i){
		// Order* j = playerOrderList.begin() + i;
		// this->playerOrderList.delete(j);
	};

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void OrdersList::move(int i, int j){};


