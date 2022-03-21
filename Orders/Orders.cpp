#include "Orders.h"
#include "../GameEngine/GameEngine.h"

// Static Method to Access static GameEngine*
GameEngine *Order::game = new GameEngine();

GameEngine *Order::getGameEngine() {
    return game;
}
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
}

// Copy constructor
Order::Order(const Order &original) {
    validated = original.validated;
    description = original.description;
}

// Destructor
Order::~Order() {
    game = nullptr;
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

void Order::setGameEngine(GameEngine *gamePlaying) {
    Order::game = gamePlaying;
}

Order &Order::operator=(const Order &order) {
    validated = order.validated;
    description = order.description;
    return *this;
}

ostream &operator<<(ostream &os, const Order &order) {
    string validated = (order.validated) ? "(validated)" : "(not validated)";
    os << order.description;
    return os;
}

void Order::validate() {} // Virtual Method

void Order::execute() {} // Virtual Method

// From Iloggable
string Order::stringToLog() {
    string logString = "The Order has been executed.\n";
    return logString;
}

/****************************** Deploy *******************************/
// Default constructor
Deploy::Deploy() : Order(false, "deploy"){
    playerIssuing = nullptr;
    target = nullptr;
    numToDeploy = 0;
}

// Parameterize Constructor
Deploy::Deploy(Player* p) : Order(false, "deploy"){
    playerIssuing = p;
    target = nullptr;
//    target = p->toDefend(game->getMap()).at(0);   TODO: ask Gabbi - the out of range problems
    numToDeploy = rand() % p->getReinforcePool() + 1;
    while (numToDeploy > playerIssuing->getReinforcePool()) {
        numToDeploy = rand() % p->getReinforcePool() + 1;
    }
}

Deploy::Deploy(const Deploy &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    target = original.target;
    numToDeploy = original.numToDeploy;
    cout << "Copy constructor for Deploy class has been called" << endl;
}

// Destructor
Deploy::~Deploy() {
    target = nullptr;
    playerIssuing = nullptr;
}

// Accessors
string Deploy::getDescription() { return description; }
bool Deploy::getValidated() { return validated; }
Player *Deploy::getPlayerIssuing() { return playerIssuing; }
Territory *Deploy::getTarget() { return target; }
int Deploy::getNumToDeploy() { return numToDeploy; }

// Mutators
void Deploy::setDescription(string d) {
    description = d;
}
void Deploy::setValidated(bool v) {
    validated = v;
}

Deploy &Deploy::operator=(const Deploy &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    target = o.target;
    numToDeploy = o.numToDeploy;
    return *this;
}

ostream &operator<<(ostream &os, const Deploy &o) {
    string validated = (o.validated) ? " (validated)" : " (not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() << " " /*<< o.target->getName() << " "*/ << o.numToDeploy << ") ";
    return os;
}

void Deploy::validate() {
    // Check if Territory belongs to the Player
    if (target->getOwner() == playerIssuing) {
        cout << "Valid!" << endl;
        validated = true;
    } else {
        cout << "Invalid! - You don't own this territory " << endl;
        validated = false;
    }
}

void Deploy::execute() {
    if (validated) {
        target->setArmies(target->getArmies() + numToDeploy); // add armies to target territory;
        playerIssuing->removeFromReinforcePool(numToDeploy);    // subtract armies from reinforcement pool
    } else {
        cout << "Can't execute Deploy order!" << endl;
    }
//    notify(this); // FROM SUBJECT
}

string Deploy::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") ";
    string logStringOrder = "Deploy order " + validation + " : Deployment " + to_string(numToDeploy) + " armies to " +
                            target->getName() + "\n";
    string logStringEffect =  to_string(target->getArmies()) +" armies now occupy " + target->getName() + ". \n";
    return logStringPlayer + logStringOrder + logStringEffect;
}
/****************************** Advance *******************************/

// Default constructor
Advance::Advance() : Order(false, "advance"){
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
    numToAdvance = 0;
}

// Parameterize Constructor
Advance::Advance(Player* p) : Order(false, "advance"){
    playerIssuing = p;
    origin = nullptr;
    target = nullptr;
//    origin = p->toDefend();   //TODO: ask Gabbi - the out of range problems
//    target = p->toAttack(game->getMap()).at(0);
//    numToAdvance = rand() % origin->getArmies() + 1;
//    while (numToAdvance > origin->getArmies()){
//        numToAdvance = rand() % origin->getArmies() + 1;
//    }
}

// Copy constructor
Advance::Advance(const Advance &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    origin = original.origin;
    target = original.target;
    numToAdvance = original.numToAdvance;
    cout << "Copy constructor for Advance class has been called" << endl;
}

// Destructor
Advance::~Advance() {
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
}

// Accessors
string Advance::getDescription() { return description; }
bool Advance::getValidated() { return validated; }
Player *Advance::getPlayerIssuing() { return playerIssuing; }
Territory* Advance::getOrigin() { return origin; }
Territory *Advance::getTarget() { return target; }
int Advance::getNumToAdvance() { return numToAdvance; }

// Mutators
void Advance::setDescription(string d) {
    description = d;
}

void Advance::setValidated(bool v) {
    validated = v;
}

Advance &Advance::operator=(const Advance &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    numToAdvance = o.numToAdvance;
    return *this;
}

ostream &operator<<(ostream &os, const Advance &o) {
    string validated = (o.validated) ? " (validated)" : " (not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() << " " /*<< o.origin->getName() << " " << o.target->getName() << " "*/ << o.numToAdvance << ")";
    return os;
}

void Advance::validate() {
    validateResult = "";

    // Check if Territory belongs to the Player
    if (origin->getOwner() != playerIssuing) {
        cout << "Invalid! - You don't own this territory" << endl;
        validated = false;
    }
    // Check if 2 Territories are adjacent
    else if(!(game->getMap()->adjacentTerritories(origin, target))){
        cout << "Invalid! - Two territories are not adjacent" << endl;
        validated = false;
    }
    // Condition: If Source territory is owned by Player && Target territory and Source territory are adjacent
    // Sub-condition: If Target Territory is owned by Player (Yes: Advance || No: Attack)
    else{
        if(target->getOwner() == playerIssuing){
            cout << "Valid! ** Type advance" << endl;
            validateResult = "Advance";
            validated = true;
        }
        // Condition: If target territory is not owned by player
        // Sub-condition: If there exist alliance (Yes: attack is invalid || No: attack is valid)
        else if (!(game->existingAlliance(origin->getOwner(), target->getOwner()))){
            cout << "Valid! ** Type attack" << endl;
            validateResult = "Advance";
            validated = true;
        }
        else{
            cout << "Invalid! - Cannot attack Territory in Negotiation";
            validated = false;
        }
    }
}

void Advance::execute() {
    if (validated) {
        // Advance
        if(target->getOwner() == playerIssuing) {
            origin->setArmies(origin->getArmies() - numToAdvance); // subtract armies from source territory;
            target->setArmies(target->getArmies() + numToAdvance); // add armies to target territory;
        }
        // Attack
        else if ((target->getOwner() != playerIssuing) && !(game->existingAlliance(origin->getOwner(), target->getOwner()))){
            origin->setArmies(origin->getArmies()-numToAdvance);

            // Target is defender -> Defend Power = Target Territory numOfArmies * 70%
            // Origin is Attacker -> Attack Power = Origin Territory numOfArmies * 60%
            int attackPower = origin->getArmies()*0.6;
            int defendPower = target->getArmies()*0.7;
            if (attackPower == defendPower) {
                target->setArmies(0);
            }
            else if (attackPower > defendPower){
                target->setArmies((attackPower - defendPower)/0.6);
                target->setOwner(playerIssuing);
                // TODO player draw a card from the Deck
            }
            else{}

        }
    } else
        cout << "Can't execute Advance order!" << endl;
}

    //notify(this); // FROM SUBJECT LET ME KNOW HOW YOU ARE GOING TO STORE THE ACTION (ATTACK OR NOT) so I can output it in the log


string Advance::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") ";
    string logStringOrder;

    if (validateResult == "Attack"){
        logStringOrder = "Advance order" + validation + " : Attack with "+ to_string(numToAdvance) + " armies to " + target->getName() + "\n";
    }

    else if (validateResult == "Advance"){
        logStringOrder = "Advance order" + validation + " : Attack with "+ to_string(numToAdvance) + " armies to " + target->getName() + "\n";
    }
    string logStringEffect = target->getName() + " has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwner()->getName() + "\n";

    return logStringPlayer + logStringOrder + logStringEffect;
}

/****************************** Airlift *******************************/

// Default constructor
Airlift::Airlift() : Order(false, "airlift"){
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
    numToAirlift = 0;
}

// Parameterize Constructor
Airlift::Airlift(Player* p) : Order(false, "airlift"){
    playerIssuing = p;
    origin = nullptr;
    target = nullptr;
//    origin = p->toDefend(game->getMap()).at(0);     //TODO: out of range - ask Gabbi
//    target = p->toAttack(game->getMap()).at(0);
//    numToAirlift = rand() % origin->getArmies() + 1;
//    while (numToAirlift > origin->getArmies()){
//        numToAirlift = rand() % origin->getArmies() + 1;
//    }
}

// Copy constructor
Airlift::Airlift(const Airlift &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    origin = original.origin;
    target = original.target;
    numToAirlift = original.numToAirlift;
    cout << "Copy constructor for Airlift class has been called" << endl;
}

// Destructor
Airlift::~Airlift() {
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
}

// Accessors
string Airlift::getDescription() { return description; }
bool Airlift::getValidated() { return validated; }
Player *Airlift::getPlayerIssuing() { return playerIssuing; }
Territory* Airlift::getOrigin() { return origin; }
Territory *Airlift::getTarget() { return target; }
int Airlift::getNumToAirlift() { return numToAirlift; }

// Mutators
void Airlift::setDescription(string d) {
    description = d;
}

void Airlift::setValidated(bool v) {
    validated = v;
}

Airlift &Airlift::operator=(const Airlift &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    numToAirlift = o.numToAirlift;
    return *this;
}

ostream &operator<<(ostream &os, const Airlift &o) {
    string validated = (o.validated) ? " (validated)" : " (not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() << " " /*<< o.origin->getName() << " " << o.target->getName() << " "*/ << o.numToAirlift << ") ";
    return os;
}

void Airlift::validate() {
    if (target->getOwner() == playerIssuing && origin->getOwner() == playerIssuing){
        cout << "Valid!" << endl;
        validated = true;
    } else {
        cout << "Invalid! - You don't own both Territories" << endl;
        validated = false;
    }
}

void Airlift::execute() {
    if(validated){
        origin->setArmies(origin->getArmies()-numToAirlift);
        target->setArmies(target->getArmies()+numToAirlift);
    } else{
        cout << "Can't execute Airlift order!" << endl;
    }
    // notify(this); // FROM SUBJECT
}

string Airlift::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") ";
    string logStringOrder =
            "Airlift order " + validation + ": Airlifting " + to_string(numToAirlift) + " armies from " +
            origin->getName() + " to " + target->getName() + ".\n";

    string logStringEffect1 =  to_string(origin->getArmies()) +" armies now occupy " + origin->getName() + ". \n";
    string logStringEffect2 =  to_string(target->getArmies()) +" armies now occupy " + target->getName() + ". \n";
    return logStringPlayer + logStringOrder + logStringEffect1 + logStringEffect2;
}

/****************************** Bomb *******************************/

// Default constructor
Bomb::Bomb() : Order(false, "bomb"){
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
}

// Parameterize Constructor
Bomb::Bomb(Player* p) : Order(false, "bomb"){
    playerIssuing = p;
    origin = nullptr;
    target = nullptr;
//    origin = p->toDefend(game->getMap()).at(0);   //TODO: out of range - ask Gabbi
//    target = p->toAttack(game->getMap()).at(0);
}

// Copy constructor
Bomb::Bomb(const Bomb &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    origin = original.origin;
    target = original.target;
    cout << "Copy constructor for Bomb class has been called" << endl;
}

// Destructor
Bomb::~Bomb() {
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
}

// Accessors
string Bomb::getDescription() { return description; }
bool Bomb::getValidated() { return validated; }
Player* Bomb::getPlayerIssuing() { return playerIssuing; }
Territory* Bomb::getOrigin() { return origin; }
Territory *Bomb::getTarget() { return target; }

// Mutators
void Bomb::setDescription(string d) {
    description = d;
}

void Bomb::setValidated(bool v) {
    validated = v;
}

Bomb &Bomb::operator=(const Bomb &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    return *this;
}

ostream &operator<<(ostream &os, const Bomb &o) {
    string validated = (o.validated) ? " (validated)" : " (not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() /*<< " " << o.origin->getName() << " " << o.target->getName()*/ << ") ";
    return os;
}

void Bomb::validate() {
    // Check that Territory A is not the Player's
    if (origin->getOwner() == playerIssuing) {
        cout << "invalid Bomb: the Territory belongs to the Player issuing the bomb order";
        validated = false;
    }
        // Check for an existing Alliance
    else if (game->existingAlliance(origin->getOwner(), target->getOwner())) {
        validated = false;
    }
        // Check that territories are adjacent
    else if (game->getMap()->adjacentTerritories(origin, target)) {
        validated = false;
    } else
        validated = true;

}

void Bomb::execute() {
    if (!validated) {
        cout << "Invalid Bomb Order, Truce between players\n";
        cout << "Invalid Bomb Order";

    } else {
        int bombedArmies = (target->getArmies()) / 2;
        target->setArmies(bombedArmies);
        cout << this->stringToLog();
    }
    //notify(this); // FROM SUBJECT
}

string Bomb::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") ";
    string logStringOrder =
            "Bomb order" + validation + ": Bomb from " + origin->getName() + " to " + target->getName() + ".\n";
    string logStringEffect = target->getName() + " has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwner()->getName() + "\n";
    return logStringPlayer + logStringOrder + logStringEffect;
}

/****************************** Blockade *******************************/

// Default constructor
Blockade::Blockade() : Order(false, "blockade"){
    playerIssuing = nullptr;
    target = nullptr;
}

// Parameterize Constructor
Blockade::Blockade(Player* p) : Order(false, "blockade"){
    playerIssuing = p;
    target = nullptr;
//    target = p->toAttack(game->getMap()).at(0);   //TODO: out of range - ask Gabbi
}

// Copy constructor
Blockade::Blockade(const Blockade &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    target = original.target;
    cout << "Copy constructor for Blockade class has been called" << endl;
}

// Destructor
Blockade::~Blockade() {
    playerIssuing = nullptr;
    target = nullptr;
}

// Accessors
string Blockade::getDescription() { return description; }
bool Blockade::getValidated() { return validated; }
Player* Blockade::getPlayerIssuing() { return playerIssuing; }
Territory *Blockade::getTarget() { return target; }

// Mutators
void Blockade::setDescription(string d) {
    description = d;
}

void Blockade::setValidated(bool v) {
    validated = v;
}

Blockade &Blockade::operator=(const Blockade &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    target = o.target;
    return *this;
}

ostream &operator<<(ostream &os, const Blockade &o) {
    string validated = (o.validated) ? " (validated)" : " (not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() /*<< " " << o.target->getName() << " "*/ << ") ";
    return os;
}

void Blockade::validate() {
    if (target->getOwner() == playerIssuing) {
        validated = true;
    } else
        validated = false;
}

void Blockade::execute() {
    if (!validated) {
        cout << "Invalid Blockade Order";
    } else {
        int doubleArmies = (target->getArmies()) * 2;
        target->setArmies(doubleArmies);
        target->setOwner(game->getNeutralPlayer());
        cout << this->stringToLog();
    }
    //notify(this); // FROM SUBJECT
}

string Blockade::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") ";
    string logStringOrder = "blockade order " + validation + ": transfer of the ownership of " + target->getName() +
                            " to the Neutral Player.\n";
    string logStringEffect = target->getName() + " has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwner()->getName() + "\n";
    return logStringPlayer + logStringOrder;
}

/****************************** Negotiate *******************************/

// Default constructor
Negotiate::Negotiate() : Order(false, "negotiate"){
    playerIssuing = nullptr;
    targetPlayer = nullptr;
}

// Parameterize Constructor
Negotiate::Negotiate(Player* p) : Order(false, "negotiate"){
    playerIssuing = p;
    // TODO: initialize targetPlayer; ??? any criteria to be a target Player
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &original) : Order(original) {
    playerIssuing = original.playerIssuing;
    // TODO: initialize targetPlayer
    cout << "Copy constructor for Negotiate class has been called" << endl;
}

// Destructor
Negotiate::~Negotiate() {
    playerIssuing = nullptr;
    targetPlayer = nullptr;
}

// Accessors
string Negotiate::getDescription() { return description; }
bool Negotiate::getValidated() { return validated; }
Player* Negotiate::getPlayerIssuing() { return playerIssuing; }
Player* Negotiate::getTargetPlayer() { return targetPlayer; }

// Mutators
void Negotiate::setDescription(string d) {
    description = d;
}

void Negotiate::setValidated(bool v) {
    validated = v;
}

Negotiate &Negotiate::operator=(const Negotiate &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    targetPlayer = o.targetPlayer;
    return *this;
}

ostream &operator<<(ostream &os, const Negotiate &o) {
    string validated = (o.validated) ? "(validated)" : "(not validated)";
    os << o.description << " (" << std::boolalpha << o.validated << " "
       << o.playerIssuing->getName() << " " << o.targetPlayer->getName() << ") ";
    return os;
}

void Negotiate::validate() {
    if (playerIssuing == targetPlayer || targetPlayer->getName() == "Neutral") {
        validated = false;
        cout << "Invalid Negotiate : Negotiate must be done with a different player, excluding the Neutral player\n";
    } else
        validated = true;
}


void Negotiate::execute() {
    if (!validated) {
        cout << "Invalid Negotiate Order\n";
    } else {
        game->addAlliances(playerIssuing, targetPlayer);
        cout << "Executed Negotiate Order\n";
    }
    //notify(this); // FROM SUBJECT
}

string Negotiate::stringToLog() {
    string validation = (validated) ? "executed" : "to be validated";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ")";
    string logStringOrder =
            "Negotiate order " + validation + ": " + playerIssuing->getName() + " and " + targetPlayer->getName() +
            " are in a truce until the end of this round of turns." "\n";
    return logStringPlayer + logStringOrder;
}

/****************************** OrdersList *******************************/

// Default constructor
OrdersList::OrdersList() {
    playerOrderList = vector<Order *>();
}

// Parameterized constructor
OrdersList::OrdersList(vector<Order *> vo) {
    playerOrderList = vo;
}

// Copy constructor
OrdersList::OrdersList(const OrdersList &original)
{
    for (int i = 0; i < original.playerOrderList.size(); i++)
    {
        if (original.playerOrderList.at(i)->getDescription() == "deploy")
        {
            playerOrderList.push_back(new Deploy());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "advance")
        {
            playerOrderList.push_back(new Advance());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "bomb")
        {
            playerOrderList.push_back(new Bomb());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "blockade")
        {
            playerOrderList.push_back(new Blockade());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "airlift")
        {
            playerOrderList.push_back(new Airlift());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "negotiate")
        {
            playerOrderList.push_back(new Negotiate());
        }
    }
    cout << "Copy constructor for OrdersList class has been called" << endl;
}

// Destructor
OrdersList::~OrdersList() {
    // Iterate through all pointed orders and delete the content in heap of each
    for (Order *i: playerOrderList) {
        if (i != nullptr) {
            free(i);
            i = nullptr;
        }
    }

    playerOrderList.clear();
}

// Accessors
vector<Order *> OrdersList::getOrderList() { return playerOrderList; }

// Mutators
void OrdersList::setOrderList(vector<Order *> vo) { playerOrderList = vo; }


// Assignment Operator overloading, will have the same behavior as the Copy constructor. Deep copy of Vector through = operator.
OrdersList OrdersList::operator=(const OrdersList &original) {

    for (int i = 0; i < original.playerOrderList.size(); i++)
    {
        if (original.playerOrderList.at(i)->getDescription() == "deploy")
        {
            playerOrderList.push_back(new Deploy());
        }
        else if (original.playerOrderList.at(i)->getDescription()  == "advance")
        {
            this->playerOrderList.push_back(new Advance());
        }
        else if (original.playerOrderList.at(i)->getDescription()  == "bomb")
        {
            this->playerOrderList.push_back(new Bomb());
        }
        else if (original.playerOrderList.at(i)->getDescription()  == "blockade")
        {
            this->playerOrderList.push_back(new Blockade());
        }
        else if (original.playerOrderList.at(i)->getDescription()  == "airlift")
        {
            this->playerOrderList.push_back(new Airlift());
        }
        else if (original.playerOrderList.at(i)->getDescription() == "negotiate")
        {
            this->playerOrderList.push_back(new Negotiate());
        }
    }
    cout << "Assignment operator for OrdersList class has been called" << endl;
    return *this;
}

// stream insertion operator that outputs the OrdersList's vector
ostream &operator<<(ostream &os, const OrdersList &ordersList) {
    os << "Order List (size: " << ordersList.playerOrderList.size() << ") \n";
    for (int i = 0; i < ordersList.playerOrderList.size(); i++) {
        os << i << " - " << *(ordersList.playerOrderList.at(i)) << " | ";
    }
    return os;
}


void OrdersList::addOrder(Order *order) {
    playerOrderList.push_back(order);
    //notify(this);
}

// Remove Method used to remove an order of the OrderList. The Parameter is an int for the index of the Order.
void OrdersList::remove(int i) {
    int j = 0;
    playerOrderList.erase(playerOrderList.begin() + i);
}

// Move Method used to swap to Orders in the list. The parameters are both int type for the index of the Orders.
void OrdersList::move(int i, int j) {
    //Case 1: Moving Order downwards
    if (i > j) {
        for (j = j; j < i; j++) {
            swap(playerOrderList[i], playerOrderList[j]);
        }
    }
        //Case 2: Moving Order Upwards
    else if (i < j) {
        for (j = j; j > i; j--) {
            swap(playerOrderList[i], playerOrderList[j]);
        }
    } else {
        cout << " wrong order index or wrong destination index" << endl;
    }
}

string OrdersList::stringToLog() {
    Order *lastOrderAdded = playerOrderList.at(playerOrderList.size() - 1);
    string logString = lastOrderAdded->stringToLog() + ".\n";
    return logString;
}

/******************************* DRAFT *******************************/
// Second version is more compatible with OrderList log
//string Deploy::stringToLog() {
//    string logStringPlayer = "- Player " + playerIssuing->getName() + " executed a " + to_string(validate()) + " ";
//    string logStringOrder = "Deploy order : Deployed " + to_string(numToDeploy) + " soldiers to " + target->getName() + "\n";
//    return logStringPlayer + logStringOrder;
//}


/* Deploy
   * Maybe ask for input of the player for the number of armies for deployment or is it a standard number?
   * Validate number here? make sure its <= than the Player's reinforcement pool Or Change Validate to receive int armies and Territory
   * will call validate() to check Territory
   * if false, print out invalid
   * if true, add armiesForDeployment to the Territory and remove it from the Player's Reinforcement pool
*/

/* Advance
 * ask input from the player for number of armies moved, Territory A and Territory B
 * call validate() --> Change method to accept armies, Territory A and Territory B ?
 * if 1 print invalid order
 * if 2 remove armies from Territory A and add them to Territory B
 *  if 3 ATTACK
 */

/* Airlift
  * Can only be played with a CARD so remove it from IssueOrder in Player
  * Ask player for Territory A, Territory B and int armies
  * validate()
  * if false, order invalid
  * if true, remove armies from Territory A and add them to Territory B
  */

/* Negotiate
  * Can only be played with a DIPLOMACY CARD so remove it from IssueOrder in Player
  * Ask player for another player name
  * validate()
  * if false, invalid order
  * if true make any attack from Player A to Player B and vice-versa invalid until end of turn (probably until reinforcement phase)
  * Maybe add a List of Player* as an attribute in PLayer to keep track of who has a truce with who.
  * In this case, this adds Player A to Player B's list and vice-versa
  * Lists must be cleared when goes to reinforcement phase
  */

/*************

 *********** Deploy execute() prompt user for input
 // Prompt player for number of Armies to deploy
        numToDeploy = 0;
        cout << playerIssuing->getName() << " reinforcement Pool: " << playerIssuing->getReinforcePool() << " armies" << endl;
        cout << "Number of armies to deploy: ";
        cin >> numToDeploy;
        // Check if number of Armies to Deploy < Reinforcement Pool
        while (numToDeploy > playerIssuing->getReinforcePool()) {
            cout << "Re-enter number of Armies to deploy: ";
            cin >> numToDeploy;
        }
 ***********



 * // Parameterized constructor
Deploy::Deploy(bool v, string s, Player *p, Territory *t)
        : Order(v, s, p),
          target{t} {}

// Parameterized constructor for IssueOrders Phase
Deploy::Deploy(Player *p, Territory *t)
        : Order(false, "Deploy", p),
          target{t} {}

 // Parameterized constructor
Advance::Advance(bool v, string s, Player *p, Territory *o, Territory *t)
        : Order(v, s, p),
          origin{o},
          target{t}
          {}

// Parameterized constructor for IssueOrders Phase
Advance::Advance(Player *p, Territory *o, Territory *t)
        : Order(false, "Advance", p),
          origin{o},
          target{t}
          {}

 // Parameterized constructor
Airlift::Airlift(bool v, string s, Player *p, Territory *o, Territory *t, int armies)
        : Order(v, s, p),
          origin{o},
          target{t},
          numOfArmies{armies} {}

// Parameterized constructor for IssueOrders Phase
Airlift::Airlift(Player *p, Territory *o, Territory *t, int armies)
        : Order(false, "Airlift", p),
          origin{o},
          target{t},
          numOfArmies{armies} {}

// Parameterized constructor For IssueOrders Phase
 Bomb::Bomb(Player *p, Territory *o, Territory *t) : Order(false, "Bomb", p) {
    origin = o;
    target = t;
}

// Parameterized constructor
Bomb::Bomb(bool v, string s, Player *p, Territory *o, Territory *t) : Order(v, s, p) {
    origin = o;
    target = t;
}

 // Parameterized constructor
Blockade::Blockade(bool v, string s, Player *p, Territory *t) : Order(v, s, p) {
    target = t;
};

// Parameterized constructor for Orders Issuing Phase
Blockade::Blockade(Player *p, Territory *t) : Order(false, "Blockade", p) {
    target = t;
}

 // Parameterized constructor for IssueOrders Phase
Negotiate::Negotiate(Player *p1, Player *p2) : Order(false, "Negotiate", p1) {
    targetPlayer = p2;
};

// Parameterized constructor
Negotiate::Negotiate(bool v, string s, Player *p1, Player *p2) : Order(v, s, p1) {
    targetPlayer = p2;
};

 void OrdersList::addOrder(string orderString) {
    Order *orderObject;

    // CONDITIONAL
    if (orderString == "deploy") {
        orderObject = new Deploy();
    } else if (orderString == "advance") {
        orderObject = new Advance();
    } else if (orderString == "bomb") {
        orderObject = new Bomb();
    } else if (orderString == "blockade") {
        orderObject = new Blockade();
    } else if (orderString == "airlift") {
        orderObject = new Airlift();
    } else if (orderString == "Negotiate") {
        orderObject = new Negotiate();
    } else {
        cout << "wrong Order/Card type" << endl;
    }

    playerOrderList.push_back(orderObject);
    //notify(this); // FROM SUBJECT
}

 // Default constructor
Bomb::Bomb()
        : Order(false, "Bomb", new Player()),
          target{new Territory()} {}

// Copy constructor
Bomb::Bomb(const Bomb &original) : Order(original) {}

// Destructor
Bomb::~Bomb() {
    origin = nullptr; // DONT WANT TO DESTROY ACTUAL TERRITORY
    target = nullptr;
};

 // Default constructor
Blockade::Blockade()
        : Order(false, "Deploy", new Player()),
          target{new Territory()} {}


// Copy constructor
Blockade::Blockade(const Blockade &original) : Order(original) {}

// Destructor
Blockade::~Blockade() {
    target = nullptr;
}

 // Default constructor
Negotiate::Negotiate()
        : Order(false, "Deploy", new Player())
        {}

// Parameterized constructor (player only)
Negotiate::Negotiate(Player* p)
    : Order(false, "Order",p)
    {}

// Copy constructor
Negotiate::Negotiate(const Negotiate &original) : Order(original) {}

// Destructor
Negotiate::~Negotiate() {
    targetPlayer = nullptr;
};


*********** OrderList constructors with dynamic_cast<>
// Parameterized constructor
OrdersList::OrdersList(vector<Order *> vo) {
    playerOrderList = vector<Order *>();

    for (Order *i: vo) {
        Order *objectCopied = nullptr;
        if (dynamic_cast<Deploy *>(i) != nullptr) {
            objectCopied = new Deploy(*(dynamic_cast<Deploy *>(i)));
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Advance *>(i) != nullptr) {
            objectCopied = new Advance(*(dynamic_cast<Advance *>(i)));
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Airlift *>(i) != nullptr) {
            objectCopied = new Airlift(*(dynamic_cast<Airlift *>(i)));
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Bomb *>(i) != nullptr) {
            objectCopied = new Bomb(*(dynamic_cast<Bomb *>(i)));
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Blockade *>(i) != nullptr) {
            objectCopied = new Blockade(*(dynamic_cast<Blockade *>(i)));
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Negotiate *>(i) != nullptr) {
            objectCopied = new Negotiate(*(dynamic_cast<Negotiate *>(i)));
            playerOrderList.push_back(objectCopied);
        }

    }
}

// Copy constructor
OrdersList::OrdersList(const OrdersList &original) {
    playerOrderList = vector<Order *>();

    for (Order *i: original.playerOrderList) {
        Order *objectCopied;
        if (dynamic_cast<Deploy *>(i) != nullptr) {
            objectCopied = new Deploy(*dynamic_cast<Deploy *>(i));
            cout << *objectCopied << endl;
            cout << "adding a Deploy order\n";
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Advance *>(i) != nullptr) {
            objectCopied = new Advance(*dynamic_cast<Advance *>(i));
            cout << "adding a Advance order\n";
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Airlift *>(i) != nullptr) {
            objectCopied = new Airlift(*dynamic_cast<Airlift *>(i));
            cout << "adding a Airlift order\n";
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Bomb *>(i) != nullptr) {
            objectCopied = new Bomb(*dynamic_cast<Bomb *>(i));
            cout << "adding a Bomb order\n";
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Blockade *>(i) != nullptr) {
            objectCopied = new Blockade(*dynamic_cast<Blockade *>(i));
            cout << "adding a Blockade order\n";
            playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Negotiate *>(i) != nullptr) {
            objectCopied = new Negotiate(*dynamic_cast<Negotiate *>(i));
            cout << "adding a Negotiate order\n";
            playerOrderList.push_back(objectCopied);
        }
    }
}

// Assignment Operator overloading, will have the same behavior as the Copy constructor. Deep copy of Vector through = operator.
OrdersList OrdersList::operator=(const OrdersList &original) {
    OrdersList deepcopy;

    for (Order *i: original.playerOrderList) {
        Order *objectCopied = nullptr;
        if (dynamic_cast<Deploy *>(i) != nullptr) {
            objectCopied = new Deploy(*(dynamic_cast<Deploy *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Advance *>(i) != nullptr) {
            objectCopied = new Advance(*(dynamic_cast<Advance *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Airlift *>(i) != nullptr) {
            objectCopied = new Airlift(*(dynamic_cast<Airlift *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Bomb *>(i) != nullptr) {
            objectCopied = new Bomb(*(dynamic_cast<Bomb *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Blockade *>(i) != nullptr) {
            objectCopied = new Blockade(*(dynamic_cast<Blockade *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        } else if (dynamic_cast<Negotiate *>(i) != nullptr) {
            objectCopied = new Negotiate(*(dynamic_cast<Negotiate *>(i)));
            deepcopy.playerOrderList.push_back(objectCopied);
        }
    }
    cout << "DEBUG : for loop inside assignment operator" << endl;

    return deepcopy;
}
***********

 */
