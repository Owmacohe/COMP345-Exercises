#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "Orders.h"

// Static GameEngine*
GameEngine *Order::game = new GameEngine();

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
    target = p->toDefend(this->game->getMap()).at(0);
    numToDeploy = 1;
}

Deploy::Deploy(Player *p, Territory *target) : Order(false, "deploy") {
    playerIssuing = p;
    this->target = target;
    // Condition checked: If there's no more armies to airlift
    if (p->getReinforcePool() == 0) {
        numToDeploy = 0;
    } else {
        numToDeploy = rand() % p->getReinforcePool() + 1; // generate a random number
        while (numToDeploy > p->getReinforcePool()) { // make sure the condition armies <= armies in origin
            numToDeploy = rand() % p->getReinforcePool() + 1;
        }
    }
}
// Copy Constructor
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

Deploy &Deploy::operator=(const Deploy &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    target = o.target;
    numToDeploy = o.numToDeploy;
    return *this;
}

ostream &operator<<(ostream &os, const Deploy &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName()  << " | "
       << validated << " | target: " << o.target->getName() << " | " << o.numToDeploy << ") ";
    return os;
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

void Deploy::validate() {
    cout << "... ";
    if (numToDeploy == 0) {
        cout << "Invalid! - No more armies left to deploy" << endl;
        validated = false;
    } else if (target->getOwnerName() == playerIssuing->getName()) {
        cout << "Valid! - Territory owner: " << target->getOwnerName() << endl;
        validated = true;
    } else {
        cout << "Invalid! - You don't own this territory - Territory owner: " << target->getOwnerName() << endl;
        validated = false;
    }
}

void Deploy::execute() {
    cout << "... ";
    if (validated) {
        target->setArmies(target->getArmies() + numToDeploy); // add armies to target territory;
        playerIssuing->removeFromReinforcePool(numToDeploy);    // subtract armies from reinforcement pool
        cout << "Execution successful!\n" << endl;
    } else {
        cout << "Execution fail!\n" << endl;
    }
//   notify(this);
}

string Deploy::stringToLog() {
    string logStringOrder = "";
    string logStringEffect = "";
    string validation = (validated) ? "executed" : "validation failed";

    string logStringPlayer = "(Player " + playerIssuing->getName() + ") \n";
    string logStringReinforcePool = to_string(playerIssuing->getReinforcePool()) +" armies remains in reinforcement pool \n";
    if(validated){
        logStringOrder = "Deploy " + validation + " : Deploy " + to_string(numToDeploy) + " armies to " + target->getName() + "\n";
        logStringEffect = to_string(target->getArmies()) + " armies now occupy " + target->getName() + "\n";
    } else {
        logStringOrder = "Deploy " + validation + " : Deploy " + "0 armies to " + target->getName() + "\n";
        logStringEffect = to_string(target->getArmies()) + " armies now occupy " + target->getName() + "\n";
    }
    return logStringPlayer + logStringOrder + logStringReinforcePool + logStringEffect;
}

/****************************** Advance *******************************/

// Default constructor
Advance::Advance() : Order(false, "advance"){
    playerIssuing = nullptr;
    origin = nullptr;
    target = nullptr;
    numToAdvance = 0;
    validateResult = " ";
}

// Parameterize Constructor
Advance::Advance(Player* p) : Order(false, "advance") {
    playerIssuing = p;

    string input = "";
    int x =  rand() % 2;
    if (x == 0) {
        input = "move";
    } else
        input = "attack";

    // Move armies -> target = 1st territory in toDefend() || Attack -> target = 1st territory in toAttack()
    if (input == "move") {
    target = p->toDefend(game->getMap()).at(0);
    } else if (input == "attack")
        target = p->toAttack(game->getMap()).at(0);

        // From the target we chose, generate an origin that adjacent to it to attack
        origin = p->getOriginTerritory(target, game->getMap());

//        cout << "Target : " << target->getName() << " " << target->getOwnerName() << endl;
//        cout  << "Origin : "<< origin->getName() << " " << origin->getOwner()->getName() << endl;
//        cout << to_string(origin->getArmies()) << endl;

        // Condition checked: If there's no more armies to advance
        if (origin->getArmies() == 0) {
            numToAdvance = 0;
        } else {
            numToAdvance = rand() % origin->getArmies() + 1; // generate a random number
            while (numToAdvance > origin->getArmies()) { // make sure the condition armies <= armies in origin
                numToAdvance = rand() % origin->getArmies() + 1;
            }
        }
}
Advance::Advance(Player* p, Territory* origin, Territory* target) {
    playerIssuing = p;
    this->origin = origin;
    this->target = target;

    // Condition checked: If there's no more armies to advance
    if (origin->getArmies() == 0) {
        numToAdvance = 0;
    } else {
        numToAdvance = rand() % origin->getArmies() + 1; // generate a random number
        while (numToAdvance > origin->getArmies()) { // make sure the condition armies <= armies in origin
            numToAdvance = rand() % origin->getArmies() + 1;
        }
    }
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

Advance &Advance::operator=(const Advance &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    numToAdvance = o.numToAdvance;
    return *this;
}

ostream &operator<<(ostream &os, const Advance &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName() << " | "
       << validated << " | origin: " << o.origin->getName() << " | target: " << o.target->getName() << " | " + o.validateResult + " with " << o.numToAdvance << " armies)";
    return os;
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

void Advance::validate() {
    validateResult = "";
    cout << "... ";
    // Check if territory belongs to the player
    if (origin->getOwnerName() != playerIssuing->getName()) {
        cout << "Invalid! - You don't own this territory" << endl;
        validated = false;
    }
    // Check if 2 Territories are adjacent
    else if(!(game->getMap()->adjacentTerritories(origin, target))){
        cout << "Invalid! - Territories are not adjacent" << endl;
        validated = false;
    }
    // Check if Territory belongs to the Player
    else if (numToAdvance == 0 ) {
        cout << "Invalid! - No more armies left to advance" << endl;
        validated = false;
    }
    // Condition checked: If origin is owned by Player && target and origin are adjacent
    // Sub-condition: If target is owned by Player Issuing (Yes: Advance || No: Attack)
    else{
        // Yes: Target is owned by player issuing -> Move armies
        if(target->getOwnerName() == playerIssuing->getName()){
            cout << "Valid! ** Move armies" << endl;
            validateResult = "move";
            validated = true;
        }
        // No: Target is not owned by player issuing -> Attack
        // Check for existing alliance
        else if(game->existingAlliance(origin->getOwner(), target->getOwner())){
            cout << "Invalid! - You can't attack territory in negotiation" << endl;
            validated = false;
        }
        // Checking blockade protection
        else if(target->getOwnerName() == "Neutral"){
            cout << "Invalid! - You can't attack territory under protection of blockade" << endl;
            validated = false;
        }
        else {
            cout << "Valid! ** Attack" << endl;
            validateResult = "attack";
            validated = true;
        }
    }
}

void Advance::execute() {
    if (validated) {
        // Advance
        if (validateResult == "move") {
            origin->setArmies(origin->getArmies() - numToAdvance); // subtract armies from source territory;
            target->setArmies(target->getArmies() + numToAdvance); // add armies to target territory;
        }
        // Attack
        else if (validateResult == "attack") {
            int defend_alive = target->getArmies() - deathCalculation(target->getArmies(),0.6 );
            cout << "Enemy's armies " << defend_alive <<endl;
            int attack_alive = numToAdvance -  deathCalculation(numToAdvance, 0.7);
            cout << "Player's armies " << defend_alive << endl;
            // Attack successful
            if (attack_alive > defend_alive){
                target->setArmies(attack_alive); // Attacker survived conquered the territory
                target->setOwner(playerIssuing); // The territory now belong to player issuing
                playerIssuing->getHand()->drawCard(*game->getDeck()); // given a card if successfully conquered a territory
            }
            // Attack failed
            else {
                target->setArmies(defend_alive);
                cout << "Attack Failed, player now has " << defend_alive << " armies."<< endl;
            }
        }
    } else
        cout << "Can't execute Advance order!" << endl;

//    notify(this);
}

int Advance::deathCalculation(int qty, double probability) {
    bool kill;
    int dead = 0;
    while (qty > 0){
        kill = (rand() % 100) < probability*100;
        if (kill) dead++;
        qty--;
    }
    return dead;
}

string Advance::stringToLog() {
    string validation = (validated) ? "executed" : "validation failed";
    string logStringPlayer = "(Player " + playerIssuing->getName() + ") \n";
    string logStringOrder = "";
    string loStringEffect = "";

    if (validateResult == "attack"){
        logStringOrder = "Advance: " + validation + " : attack "  + target->getName() + " with " + to_string(numToAdvance) + " armies \n";
    }
    else if (validateResult == "move"){
        logStringOrder = "Advance: " + validation + " : Move "+ to_string(numToAdvance) + " armies from " + origin->getName() + " to " + target->getName() + "\n";
    }
    string logStringEffect = target->getName() + " has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwnerName() + "\n";
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
    Territory* territory_most_armies; // Choose 1 territory belongs to the player that has the most armies
    int max_armies = 0 ;
    for (Territory* t : p->getTerritoryList()) {
        if (t->getArmies() > max_armies) {
            territory_most_armies = t;
            max_armies = t->getArmies();
        }
    }
    origin = territory_most_armies; // Origin = territory with the most armies
    target = p->toDefend(game->getMap()).at(0); // Target = territory need to be defended most

//    // Condition checked: If target territory == origin territory, take next in toDefend()
//    vector<Territory*> toDefendList = p->toDefend(game->getMap()); // TODO MAKE SURE WE DELETE THIS
//    unsigned i = 0;
//    target = p->toDefend(game->getMap()).at(i);
//    while (i<toDefendList.size()){
//        Territory* target2 = toDefendList.at(i+1);
//        if(target->getName() == target2->getName())
//        i=+1;
//    }


    // Condition checked: If there's no more armies to airlift
    if (origin->getArmies() == 0){
        numToAirlift = 0;
    } else {
        numToAirlift = rand() % origin->getArmies() + 1; // generate a random number
        while (numToAirlift > origin->getArmies()){ // make sure the condition armies <= armies in origin
            numToAirlift = rand() % origin->getArmies() + 1;
        }
    }
}

Airlift::Airlift(Player* p, Territory* origin, Territory* target) : Order (false, "airlift"){
    playerIssuing = p;
    this->origin = origin;
    this->target = target;

    // Condition checked: If there's no more armies to airlift
    if (origin->getArmies() == 0){
        numToAirlift = 0;
    } else {
        numToAirlift = rand() % origin->getArmies() + 1; // generate a random number
        while (numToAirlift > origin->getArmies()) { // make sure the condition armies <= armies in origin
        }
    }
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

Airlift &Airlift::operator=(const Airlift &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    numToAirlift = o.numToAirlift;
    return *this;
}

ostream &operator<<(ostream &os, const Airlift &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName()  << " | "
       << validated << " | origin: " << o.origin->getName() << " | target: " << o.target->getName() << " | " << o.numToAirlift << ") ";
    return os;
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

void Airlift::validate() {
    cout << "... ";
    // Check if the target territory and origin belong to the player issuing
    if (target->getOwnerName() != playerIssuing->getName() || origin->getOwnerName() != playerIssuing->getName()) {
        cout << "Invalid! - You don't own both territories" << endl;
        validated = false;
    }
    // Check if there are armies to airlift
    else if (numToAirlift == 0) {
        cout << "Invalid! - No more armies left to airlift" << endl;
        validated = false;
    }
    else{
        cout << "Valid!" << endl;
        validated = true;
    }
}

void Airlift::execute() {
    cout << "... ";
    if(validated){
        origin->setArmies(origin->getArmies()-numToAirlift); // Subtract armies from origin
        target->setArmies(target->getArmies()+numToAirlift); // Add armies to target
        cout << "Execution successful!\n" << endl;
    } else{
        cout << "Execution failed!\n" << endl;
    }
//     notify(this);
}


string Airlift::stringToLog() {
    string logStringOrder = "";
    string logStringEffect1 = "";
    string logStringEffect2 = "";
    string validation = (validated) ? "executed" : "validation failed";

    string logStringPlayer = "(Player " + playerIssuing->getName() + ") \n";
    if(validated){
        logStringOrder = "Airlift " + validation + " : Airlift " + to_string(numToAirlift) + " armies from " + origin->getName()
                         + " to " + target->getName() + " \n";
        logStringEffect1 =  to_string(origin->getArmies()) +" armies now occupy " + origin->getName() + " \n";
        logStringEffect2 =  to_string(target->getArmies()) +" armies now occupy " + target->getName() + " \n";
    } else {
        logStringOrder = "Airlift " + validation + " : Airlift 0 armies from " + origin->getName()
                         + " to " + target->getName() + " \n";
        logStringEffect1 =  to_string(origin->getArmies()) +" armies now occupy " + origin->getName() + " \n";
        logStringEffect2 =  to_string(target->getArmies()) +" armies now occupy " + target->getName() + " \n";
    }
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
    target = p->toAttack(game->getMap()).at(0);
    origin = p->getOriginTerritory(target,game->getMap());
}

Bomb::Bomb(Player* p, Territory* origin, Territory* target) : Order(false, "bomb"){
    playerIssuing = p;
    this->origin = origin;
    this->target = target;
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

Bomb &Bomb::operator=(const Bomb &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    origin = o.origin;
    target = o.target;
    return *this;
}

ostream &operator<<(ostream &os, const Bomb &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName() << " | "
       << validated << " | origin: " << o.origin->getName() << " | target: " << o.target->getName() << ") ";
    return os;
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

void Bomb::validate() {
    cout << "... ";
    // Check if target territory belongs to playerIssuing
    if (target->getOwnerName() == playerIssuing->getName()) {
        cout << "Invalid! - You can't bomb your territories" << endl;
        validated = false;
    }
    // Check for an existing Alliance or blockade protection
    else if (game->existingAlliance(origin->getOwner(), target->getOwner())) {
        cout << "Invalid! - You can't bomb territory in negotiation" << endl;
        validated = false;
    }
    // Check for blockade protection
    else if (target->getOwnerName() == "Neutral"){
        cout << "Invalid! - You can't bomb territory under protection of blockade" << endl;
        validated = false;
    }
    // Check that territories are adjacent
    else if (!(game->getMap()->adjacentTerritories(origin, target))) {
        cout << "Invalid! - Territory is not adjacent" << endl;
        validated = false;
    }else {
        cout << "Valid!" << endl;
        validated = true;
    }
}

void Bomb::execute() {
    cout << "... ";
    if (!validated) {
        cout << "Execution failed! \n" << endl;
    } else {
        int bombedArmies = (target->getArmies()) / 2;
        target->setArmies(bombedArmies);
        cout << "Execution successful! \n" << endl;
    }
//    notify(this);
}

string Bomb::stringToLog() {
    string logStringOrder = "";
    string logStringEffect = "";
    string validation = (validated) ? "executed" : "validation failed";

    string logStringPlayer = "(Player " + playerIssuing->getName() + ") \n";
    if (validated){
        logStringOrder = "Bomb " + validation + ": Send bomb from " + origin->getName() + " to " + target->getName() + "\n";
        logStringEffect = target->getName() + " has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwner()->getName() + "\n";
    } else {
        logStringOrder = "Bomb " + validation + ": Send no bomb from " + origin->getName() + " to " + target->getName() + "\n";
        logStringEffect = target->getName() + " still has " + to_string(target->getArmies()) + " armies and is under the ownership of " + target->getOwner()->getName() + "\n";
    }
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
    // Condition checked: If target territory is already Neutral (protected), take next in toDefend()
    vector<Territory*> toDefendList = p->toDefend(game->getMap());
    unsigned i = 0;
    target = p->toDefend(game->getMap()).at(i);
    while (i<toDefendList.size() && target->getOwner()->getName() == "Neutral"){
        target = p->toDefend(game->getMap()).at(i+1);
        i++;
    }
}

Blockade::Blockade(Player* p, Territory* target) : Order (false,"blockade"){
    playerIssuing = p;
    this->target = target;
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
Blockade &Blockade::operator=(const Blockade &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    target = o.target;
    return *this;
}

ostream &operator<<(ostream &os, const Blockade &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName() << " | "
       <<  validated << " | target: " << o.target->getName() << ") ";
    return os;
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

void Blockade::validate() {
    cout << "... ";
    if (target->getOwnerName() == playerIssuing->getName()) {
        validated = true;
        cout << "Valid!" << endl;
    } else {
        validated = false;
        cout << "Invalid! - You don't own this territory" << endl;
    }

}

void Blockade::execute() {
    cout << "... ";
    if (!validated) {
        cout << "Execution failed!\n" << endl;
    } else {
        int doubleArmies = (target->getArmies()) * 2;
        target->setArmies(doubleArmies);
        target->setOwner(game->getNeutralPlayer());
        cout << "Execution successful!\n" << endl;
    }
    notify(this);
}

string Blockade::stringToLog() {
    string logStringOrder = "";
    string logStringEffect = "";
    string validation = (validated) ? "executed" : "validation failed";

    string logStringPlayer = "(Player " + playerIssuing->getName() + ") \n";
    if(validated){
        logStringOrder = "Blockade " + validation + ": successfully transfer the ownership of " + target->getName() + " to Neutral Player\n";
        logStringEffect = target->getName() + " has " + to_string(target->getArmies())
                        + " armies and is under the ownership of the " + target->getOwner()->getName() + " player \n";
    } else {
        logStringOrder = "Blockade " + validation + ": unsuccessful transfer the ownership of " + target->getName() + " to Neutral Player\n";
        logStringEffect = target->getName() + " has " + to_string(target->getArmies())
                          + " armies and is still under the ownership of the " + target->getOwner()->getName() + " player \n";
    }
    return logStringPlayer + logStringOrder + logStringEffect;
}

/****************************** Negotiate *******************************/

// Default constructor
Negotiate::Negotiate() : Order(false, "negotiate"){
    playerIssuing = nullptr;
    targetPlayer = nullptr;
}

// Parameterize Constructor
Negotiate::Negotiate(Player* p) : Order(false, "negotiate") {
    playerIssuing = p;
    cout << "\nPlayer to negotiate with: ";
    string playerTargetName = "";
    cin >> playerTargetName;
    unsigned i = 0;
    // TODO: Check if the player does not exist -> re-enter player's name
    // target player = player of the name playerTargetName
    for (int i = 0; i < game->getplayer_list().size(); i++) {
        if (game->getplayer_list().at(i)->getName() == playerTargetName) {
            targetPlayer = game->getplayer_list().at(i);
        }
    }
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &original) : Order(original) {
    playerIssuing = new Player(*original.playerIssuing);
    targetPlayer = new Player(*original.targetPlayer);
    cout << "Copy constructor for Negotiate class has been called" << endl;
}

Negotiate::Negotiate(Player* p, Player* target) : Order(false, "negotiate") {
    playerIssuing = p;
    targetPlayer = target;
}

// Destructor
Negotiate::~Negotiate() {
    playerIssuing = nullptr;
    targetPlayer = nullptr;
}

Negotiate &Negotiate::operator=(const Negotiate &o) {
    Order::operator=(o);
    playerIssuing = o.playerIssuing;
    targetPlayer = o.targetPlayer;
    return *this;
}

ostream &operator<<(ostream &os, const Negotiate &o) {
    string validated = (o.validated) ? "validated" : "not validated";
    os << o.description << " (" << o.playerIssuing->getName() << " | " << validated << " | target: " << o.targetPlayer->getName() << ") ";
    return os;
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

void Negotiate::validate() {
    cout << "... ";
    if (playerIssuing->getName() == targetPlayer->getName() || targetPlayer->getName() == "Neutral") {
        validated = false;
        cout << "Invalid! - Negotiate must be done with a different player, excluding the Neutral player" << endl;
    } else {
        validated = true;
        cout << "Valid!" << endl;
    }

}

void Negotiate::execute() {
    cout << "... ";
    if (!validated) {
        cout << "Execution failed!\n" << endl;
    } else {
        game->addAlliances(playerIssuing, targetPlayer);
        cout << "Execution successful!\n" << endl;
    }
//    notify(this);
}

string Negotiate::stringToLog() {
    string logStringOrder = "";
    string validation = (validated) ? "executed" : "validation failed";

    string logStringPlayer = "(Player " + playerIssuing->getName() + ")\n";
    if (validated){
        logStringOrder = "Negotiate " + validation + ": an alliance is form between " + playerIssuing->getName() + " and " + targetPlayer->getName()
                         + " - cannot attack each other \n";
    } else {
        logStringOrder = "Negotiate " + validation + ": no alliance is formed between " + playerIssuing->getName() + " and " + targetPlayer->getName()+ "\n";
    }
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
//    notify(this);
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
// Advance execute()
//            origin->setArmies(origin->getArmies()-numToAdvance);
//            // Target is defender -> Defend Power = Target Territory numOfArmies * 70%
//            // Origin is Attacker -> Attack Power = Origin Territory numOfArmies * 60%
//            int attackPower = origin->getArmies()*0.6;
//            int defendPower = target->getArmies()*0.7;
//            if (attackPower == defendPower) {
//                target->setArmies(0);
//            }
//            else if (attackPower > defendPower){
//                target->setArmies((attackPower - defendPower)/0.6);
//                target->setOwner(playerIssuing);
//
//                playerIssuing->getHand()->drawCard(*game->getDeck());
//            }
//            else{}
//        }
