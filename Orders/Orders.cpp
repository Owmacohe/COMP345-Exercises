#include "Orders.h"
#include <string>

/****************************** Order *******************************/

// Default constructor
Order::Order() {
    validated = false;
    description = "";
}

// Parameterized constructor
Order::Order(bool v, string s) {
    validated = v;
    description = s;
};

// Copy constructor
Order::Order(Order& original) {
    validated = original.validated;
    description = original.description;
}

// Destructor
Order::~Order() { }

// Accessors
string Order::getDescription() { return description; }
bool Order::getValidated() { return validated; }

// Mutators
void Order::setDescription(string d) {
    description = d;
}
void Order::setValidated(bool v) {
    validated = v;
}

Order& Order::operator = (const Order& order) {
    validated = order.validated;
    description = order.description;
    return *this;
}

ostream& operator<<(ostream& os, const Order& order) {
    string validated = (order.validated)? "(validated)" : "(not validated)";
    os << order.description ;
	return os;
}

// Complete implementation next assignment
bool Order::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Order::execute() {
    cout << "Executing Order" << endl;
    notify(this); // FROM SUBJECT
    return true;
}

// From Iloggable
string Order::stringToLog(){
    string logString = "The Order has been executed.\n";
    return logString;}

/****************************** Deploy *******************************/

// Default constructor
Deploy::Deploy() : Order(false, "Deploy") { };

// Parameterized constructor
Deploy::Deploy(bool v, string s) : Order(v,s) { };

Deploy::Deploy(Deploy& original) : Order(original) {
    description = "Deploy Armies into a territory";
}

// Destructor
Deploy::~Deploy() { };

// Accessors
string Deploy::getDescription() { return description; }
bool Deploy::getValidated() { return validated; }

// Mutators
void Deploy::setDescription(string d) {
    description = d;
}
void Deploy::setValidated(bool v) {
    validated = v;
}

Deploy& Deploy::operator = (const Deploy& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Deploy& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description;
    return os;
}

// Complete implementation next assignment
string Deploy::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Deploy::execute() {
    cout << "Executing Order Deploy" << endl;
    return true;
}

/****************************** Advance *******************************/

// Default constructor
Advance::Advance() : Order(false, "Advance") { };

// Parameterized constructor
Advance::Advance(bool v, string s) : Order(v,s) { };

// Copy constructor
Advance::Advance(Advance& original) : Order(original) {
    description = "Advance Armies into a territory";
}

// Destructor
Advance::~Advance() { };

// Accessors
string Advance::getDescription() { return description; }
bool Advance::getValidated() { return validated; }

// Mutators
void Advance::setDescription(string d) {
    description = d;
}
void Advance::setValidated(bool v) {
    validated = v;
}

Advance& Advance::operator = (const Advance& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Advance& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description ;
    return os;
}

// Complete implementation next assignment
string Advance::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Advance::execute() {
    cout << "Executing Order Advance" << endl;
    return true;
}

/****************************** Bomb *******************************/

// Default constructor
Bomb::Bomb() : Order(false, "Bomb") { };

// Parameterized constructor
Bomb::Bomb(bool v, string s) : Order(v,s) { };

// Copy constructor
Bomb::Bomb(Bomb& original) : Order(original) {
    description = "Bomb a territory";
}

// Destructor
Bomb::~Bomb() { };

// Accessors
string Bomb::getDescription() { return description; }
bool Bomb::getValidated() { return validated; }

// Mutators
void Bomb::setDescription(string d) {
    description = d;
}
void Bomb::setValidated(bool v) {
    validated = v;
}

Bomb& Bomb::operator = (const Bomb& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Bomb& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description;
    return os;
}

// Complete implementation next assignment
string Bomb::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Bomb::execute() {
    cout << "Executing Order Bomb" << endl;
    return true;
}

/****************************** Blockade *******************************/

// Default constructor
Blockade::Blockade() : Order(false, "Blockade") { };

// Parameterized constructor
Blockade::Blockade(bool v, string s) : Order(v,s) { };

// Copy constructor
Blockade::Blockade(Blockade& original) : Order(original) {
    description = "Create a blockade in a territory";
}

// Destructor
Blockade::~Blockade() { };

// Accessors
string Blockade::getDescription() { return description; }
bool Blockade::getValidated() { return validated; }

// Mutators
void Blockade::setDescription(string d) {
    description = d;
}
void Blockade::setValidated(bool v) {
    validated = v;
}

Blockade& Blockade::operator = (const Blockade& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Blockade& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description ;
    return os;
}

// Complete implementation next assignment
string Blockade::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Blockade::execute() {
    cout << "Executing Order Blockade" << endl;
    return true;
}

/****************************** Airlift *******************************/

// Default constructor
Airlift::Airlift() : Order(false, "Airlift") { };

// Parameterized constructor
Airlift::Airlift(bool v, string s): Order(v,s) { };

// Copy constructor
Airlift::Airlift(Airlift& original) : Order(original) {
    description = "Airlift Armies into another territory";
}

// Destructor
Airlift::~Airlift() { };

// Accessors
string Airlift::getDescription() { return description; }
bool Airlift::getValidated() { return validated; }

// Mutators
void Airlift::setDescription(string d) {
    description = d;
}
void Airlift::setValidated(bool v) {
    validated = v;
}

Airlift& Airlift::operator = (const Airlift& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Airlift& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description ;
    return os;
}

// Complete implementation next assignment
string Airlift::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Airlift::execute() {
    cout << "Executing Order Execute" << endl;
    return true;
}

/****************************** Negotiate *******************************/

// Default constructor
Negotiate::Negotiate() : Order(false, "Negotiate") { };

// Parameterized constructor
Negotiate::Negotiate(bool v, string s) : Order(v,s) { };

// Copy constructor
Negotiate::Negotiate(Negotiate& original) : Order(original) {
    description = "Negotiate with another Army";
}

// Destructor
Negotiate::~Negotiate() { };

// Accessors
string Negotiate::getDescription() { return description; }
bool Negotiate::getValidated() { return validated; }

// Mutators
void Negotiate::setDescription(string d) {
    description = d;
}
void Negotiate::setValidated(bool v) {
    validated = v;
}

Negotiate& Negotiate::operator = (const Negotiate& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Negotiate& o) {
    string validated = (o.validated)? "(validated)" : "(not validated)";
    os << o.description;
    return os;
}

// Complete implementation next assignment
string Negotiate::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Negotiate::execute() {
    cout << "Executing Order Negotiate" << endl;
    return true;
}

/****************************** Diplomacy *******************************/

// Default constructor
Diplomacy::Diplomacy() : Order(false, "Diplomacy") { };

// Parameterized constructor
Diplomacy::Diplomacy(bool v, string s) : Order(v,s) { } ;

// Copy constructor
Diplomacy::Diplomacy(Diplomacy& original) : Order(original) {
    description = "Diplomatic convention";
}

// Destructor
Diplomacy::~Diplomacy() { };

// Accessors
string Diplomacy::getDescription() { return description; }
bool Diplomacy::getValidated() { return validated; }

// Mutators
void Diplomacy::setDescription(string d) {
    description = d;
}
void Diplomacy::setValidated(bool v) {
    validated = v;
}

Diplomacy& Diplomacy::operator = (const Diplomacy& o) {
    validated = o.validated;
    description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Diplomacy& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description;
    return os;
}

// Complete implementation next assignment
string Diplomacy::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Diplomacy::execute() {
    cout << "Executing Order Diplomacy" << endl;
    return true;
}

/****************************** Reinforcement *******************************/

// Default constructor
Reinforcement::Reinforcement() : Order(false, "Reinforcement") { };

// Parameterized constructor
Reinforcement::Reinforcement(bool v, string s): Order(v,s) { };

// Copy constructor
Reinforcement::Reinforcement(Reinforcement& original) : Order(original) {
    description = "Send reinforcement into a territory";
}

// Destructor
Reinforcement::~Reinforcement() { };

// Accessors
string Reinforcement::getDescription() { return description; }
bool Reinforcement::getValidated() { return validated; }

// Mutators
void Reinforcement::setDescription(string d) {
    description = d;
}
void Reinforcement::setValidated(bool v) {
    validated = v;
}

Reinforcement& Reinforcement::operator = (const Reinforcement& o) {
    validated = o.validated; description = o.description;
    return *this;
}

ostream& operator<<(ostream& os, const Reinforcement& o) {
    string validated = (o.validated)? " (validated)" : " (not validated)";
    os << o.description;
    return os;
}

// Complete implementation next assignment
string Reinforcement::validate() {
    return (validated)? "validated" : "not validated";
}

// Complete implementation next assignment
bool Reinforcement::execute() {
    cout << "Executing Order Reinforcement" << endl;
    return true;
}

/****************************** OrdersList *******************************/

// Default constructor
OrdersList::OrdersList() {
    playerOrderList = vector<Order*>();
}

// Parameterized constructor
OrdersList::OrdersList(vector<Order*> vo, bool aov) {
    playerOrderList = vector<Order*>();
    
    for (Order* i : vo) {
        playerOrderList.push_back(new Order(*i));
    }
    
    allOrdersValidated = aov;
}

// Copy constructor
OrdersList::OrdersList(OrdersList &original) {
    playerOrderList = vector<Order*>();
    
    for (Order* i : original.playerOrderList) {
        playerOrderList.push_back(new Order(*i));
    }

    allOrdersValidated = original.allOrdersValidated;
}

// Destructor
OrdersList::~OrdersList() {
	// Iterate through all pointed orders and delete the content in heap of each
    for (Order* i : playerOrderList) {
        delete i;
        i = NULL;
        //cout << "deleting an order in OrdersList" <<endl;
    }
    
	// then delete the vector
	playerOrderList.clear();
    //cout << "deleted OrdersList" <<endl;
}

// Assignment Operator overloading, will have the same behavior as the Copy constructor. Deep copy of Vector through = operator.
OrdersList OrdersList::operator = (const OrdersList& original) {
	OrdersList deepcopy;

    for (Order* i : original.playerOrderList) {
       deepcopy.playerOrderList.push_back(new Order(*i));
       cout << "DEBUG : for loop inside assignment operator" <<endl;
    }
	return deepcopy;
}

// stream insertion operator that outputs the OrdersList's vector
ostream& operator<<(ostream& os, const OrdersList& ordersList) {
    os << "Order List (size: " << ordersList.playerOrderList.size() << " ): \n";
    for(int i = 0; i < ordersList.playerOrderList.size(); i++) {
        os << i << " - " << *(ordersList.playerOrderList.at(i)) << " | ";
    }
    return os;
}

// Add Method used to add an order of the OrderList. The Parameter is an object from a subclass of Order. Overloaded method to increase compatibility with other classes.
void OrdersList::addOrder(Order order) {
	playerOrderList.push_back(new Order(order));
}

void OrdersList::addOrder(Order* order) {
	playerOrderList.push_back(order);
}

void OrdersList::addOrder(string orderString) {
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
	else {
        cout << "wrong Order/Card type" << endl;
    }

    playerOrderList.push_back(orderObject);
}

// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
void OrdersList::remove(int i) {
	int j = 0;
	playerOrderList.erase( playerOrderList.begin() + i);
}

// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
void OrdersList::move(int i, int j) {
    //Case 1: Moving Order downwards
    if (i > j) {
        for(j; j<i;j++) {
            swap(playerOrderList[i],playerOrderList[j]);}
    }
    //Case 2: Moving Order Upwards
    else if (i < j) {
        for(j; j>i; j--) {
            swap(playerOrderList[i],playerOrderList[j]);}
    }
    else {
        cout<<" wrong order index or wrong destination index" <<endl;
    }
}