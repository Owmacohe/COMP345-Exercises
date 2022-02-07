#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;
	
	Order::Order(){this->validated = false; this->description = "";}  // Default Constructor
	Order::Order(bool v, string s): validated(v), description(s){};  // Parameterized Constructor
	Order::Order(Order& original){validated = original.validated; description = original.description;} // Copy Constructor
	Order::~Order(){} // Default Destructor

	// Accessors & Mutators
	string Order::getDescription(){return description;}
	bool Order::getValidated(){return validated;}
	void Order::setDescription(string d){this->description = d;}
	void Order::setValidated(bool v){this->validated = v;}

	Order& Order::operator = (const Order& order){this->validated = order.validated; this->description = order.description;}
	ostream& operator<<(ostream& os, Order& order){
		os << order.description << " validated: " << order.validated << endl; 
		return os;}

	bool Order::validate(){}; 	//Implementation next assignment
	bool Order::execute(){}; 	//Implementation next assignment


	Deploy::Deploy(){}; // Default Constructor
	Deploy::Deploy(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Deploy::Deploy(Deploy& original) : Order(original){this->description = "Deploy Armies into a territory";}  // Copy Constructor
	Deploy::~Deploy(){} // Default Destructor
	// Accessors
	string Deploy::getDescription(){return this->description;}
	bool Deploy::getValidated(){return this->validated;} 
	 // Mutators
	void Deploy::setDescription(string d){this->description = d;}
	void Deploy::setValidated(bool v){this->validated = v;}
	Deploy& Deploy::operator = (const Deploy& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Deploy& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Deploy::validate(){}; //Implementation next assignment
	bool Deploy::execute(){}; //Implementation next assignment


	Advance::Advance(){}; // Default Constructor
	Advance::Advance(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Advance::Advance(Advance& original) : Order(original){this->description = "Advance Armies into a territory";}  // Copy Constructor
	Advance::~Advance(){} // Default Destructor
	// Accessors
	string Advance::getDescription(){return this->description;}
	bool Advance::getValidated(){return this->validated;} 
	// Mutators
	void Advance::setDescription(string d){this->description = d;}
	void Advance::setValidated(bool v){this->validated = v;}
	Advance& Advance::operator = (const Advance& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Advance& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Advance::validate(){}; //Implementation next assignment
	bool Advance::execute(){}; //Implementation next assignment

	
	Bomb::Bomb(){}; // Default Constructor
	Bomb::Bomb(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Bomb::Bomb(Bomb& original) : Order(original){this->description = "Bomb a territory";}  // Copy Constructor
	Bomb::~Bomb(){} // Default Destructor
	// Accessors
	string Bomb::getDescription(){return this->description;}
	bool Bomb::getValidated(){return this->validated;} 
	// Mutators
	void Bomb::setDescription(string d){this->description = d;}
	void Bomb::setValidated(bool v){this->validated = v;}
	Bomb& Bomb::operator = (const Bomb& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Bomb& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Bomb::validate(){}; //Implementation next assignment
	bool Bomb::execute(){}; //Implementation next assignment


	Blockade::Blockade(){}; // Default Constructor
	Blockade::Blockade(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Blockade::Blockade(Blockade& original) : Order(original){this->description = "Create a blockade in a territory";}  // Copy Constructor
	Blockade::~Blockade(){} // Default Destructor
	// Accessors
	string Blockade::getDescription(){return this->description;}
	bool Blockade::getValidated(){return this->validated;} 
	// Mutators
	void Blockade::setDescription(string d){this->description = d;}
	void Blockade::setValidated(bool v){this->validated = v;}
	Blockade& Blockade::operator = (const Blockade& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Blockade& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Blockade::validate(){}; //Implementation next assignment
	bool Blockade::execute(){}; //Implementation next assignment


	Airlift::Airlift(){}; // Default Constructor
	Airlift::Airlift(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Airlift::Airlift(Airlift& original) : Order(original){this->description = "Airlift Armies into another territory";}  // Copy Constructor
	Airlift::~Airlift(){} // Default Destructor
	// Accessors
	string Airlift::getDescription(){return this->description;}
	bool Airlift::getValidated(){return this->validated;} 
	// Mutators
	void Airlift::setDescription(string d){this->description = d;}
	void Airlift::setValidated(bool v){this->validated = v;}
	Airlift& Airlift::operator = (const Airlift& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Airlift& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Airlift::validate(){}; //Implementation next assignment
	bool Airlift::execute(){}; //Implementation next assignment


	Negotiate::Negotiate(){}; // Default Constructor
	Negotiate::Negotiate(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Negotiate::Negotiate(Negotiate& original) : Order(original){this->description = "Negotiate with another Army";}  // Copy Constructor
	Negotiate::~Negotiate(){} // Default Destructor
	// Accessors
	string Negotiate::getDescription(){return this->description;}
	bool Negotiate::getValidated(){return this->validated;} 
	// Mutators
	void Negotiate::setDescription(string d){this->description = d;}
	void Negotiate::setValidated(bool v){this->validated = v;}
	Negotiate& Negotiate::operator = (const Negotiate& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Negotiate& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Negotiate::validate(){}; //Implementation next assignment
	bool Negotiate::execute(){}; //Implementation next assignment


	Diplomacy::Diplomacy(){}; // Default Constructor
	Diplomacy::Diplomacy(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Diplomacy::Diplomacy(Diplomacy& original) : Order(original){this->description = "Diplomatic convention";}  // Copy Constructor
	Diplomacy::~Diplomacy(){} // Default Destructor
	// Accessors
	string Diplomacy::getDescription(){return this->description;}
	bool Diplomacy::getValidated(){return this->validated;} 
	// Mutators
	void Diplomacy::setDescription(string d){this->description = d;}
	void Diplomacy::setValidated(bool v){this->validated = v;}
	Diplomacy& Diplomacy::operator = (const Diplomacy& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Diplomacy& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Diplomacy::validate(){}; //Implementation next assignment
	bool Diplomacy::execute(){}; //Implementation next assignment


	Reinforcement::Reinforcement(){}; // Default Constructor
	Reinforcement::Reinforcement(bool v, string s){ Order(v,s);} // Parameterized Constructor
	Reinforcement::Reinforcement(Reinforcement& original) : Order(original){this->description = "Send reinforcement into a territory";}  // Copy Constructor
	Reinforcement::~Reinforcement(){} // Default Destructor
	// Accessors
	string Reinforcement::getDescription(){return this->description;}
	bool Reinforcement::getValidated(){return this->validated;} 
	// Mutators
	void Reinforcement::setDescription(string d){this->description = d;}
	void Reinforcement::setValidated(bool v){this->validated = v;}
	Reinforcement& Reinforcement::operator = (const Reinforcement& o){this->validated = o.validated; this->description = o.description;}
 	ostream& operator<<(ostream& os, Reinforcement& o){ os << o.description << " validated: " << o.validated << endl; return os;};
	bool Reinforcement::validate(){}; //Implementation next assignment
	bool Reinforcement::execute(){}; //Implementation next assignment



	// Default Constructor
	OrdersList::OrdersList(){vector<Order*> playerOrderList;};

	// Copy Constructor 
	OrdersList::OrdersList(OrdersList& original){
		for(auto i=original.playerOrderList.cbegin(); i!= original.playerOrderList.cend(); ++i){
		//	this->playerOrderList.push_back(new Order(i)); // Dereference i? TODO
		}
		playerOrderList = original.playerOrderList;
	};

	// Default Destructor 
	OrdersList::~OrdersList(){
		// Iterate through all pointed orders and delete the content in heap of each
	for (auto i= this->playerOrderList.cbegin(); i != this->playerOrderList.cend(); ++i){
			//TODO DELETE ORDERS OBJETC IN HEAP
		}
		// then delete the vector
		this->playerOrderList.clear();
	};

	// Assignment Operator overloading, will have the same behavior as the copy constructor. Deep copy of Vector through = operator.
	OrdersList OrdersList::operator = (const OrdersList& original){
		
		OrdersList deepcopy;
		for(auto i=original.playerOrderList.cbegin(); i!= original.playerOrderList.cend(); ++i){
			//deepcopy.playerOrderList.push_back(new Order(i)); // TODO ERROR??
		}

	};

	// stream insertion operator that outputs the Order List's vector 
	ostream& operator<<(ostream& os, OrdersList ordersList){
		int a = 1;
		os << "Orders List:\n [" ; 
		for (auto i= ordersList.playerOrderList.cbegin(); i != ordersList.playerOrderList.cend(); ++i){
			cout << a << " : " << *i << "\n";
			a++;
		}
		cout << "]"<< endl;
		return os;
	}

	// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order 
	void OrdersList::addOrder(Order order){
		playerOrderList.push_back(new Order(order));}

	void OrdersList::addOrder(Order* order){
		playerOrderList.push_back(order);}

	void OrdersList::addOrder(string orderString){
		Order* orderObject;
		// CONDITIONAL
		if (orderString == "deploy") {orderObject = new Deploy();}
		else if (orderString == "advance") {orderObject = new Advance();}
		else if (orderString == "bomb") {orderObject = new Bomb();}
		else if (orderString == "blockade") {orderObject = new Blockade();}
		else if (orderString == "airlift") {orderObject = new Airlift();}
		else if (orderString == "negotiate") {orderObject = new Negotiate();}
		else if (orderString == "diplomacy") {orderObject = new Diplomacy();}
		else cout << "wrong Order/Card type" << endl;

	playerOrderList.push_back(orderObject);}

	// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
	void OrdersList::remove(int i){
		this->playerOrderList[i];
		// TODO
	};

	// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
	void OrdersList::move(int i, int j){
		Order* swap1 = this->playerOrderList[i];
		Order* swap2 = this->playerOrderList[j];
		Order* swap3;

		swap3 = swap1;
		swap1 = swap2;
		swap2 = swap3;
		// Did not use new, once out of scope, pointer swap3 is delete, no memory leak
	};


