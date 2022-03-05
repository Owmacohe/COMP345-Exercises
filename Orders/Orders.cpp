#include "Orders.h"
#include "../LoggingObserver/LoggingObserver.h"

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

bool Order::validate() { } // Virtual Method

bool Order::execute() {
    cout << "Executing Order" << endl;
    notify(this); // FROM SUBJECT
    return true;
}

// From Iloggable
string Order::stringToLog() {
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


bool Deploy::validate() {
    /*
     * Check if Territory belongs to the player that issued the Order ----> So each Order has a Player* & each OrderList has a Player*
     */
    return validated;
}


bool Deploy::execute() {
    int armiesForDeployment;
    /* Maybe ask for input of the player for the number of armies for deployment or is it a standard number?
     * Validate number here? make sure its <= than the Player's reinforcement pool Or Change Validate to receive int armies and Territory
     * will call validate() to check Territory
     * if false, print out invalid
     * if true, add armiesForDeployment to the Territory and remove it from the Player's Reinforcement pool
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Deploy::stringToLog() {
    string logString = "Create log string for execution of deploy.\n";
    return logString;}


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


bool Advance::validate() { // there are 3 options: valid, invalid and ATTACK
    /*
     * Check if Territory B belongs to player return 1
     * Check if Territory A is adjacent to territory B return 1
     *
     * If territory B belong to player and is adjacent return 2
     *
     * If Territory B is another Player's return 3
     */
    return validated;
}


bool Advance::execute() {
    /*
     * ask input from the player for number of armies moved, Territory A and Territory B
     * call validate() --> Change method to accept armies, Territory A and Territory B ?
     * if 1 print invalid order
     * if 2 remove armies from Territory A and add them to Territory B
     *  if 3 ATTACK
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Advance::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;}

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


bool Bomb::validate() {
    /*
     * Check that Territory A is not the Player's
     * Check that Territory A is adjacent to one of the Player's
     * if all good, return true, else false
     */
    return validated;
}


bool Bomb::execute() {
    /*
     * Can only be played with a CARD so remove it from IssueOrder in Player
     * Ask player for Territory A
     * validate()
     * if false, invalid order
     * if true, /2 armies in the other Player's Territory A
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Bomb::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;}

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


bool Blockade::validate() {
    /*
     * Check if Territory A belong to the player
     * if no, return false
     * if yes, return true
     */
    return validated;
}


bool Blockade::execute() {
    /*
     *  Can only be played with a CARD so remove it from IssueOrder in Player
     *  ask the player for a Territory A
     *  validate()
     *  if false, invalid order
     *  if true, make armies in territory x2 and make 'Neutral Player owner of that'
     *  Maybe create Neutral Player here (or at startup of game)
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Blockade::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;}

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


bool Airlift::validate() {
    /*
     * check that A and B are the Player's territories
     * return true
     * else false
     */
    return validated;
}


bool Airlift::execute() {
    /*
     * Can only be played with a CARD so remove it from IssueOrder in Player
     * Ask player for Territory A, Territory B and int armies
     * validate()
     *if false, order invalid
     * if true, remove armies from Territory A and add them to Territory B
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Airlift::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;}

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


bool Negotiate::validate() {
    /*
     * Check if the player name submitted is not the same as the player that issued the order
     * (Check if its not the neutral player....?)
     * return true if ok
     * else false
     */
    return validated;
}


bool Negotiate::execute() {
    /*
     * Can only be played with a DIPLOMACY CARD so remove it from IssueOrder in Player
     * Ask player for another player name
     * validate()
     * if false, invalid order
     * if true make any attack from Player A to Player B and vice-versa invalid until end of turn (probably until reinforcement phase)
     * Maybe add a List of Player* as an attribute in PLayer to keep track of who has a truce with who.
     * In this case, this adds Player A to Player B's list and vice-versa
     * Lists must be cleared when goes to reinforcement phase
     */
    notify(this); // FROM SUBJECT
    return true;
}

string Negotiate::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;
}

/****************************** Reinforcement *******************************/ // I THINK WE CAN DELETE THIS

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

bool Reinforcement::validate() {
    return validated;
}

bool Reinforcement::execute() {
    cout << "Executing Order Reinforcement" << endl;
    notify(this); // FROM SUBJECT
    return true;
}

string Reinforcement::stringToLog() {
    string logString = "Create log string for execution.\n";
    return logString;
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
    notify(this); // FROM SUBJECT
}

void OrdersList::addOrder(Order* order) {
	playerOrderList.push_back(order);
    notify(this); // FROM SUBJECT
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
    /*
	else if (orderString == "diplomacy") {
        orderObject = new Diplomacy();
    }
    */
	else {
        cout << "wrong Order/Card type" << endl;
    }

    playerOrderList.push_back(orderObject);
    notify(this); // FROM SUBJECT
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

string OrdersList::stringToLog() {
    string logString = "Create log string for adding an Order.\n";
    return logString;
}