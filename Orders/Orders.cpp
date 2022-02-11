#include "Orders.h"
#include <string>
/****************************** Order *******************************/
// Default Constructor
Order::Order(){
    this->validated = false;
    this->description = "";
}

Order::Order(bool v, string s){
    validated = v;
    description = s;
}; // Parameterized Constructor

// Copy Constructor
Order::Order(Order& original){
    validated = original.validated;
    description = original.description;
}
// Default Destructor
Order::~Order(){

}

// Accessors & Mutators
string Order::getDescription(){
    return description;
}

bool Order::getValidated(){
    return validated;
}

void Order::setDescription(string d){
    this->description = d;
}

void Order::setValidated(bool v){
    this->validated = v;
}

Order& Order::operator = (const Order& order){
    this->validated = order.validated;
    this->description = order.description;
    return *this;
}

ostream& operator<<(ostream& os, const Order& order){
    string validated = (order.validated)? "(validated)" : "(not validated)";
    os << order.description << " " << validated ;
	return os;
}

// Complete Implementation next assignment
bool Order::validate(){
    return (validated)? "validated" : "not validated";
}

//Implementation next assignment
bool Order::execute(){
    return true;
}

/****************************** Deploy *******************************/
// Default Constructor
Deploy::Deploy() : Order(false, "Deploy"){};

// Parameterized Constructor
Deploy::Deploy(bool v, string s) : Order(v,s){};

//Copy constructor
Deploy::Deploy(Deploy& original) : Order(original){
    this->description = "Deploy Armies into a territory";
}

// Default Destructor
Deploy::~Deploy(){};
// Accessors

string Deploy::getDescription(){
    return this->description;
}
bool Deploy::getValidated(){
    return this->validated;
}

// Mutators
void Deploy::setDescription(string d){
    this->description = d;
}
void Deploy::setValidated(bool v){
    this->validated = v;
}
Deploy& Deploy::operator = (const Deploy& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;}

ostream& operator<<(ostream& os, const Deploy& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;};

// Complete Implementation next assignment
string Deploy::validate(){
    return (validated)? "validated" : "not validated";
}

//Implementation next assignment
bool Deploy::execute(){
    return true;
}

/****************************** Advance *******************************/
// Default Constructor
Advance::Advance() : Order(false, "Advance"){};

// Parameterized Constructor
Advance::Advance(bool v, string s) : Order(v,s){};

// Copy Constructor
Advance::Advance(Advance& original) : Order(original){
    this->description = "Advance Armies into a territory";
}

// Default Destructor
Advance::~Advance(){};

// Accessors
string Advance::getDescription(){
    return this->description;

}
bool Advance::getValidated(){
    return this->validated;
}

// Mutators
void Advance::setDescription(string d){
    this->description = d;
}
void Advance::setValidated(bool v){
    this->validated = v;
}
Advance& Advance::operator = (const Advance& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Advance& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;
};

// Complete Implementation next assignment
string Advance::validate(){
    return (validated)? "validated" : "not validated";
}
//Implementation next assignment
bool Advance::execute(){
    return true;
}

/****************************** Bomb *******************************/
// Default Constructor
Bomb::Bomb() : Order(false, "Bomb"){};
// Parameterized Constructor
Bomb::Bomb(bool v, string s) : Order(v,s){};

// Copy Constructor
Bomb::Bomb(Bomb& original) : Order(original){
    this->description = "Bomb a territory";
}
// Default Destructor
Bomb::~Bomb(){};

// Accessors
string Bomb::getDescription(){
    return this->description;
}
bool Bomb::getValidated(){
    return this->validated;
}
// Mutators
void Bomb::setDescription(string d){
    this->description = d;
}
void Bomb::setValidated(bool v){
    this->validated = v;
}
Bomb& Bomb::operator = (const Bomb& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;
}
ostream& operator<<(ostream& os, const Bomb& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;
};

// Complete Implementation next assignment
string Bomb::validate(){
    return (validated)? "validated" : "not validated";
}
//Implementation next assignment
bool Bomb::execute(){
    return true;
}

/****************************** Blockade *******************************/
// Default Constructor
Blockade::Blockade() : Order(false, "Blockade"){};

// Parameterized Constructor
Blockade::Blockade(bool v, string s) : Order(v,s){};

// Copy Constructor
Blockade::Blockade(Blockade& original) : Order(original){
    this->description = "Create a blockade in a territory";
}

// Default Destructor
Blockade::~Blockade(){};

// Accessors
string Blockade::getDescription(){
    return this->description;
}

bool Blockade::getValidated(){
    return this->validated;
}

// Mutators
void Blockade::setDescription(string d){
    this->description = d;
}

void Blockade::setValidated(bool v){
    this->validated = v;
}

Blockade& Blockade::operator = (const Blockade& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;
}
ostream& operator<<(ostream& os, const Blockade& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;
}

// Complete Implementation next assignment
string Blockade::validate(){
    return (validated)? "validated" : "not validated";
}
//Implementation next assignment
bool Blockade::execute(){
    return true;
}

/****************************** Airlift *******************************/
// Default Constructor
Airlift::Airlift() : Order(false, "Airlift"){};

// Parameterized Constructor
Airlift::Airlift(bool v, string s): Order(v,s){};

// Copy Constructor
Airlift::Airlift(Airlift& original) : Order(original){
    this->description = "Airlift Armies into another territory";

}

// Default Destructor
Airlift::~Airlift(){};

// Accessors
string Airlift::getDescription(){
    return this->description;
}
bool Airlift::getValidated(){
    return this->validated;
}

// Mutators
void Airlift::setDescription(string d){
    this->description = d;
}

void Airlift::setValidated(bool v){
    this->validated = v;
}

Airlift& Airlift::operator = (const Airlift& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;}

ostream& operator<<(ostream& os, const Airlift& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;};

// Complete Implementation next assignment
string Airlift::validate(){
    return (validated)? "validated" : "not validated";
}

//Implementation next assignment
bool Airlift::execute(){
    return true;
}

/****************************** Negotiate *******************************/
// Default Constructor
Negotiate::Negotiate() : Order(false, "Negotiate"){};

// Parameterized Constructor
Negotiate::Negotiate(bool v, string s) : Order(v,s) {};

// Copy Constructor
Negotiate::Negotiate(Negotiate& original) : Order(original){
    this->description = "Negotiate with another Army";
}
// Default Destructor
Negotiate::~Negotiate(){};

// Accessors
string Negotiate::getDescription(){
    return this->description;
}

bool Negotiate::getValidated(){
    return this->validated;
}
// Mutators
void Negotiate::setDescription(string d){
    this->description = d;
}

void Negotiate::setValidated(bool v){
    this->validated = v;
}

Negotiate& Negotiate::operator = (const Negotiate& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Negotiate& o){
    string validated = (o.validated)? "(validated)" : "(not validated)";
    os << o.description << " "<< validated;
    return os;
}

// Complete Implementation next assignment
string Negotiate::validate(){
    return (validated)? "validated" : "not validated";
}

bool Negotiate::execute(){
    return true;
}

/****************************** Diplomacy *******************************/
// Default Constructor
Diplomacy::Diplomacy() : Order(false, "Diplomacy"){};

// Parameterized Constructor
Diplomacy::Diplomacy(bool v, string s) : Order(v,s) {} ;

// Copy Constructor
Diplomacy::Diplomacy(Diplomacy& original) : Order(original){
    this->description = "Diplomatic convention";
}

// Default Destructor
Diplomacy::~Diplomacy(){};

// Accessors
string Diplomacy::getDescription(){
    return this->description;

}
bool Diplomacy::getValidated(){
    return this->validated;
}

// Mutators
void Diplomacy::setDescription(string d){
    this->description = d;
}

void Diplomacy::setValidated(bool v){
    this->validated = v;
}

Diplomacy& Diplomacy::operator = (const Diplomacy& o){
    this->validated = o.validated;
    this->description = o.description;
    return *this;}

ostream& operator<<(ostream& os, const Diplomacy& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;
}

// Complete Implementation next assignment
string Diplomacy::validate(){
    return (validated)? "validated" : "not validated";
}
//Implementation next assignment
bool Diplomacy::execute() {
    return true;
}

/****************************** Reinforcement *******************************/
// Default Constructor
Reinforcement::Reinforcement() : Order(false, "Reinforcement"){};

// Parameterized Constructor
Reinforcement::Reinforcement(bool v, string s): Order(v,s){};

// Copy Constructor
Reinforcement::Reinforcement(Reinforcement& original) : Order(original){
    this->description = "Send reinforcement into a territory";
}

// Default Destructor
Reinforcement::~Reinforcement(){};

// Accessors
string Reinforcement::getDescription(){
    return this->description;
}

bool Reinforcement::getValidated(){
    return this->validated;
}
// Mutators
void Reinforcement::setDescription(string d){
    this->description = d;
}

void Reinforcement::setValidated(bool v){
    this->validated = v;
}

Reinforcement& Reinforcement::operator = (const Reinforcement& o){
    this->validated = o.validated; this->description = o.description;
    return *this;}

ostream& operator<<(ostream& os, const Reinforcement& o){
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description << " "<< validated;
    return os;
}
// Complete Implementation next assignment
string Reinforcement::validate(){
    return (validated)? "validated" : "not validated";
}
//Implementation next assignment
bool Reinforcement::execute(){
    return true;
}

/****************************** OrdersList *******************************/

// Default Constructor
OrdersList::OrdersList(){
    playerOrderList = vector<Order*>();
}

// Copy Constructor
OrdersList::OrdersList(OrdersList &original){
	for(int i= 0; i <= original.playerOrderList.size(); ++i){
		this->playerOrderList.push_back(new Order(*original.playerOrderList[i]));
	}
}

// Default Destructor
OrdersList::~OrdersList(){
	// Iterate through all pointed orders and delete the content in heap of each
	for(int i= 0; i <= this->playerOrderList.size(); ++i){
				delete(this->playerOrderList[i]);
				this->playerOrderList[i] = NULL;
			}
	// then delete the vector
	this->playerOrderList.clear();
}

// Assignment Operator overloading, will have the same behavior as the copy constructor. Deep copy of Vector through = operator.
OrdersList OrdersList::operator = (const OrdersList& original){
	OrdersList deepcopy;
	for(int i= 0; i <= original.playerOrderList.size(); ++i){
		deepcopy.playerOrderList.push_back(new Order(*original.playerOrderList[i]));
	}
	return deepcopy;
}

// stream insertion operator that outputs the OrdersList's vector
ostream& operator<<(ostream& os, const OrdersList& ordersList) {
//    int a = 1;
//    os << "Orders List:\n [";
//    for (auto i = ordersList.playerOrderList.cbegin(); i != ordersList.playerOrderList.cend(); ++i) {
//        cout << a << " : " << *i << "\n";
//        a++;
//    }
//    cout << "]" << endl;
    os << "Order List: \n";
    for(int i = 0; i < ordersList.playerOrderList.size(); i++){
        os << i << " - " << *(ordersList.playerOrderList.at(i)) << "\n";
    }
    return os;
}


// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order
void OrdersList::addOrder(Order order){
	playerOrderList.push_back(new Order(order));
}

void OrdersList::addOrder(Order* order){
	playerOrderList.push_back(order);
}

void OrdersList::addOrder(string orderString){
	Order* orderObject;
	// CONDITIONAL
	if (orderString == "deploy") {
        orderObject = new Deploy();
    }
	else if (orderString == "advance") {
        orderObject = new Advance();
    }
	else if (orderString == "bomb") {
        orderObject = new Bomb();
    }
	else if (orderString == "blockade") {
        orderObject = new Blockade();
    }
	else if (orderString == "airlift") {
        orderObject = new Negotiate();
    }
	else if (orderString == "diplomacy") {
        orderObject = new Diplomacy();
    }
	else cout << "wrong Order/Card type" << endl;

playerOrderList.push_back(orderObject);}

// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
void OrdersList::remove(int i){
	int j = 0;
			this->playerOrderList.erase( this->playerOrderList.begin() + i);
}
// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
void OrdersList::move(int i, int j){
    swap(this->playerOrderList[i],this->playerOrderList[j]);
}