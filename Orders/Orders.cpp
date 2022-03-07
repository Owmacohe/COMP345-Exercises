#include "Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"


/****************************** Order *******************************/
// Static Method to Access static GameEngine*
GameEngine* Order::game = new GameEngine();

GameEngine* Order::getGameEngine (){
    return game;
}

// Default constructor
Order::Order() {
    validated = false;
    description = "";
    playerIssuing = NULL;
//    game = NULL;
}

// Parameterized constructor
Order::Order(bool v, string s, Player* p){
    validated = v;
    description = s;
    playerIssuing = p;
}

// Copy constructor
Order::Order(Order& original) {
    validated = original.validated;
    description = original.description;
    playerIssuing = new Player(*(original.playerIssuing));
}

// Destructor
Order::~Order() {
    playerIssuing = NULL;
}

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

void Order::setGameEngine(GameEngine* gamePlaying){
   Order::game = gamePlaying;
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

bool Order::validate() {return true;} // Virtual Method

void Order::execute() {} // Virtual Method

// From Iloggable
string Order::stringToLog() {
    string logString = "The Order has been executed.\n";
    return logString;
}

/****************************** Deploy *******************************/

// Default constructor
Deploy::Deploy() : Order(false, "Deploy", NULL) { }

// Parameterized constructor
Deploy::Deploy(bool v, string s, Player* p, Territory* t, int armies)
    : Order(v,s,p),
    target{t},
    numToDeploy{armies}
    {}

// Parameterized constructor for IssueOrders Phase
Deploy::Deploy(Player* p, Territory* t, int armies)
    : Order(false, "Deploy", NULL),
    target{t},
    numToDeploy{armies}
    {}

Deploy::Deploy(Deploy& original) : Order(original) {
    description = "Deploy Armies into a territory";
}

// Destructor
Deploy::~Deploy() {
    target = NULL;
}

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
    vector<Territory*> ownTerritory = playerIssuing->getTerritory();
    if (numToDeploy > 0 and numToDeploy <= playerIssuing->getReinforcePool()) {
        cout << "Valid number of armies to deploy" << endl;
        for (auto aTerritory: ownTerritory) {
            if (target->getName() == aTerritory->getName()) {
                validated = true;
            }
        }
        // Check if the method is working - will be deleted after
        if (validated) {cout << "Deploy order is VALID" << endl;}
        else{cout << "Cannot Deploy to other player's territory" << endl;}
    } else {
        cout << "Invalid number of armies to deploy." << endl;
        validated = false;
    }
    return validated;
}

void Deploy::execute() {
    if (validated){
        target->setArmies(target->getArmies()+numToDeploy); // add deployed armies to territory;
        playerIssuing->removeFromReinforcePool(numToDeploy);
    } else{
        cout << "Can't execute Deploy order!" << endl;
    }
    /* Maybe ask for input of the player for the number of armies for deployment or is it a standard number?
    * Validate number here? make sure its <= than the Player's reinforcement pool Or Change Validate to receive int armies and Territory
    * will call validate() to check Territory
    * if false, print out invalid
    * if true, add armiesForDeployment to the Territory and remove it from the Player's Reinforcement pool
    */
    //notify(this); // FROM SUBJECT
}

//string Deploy::stringToLog() { //TODO
//    string logString = "Create log string for execution of deploy.\n";
//    return logString;
//}

/****************************** Advance *******************************/

// Default constructor
Advance::Advance() : Order(false, "Advance", NULL) { }

// Parameterized constructor
Advance::Advance(bool v, string s, Player* p, Territory* o, Territory* t, int armies)
    : Order(v,s,p),
    origin{o},
    target{t},
    numOfArmies{armies}{}

// Parameterized constructor for IssueOrders Phase
Advance::Advance(Player* p, Territory* o, Territory* t, int armies)
    : Order(false, "Advance", NULL),
    origin{o},
    target{t},
    numOfArmies{armies}{}

// Copy constructor
Advance::Advance(Advance& original) : Order(original) {
    description = "Advance Armies into a territory";
}

// Destructor
Advance::~Advance() {
    target = NULL;
    origin = NULL;
}

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
    //if ( playerIssuing in list of alliance's pair is not the target player)


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

void Advance::execute() {
    /*
     * ask input from the player for number of armies moved, Territory A and Territory B
     * call validate() --> Change method to accept armies, Territory A and Territory B ?
     * if 1 print invalid order
     * if 2 remove armies from Territory A and add them to Territory B
     *  if 3 ATTACK
     */
    //notify(this); // FROM SUBJECT
}

//string Advance::stringToLog() {
//    string logString = "Create log string for execution.\n"; //TODO
//    return logString;
//}

/****************************** Airlift *******************************/

// Default constructor
Airlift::Airlift() : Order(false, "Airlift", NULL) { }

// Parameterized constructor
Airlift::Airlift(bool v, string s, Player* p, Territory* o, Territory* t, int armies)
    : Order(v,s,p),
    origin{o},
    target{t},
    numOfArmies{armies}{}

// Parameterized constructor for IssueOrders Phase
Airlift::Airlift(Player* p, Territory* o, Territory* t, int armies)
    : Order(false, "Airlift", NULL),
    origin{o},
    target{t},
    numOfArmies{armies}{}

// Copy constructor
Airlift::Airlift(Airlift& original) : Order(original) {
    description = "Airlift Armies into another territory";
}

// Destructor
Airlift::~Airlift() {
    target = NULL;
    origin = NULL;
}

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
void Airlift::execute() {
    /*
     * Can only be played with a CARD so remove it from IssueOrder in Player
     * Ask player for Territory A, Territory B and int armies
     * validate()
     *if false, order invalid
     * if true, remove armies from Territory A and add them to Territory B
     */
    // notify(this); // FROM SUBJECT
}

//string Airlift::stringToLog() {
//    string logString = "Create log string for execution.\n";
//    return logString;
//}

/****************************** Bomb *******************************/

// Default constructor
Bomb::Bomb() : Order(false, "Bomb", NULL) {};

// Parameterized constructor For IssueOrders Phase
Bomb::Bomb(Player* p, Territory* o, Territory* t) : Order(false, "Bomb", p) {
    origin = o;
    target = t;
}

// Parameterized constructor
Bomb::Bomb(bool v, string s, Player* p, Territory* o, Territory* t) : Order(v,s,p) {
    origin = o;
    target = t;
}

// Copy constructor
Bomb::Bomb(Bomb& original) : Order(original) {
    description = "Bomb a territory";
}

// Destructor
Bomb::~Bomb() {
    origin = NULL; // DONT WANT TO DESTROY ACTUAL TERRITORY
    target = NULL;
};

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
    // Check that Territory A is not the Player's
    if (origin->getOwner() == playerIssuing){
        validated = false;
    }

//  if ( playerIssuing in list of alliance's pair is not the target Player) {
//  validated = false;
//  }
    // Check that Territory A is adjacent to one of the Player's TODO
//    else if(target is in
//    vector game.getMap().getConnectedTerritories(origin.getName())){
//        validated = false;
//        return validated;
//    }

    else
        validated = true;

    return validated;
}


void Bomb::execute() {

    if (!validate()){
        //if ( playerIssuing in list of alliance's pair is not the target player) TODO
        cout << "Invalid Bomb Order, Truce between players\n";
        cout << "Invalid Bomb Order";

    }
    else{
        int bombedArmies = (target->getArmies())/2;
        target->setArmies(bombedArmies);
        cout << this->stringToLog();
    }

   //notify(this); // FROM SUBJECT
}

//string Bomb::stringToLog() {
//    string logString = "Create log string for execution.\n"; //TODO
//    return logString;
//}

/****************************** Blockade *******************************/

// Default constructor
Blockade::Blockade() : Order(false, "Blockade", NULL) { };

// Parameterized constructor
Blockade::Blockade(bool v, string s, Player* p, Territory* t) : Order(v,s,p) {
    target = t;
};

// Parameterized constructor for Orders Issuing Phase
Blockade::Blockade(Player* p, Territory* t) : Order(false, "Blockade", p) {
    target = t;
}

// Copy constructor
Blockade::Blockade(Blockade& original) : Order(original) {
    description = "Create a blockade in a territory";
}

// Destructor
Blockade::~Blockade() {
    target = NULL;
}

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
    if (target->getOwner() == playerIssuing){
        validated = true;
    }
    else
        validated = false;

    return validated;
}


void Blockade::execute() {
    /*
     *  Can only be played with a CARD so remove it from IssueOrder in Player
     *  ask the player for a Territory A
     *  validate()
     *  if false, invalid order
     *  if true, make armies in territory x2 and make 'Neutral Player owner of that'
     *  Maybe create Neutral Player here (or at startup of game)
     */
    if (!validate()){
        cout << "Invalid Blockade Order";
    }
    else {
        int doubleArmies = (target->getArmies())*2;
        target->setArmies(doubleArmies);
        //target->setOwner(NEUTRAL PLAYER); TODO -- Add neutral at startup?
        cout << this->stringToLog();
    }

    //notify(this); // FROM SUBJECT
}

//string Blockade::stringToLog() {
//    string logString = "Create log string for execution.\n"; //TODO
//    return logString;
//}

/****************************** Negotiate *******************************/

// Default constructor
Negotiate::Negotiate() : Order(false, "Negotiate", NULL) { };

//// Parameterized constructor (player only)
//Negotiate::Negotiate(Player* p) : Order(p) { };

// Parameterized constructor for IssueOrders Phase
Negotiate::Negotiate(Player* p1, Player* p2) : Order(false, "Negotiate",p1) {
    targetPlayer = p2;
};

// Parameterized constructor
Negotiate::Negotiate(bool v, string s, Player* p1, Player* p2) : Order(v,s,p1) {
    targetPlayer = p2;
};

// Copy constructor
Negotiate::Negotiate(Negotiate& original) : Order(original) {
    description = "Negotiate with another Army";
}

// Destructor
Negotiate::~Negotiate() {
    targetPlayer = NULL;
};

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
    if (playerIssuing == targetPlayer || targetPlayer->getName() == "Neutral"){
        validated = false;
    }
    else
        validated = true;
    return validated;
}


void Negotiate::execute() {
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

    if (!validate()){
        cout << "Invalid Negotiate Order\n" ;
    }
    else{}
        // add to the pair list in game playerIssuing and target
        // add to the pair list in game target and playerIssuing

    //notify(this); // FROM SUBJECT
}

//string Negotiate::stringToLog() {
//    string logString = "Create log string for execution.\n";
//    return logString;
//}

/****************************** Reinforcement *******************************/ // I THINK WE CAN DELETE THIS

// Default constructor
Reinforcement::Reinforcement() : Order(false, "Reinforcement", NULL) { };


// Parameterized constructor
Reinforcement::Reinforcement(bool v, string s, Player* p) : Order(v,s,p) { };

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

void Reinforcement::execute() {
    cout << "Executing Order Reinforcement" << endl;
    //notify(this); // FROM SUBJECT
}

//string Reinforcement::stringToLog() {
//    string logString = "Create log string for execution.\n";
//    return logString;
//}

/****************************** OrdersList *******************************/

// Default constructor
OrdersList::OrdersList() {
    playerOrderList = vector<Order*>();
}

// Parameterized constructor
OrdersList::OrdersList(vector<Order*> vo, bool aov) {
    playerOrderList = vector<Order*>();
    
//    for (Order* i : vo) {
//        Order* objectCopied;
//        if (dynamic_cast<Deploy*>(i) != nullptr) {
//            objectCopied = new Deploy(*(dynamic_cast<Deploy*>(i)));
//            playerOrderList.push_back(objectCopied);
//        }
//        else if (dynamic_cast<Advance*>(i) != nullptr) {
//            //TODO
//        }
//        else if (dynamic_cast<Airlift*>(i) != nullptr) {
//        }
//        else if (dynamic_cast<Bomb*>(i) != nullptr) {
//        }
//        else if (dynamic_cast<Blockade*>(i) != nullptr) {
//        }
//        else if (dynamic_cast<Negotiate*>(i) != nullptr) {
//        }


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
    //notify(this); // FROM SUBJECT
}

void OrdersList::addOrder(Order* order) {
	playerOrderList.push_back(order);
    //notify(this); // FROM SUBJECT
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
        orderObject = new Airlift();
    }

	else if (orderString == "Negotiate") {
        orderObject = new Negotiate();
    }

	else {
        cout << "wrong Order/Card type" << endl;
    }

    playerOrderList.push_back(orderObject);
    //notify(this); // FROM SUBJECT
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
        for(j=j; j<i;j++) {
            swap(playerOrderList[i],playerOrderList[j]);}
    }
    //Case 2: Moving Order Upwards
    else if (i < j) {
        for(j=j; j>i; j--) {
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