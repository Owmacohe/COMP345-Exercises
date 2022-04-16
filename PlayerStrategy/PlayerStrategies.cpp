#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include <random>

// Initialize the Game Engine
GameEngine* PlayerStrategies::game = new GameEngine();
/****************************** Player Strategy *******************************/
// Default Constructor
PlayerStrategies::PlayerStrategies() {
    cout << "PlayerStrategies constructor called" << endl;
    type = "";
    neutralAttack = nullptr;
}

// Parameterized Constructor
PlayerStrategies::PlayerStrategies(string t) : type(t) {
    neutralAttack = nullptr;
}

// Parameterized Constructor
PlayerStrategies::PlayerStrategies(Player *pl, string t) : p(pl), type(t) {
    neutralAttack = nullptr;
}

Player* PlayerStrategies::getPlayer() { return p; }
string PlayerStrategies::getType() { return type; }
Player* PlayerStrategies::getNeutralAttack() { return neutralAttack; }

void PlayerStrategies::setPlayer(Player *pl) { p = pl; }
void PlayerStrategies::setNeutralAttack(Player* p) { neutralAttack = p; }

// Stream insertion operator overloading
ostream& PlayerStrategies::write(ostream &strm) const {
    return strm << "Player Strategy";
}

/****************************** Human Player Strategy *******************************/
// Default Constructor
HumanPlayerStrategy::HumanPlayerStrategy(): PlayerStrategies("Human") {
    cout << "Human Strategy Default constructor called" << endl;
}

// Parameterized constructor
HumanPlayerStrategy::HumanPlayerStrategy(Player *pl) : PlayerStrategies(pl, "Human") {
    cout << "Human Strategy Parameterized constructor called" << endl;
}

void HumanPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Human Strategy called" << endl;
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    string input;

    if (equalsIgnoreCase("deploy", type)) {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        cout << *d << endl; // TODO: delete this cout after testing
        // Add order to list
        p->addOrderList(d);
    }
    else if (equalsIgnoreCase("advance", type)) {
        cout << "\nWhat type of advance would " << p->getName() << " Player like to issue ? (move, attack, none)" << endl;
        cin >> input;
        while (!equalsIgnoreCase("move", input) && !equalsIgnoreCase("attack", input) && !equalsIgnoreCase("none", input)) {
            cout << "\nInvalid input ! Try Again." << endl;
            cin >> input;
        }
        if (!equalsIgnoreCase("none", input)) {
            Advance* a = new Advance(p, input);
            cout << *a << endl; // TODO: delete this cout after testing
            p->addOrderList(a);
        }
    }
    else if (equalsIgnoreCase("card", type)) {
        int index = -1;
        cout << "\nWhich card would you like to play ? (airlift, bomb, blockade, negotiate, none)" << endl;
        cin >> input;

        if (!equalsIgnoreCase("none", input)) {
            while (index < 0) {
                index = checkCardInHand(input, p->getHand());
                if (index >= 0) {
                    p->getHand()->playCard(index, *game->getDeck(), *p->getOrder(), p);
                    break;
                }
                else {
                    cout << "\nInvalid input " << p->getName() << " does not have that card type in hand"
                         << " ! Try Again." << endl;
                    cin >> input;
                }
            }
        }
    }
    else {
        cout << "Invalid order" << endl;
    }
}

vector<Territory*> HumanPlayerStrategy::toAttack() {
    cout << "toAttack() in Human Strategy called" << endl;
    Map* m = game->getMap();
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would " << p->getName() << " Player like to attack from ?" << endl;
    cin >> input;

    while (p->checkTerritoryOwn(input) == NULL) {
        cout << "\nInvalid input " << p->getName() << " Player does not own territory ! Try Again." << endl;
        cin >> input;
    }

    Territory* territory = p->checkTerritoryOwn(input);
    vector<Territory*> territories = m->getConnectedTerritories(territory->getName());

    cout << "\nChosen territory : " << input <<". What territory would " << p->getName() << " Player like to attack ?" << endl;
    cin >> input;
    bool flag = false;
    while (flag == false) {
        for (Territory* t : territories) {
            if (equalsIgnoreCase(t->getName(), input) && (t->getOwner()->getName() != p->getName())) {
                returnTerritories.push_back(t);
                flag = true;
                break;
            }
        }
        if (flag == false) {
            cout << "\nInvalid input ! Try Again." << endl;
            cin >> input;
        }
    }

    if (returnTerritories.at(0)->getOwner()->getPlayerStrategy()->getType() == "Neutral") {
        setNeutralAttack(returnTerritories.at(0)->getOwner());
    }

    return returnTerritories;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    cout << "toDefend() in Human Strategy called" << endl;
    Map* m = game->getMap();
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would " << p->getName() << " Player like to defend ?" << endl;
    cin >> input;

    while (p->checkTerritoryOwn(input) == NULL) {
        cout << "\nInvalid input " << p->getName() << "Player does not own territory ! Try Again." << endl;
        cin >> input;
    }

    vector<Territory*> territories = p->getTerritoryList();
    for (Territory* t : territories) {
        if (equalsIgnoreCase(t->getName(), input)) {
            returnTerritories.push_back(t);
            break;
        }
    }
    return returnTerritories;
}

// Stream insertion operator overloading
ostream& HumanPlayerStrategy::write(ostream &strm) const {
    return strm << "Human Player Strategy";
}


/****************************** Aggressive Player Strategy *******************************/
// Default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategies("Aggressive") {
    cout << "Aggressive Strategy Default constructor called" << endl;
}

// Parameterized constructor
AggressivePlayerStrategy::AggressivePlayerStrategy(Player *pl) : PlayerStrategies(pl, "Aggressive") {
    cout << "Aggressive Strategy Parameterized constructor called" << endl;
}

void AggressivePlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Aggressive Strategy called" << endl;
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (equalsIgnoreCase("deploy", type)) {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        cout << *d << endl; // TODO: delete this cout after testing
        // Add order to the list
        p->addOrderList(d);
    }
    else if (equalsIgnoreCase("advance", type)) {
        Advance* a = new Advance(p, "attack"); // TODO: delete this cout after testing
        cout << *a << endl;
        // Add order to the list
        p->addOrderList(a);
    }
        // Orders that involve card will be issued using playCard()
    else if (equalsIgnoreCase("card", type)) {
        int index = -1;
        index = checkCardInHand("bomb", p->getHand());
        if (index >= 0) {
            // Only is able to play bomb card
            p->getHand()->playCard(index, *game->getDeck(), *p->getOrder(), p);
        }
    }
    else {
        cout << "Invalid order" << endl;
    }
}

vector<Territory*> AggressivePlayerStrategy::toAttack() {
    cout << "toAttack() in Aggressive Strategy called" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    pair<int, Territory*> pairs = pair<int, Territory*>();
    vector<pair<int, Territory*>> ordering = vector<pair<int, Territory*>>();
    Map* m = game->getMap();

    // Looping through the player's territories
    for (Territory* territory : p->getTerritoryList()) {
        int number_armies = 0;
        string name = territory->getName();

        // step 1 get connected territories
        // Getting surrounding territories of the player's territory
        vector<Territory*> surround_territory = m->getConnectedTerritories(name);

        // If the territories do not have any surrounding or connected territories
        if (surround_territory.empty()) {
            cout << "Surround territory vector for that territory is empty."  << endl;
        }

        // step 2 for each connected territory that's an enemy's count the number armies
        for (Territory* t : surround_territory) {
            if ((t->getOwner()->getName() != p->getName())) {
                number_armies = t->getArmies();
                // step 3 pair enemy territory and their number of armies, add pair to vector
                pairs.first = number_armies;
                pairs.second = t;
                ordering.push_back(pairs);
            }
        }
        // Delete the vector of the surrounding to avoid memory leak
        for (Territory* i : surround_territory) {
            i = nullptr;
        }
    }

    // step 3 sort and separate territories in pair
    if(ordering.empty()) {
        cout << "No territories to Attack." << endl;
    }
    else {
        sort(ordering.begin(), ordering.end());
        ordering.erase(unique(ordering.begin(), ordering.end()), ordering.end());
        for (pair<int, Territory*> p : ordering) {
            attack_territories.insert(attack_territories.end(), p.second); // Pushes them in one by one because they are already sorted (insert at the front because it is sorted small to large)
            p.second = nullptr; // Dangling pointer avoidance
        }
    }

    if (attack_territories.at(0)->getOwner()->getPlayerStrategy()->getType() == "Neutral") {
        setNeutralAttack(attack_territories.at(0)->getOwner());
    }

    return attack_territories;
}

// toDefend() = deploy to strongest territory (territory with most armies)
vector<Territory*> AggressivePlayerStrategy::toDefend() {
    cout << "toDefend() in Aggressive Strategy called" << endl;
    vector<Territory *> defend_territories = vector<Territory *>();
    Map* m = game->getMap();
    int max = p->getTerritoryList()[0]->getArmies();
    int teriWithMaxArmiesIndex = 0;
    // check for the strongest territory
    for (int i = 0; i < p->getTerritoryList().size(); i++) {
        if (p->getTerritoryList()[i]->getArmies() > max) {
            max = p->getTerritoryList()[i]->getArmies();
            teriWithMaxArmiesIndex = i;
        }
    }

    defend_territories.push_back(p->getTerritoryList().at(teriWithMaxArmiesIndex));
    return defend_territories;
}

// Stream insertion operator overloading
ostream& AggressivePlayerStrategy::write(ostream &strm) const {
    return strm << "Aggressive Player Strategy";
}

/****************************** Benevolent Player Strategy *******************************/
// Default constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy() : PlayerStrategies("Benevolent") {
    cout << "Benevolent Strategy Default constructor called" << endl;
}

// Parameterized constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player *pl) : PlayerStrategies(pl, "Benevolent") {
    cout << "Benevolent Strategy Parameterized constructor called" << endl;
}

void BenevolentPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Benevolent Strategy called" << endl;
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (equalsIgnoreCase("deploy", type)) {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        cout << *d << endl; // TODO: delete this cout after testing
        // Add order to the list
        p->addOrderList(d);
    }
    else if (equalsIgnoreCase("advance", type)) {
        Advance* a = new Advance(p, "move");
        cout << *a << endl; // TODO: delete this cout after testing
        // Add order to the list
        p->addOrderList(a);
    }
    //TODO: should be able to use airlift, negotiate, and blockade cards
    // I would suggest getting all card indexes for each type, putting them in an array and then shuffle the array using shuffle(array, array+3, default_random_engine(0)) , (the 3 being the size of the array)
    // then looping through the array until you find an value that is not -1 (-1 means the card is not in the hand) and play the card at that index then break from loop so only one card is played
    // Orders that involve card will be issued using playCard()

    else if (equalsIgnoreCase("card", type)){
        vector<int> indices = vector<int>();
       //gets all indices of the cards of the types airlift, blockade
        for(int i =0 ; i<p->getHand()->numCardInHand; i++){
            if (p->getHand()->hand[i]->getType() == "airlift"){
                indices.push_back(i);
            }
            if (p->getHand()->hand[i]->getType() == "blockade"){
                indices.push_back(i);
            }
        }

        if(indices.size()>0) {
            //shuffle the vector
            shuffle(indices.begin(), indices.end(), default_random_engine());

            //pick the first card in the vector to be played
            p->getHand()->playCard(indices[0], *game->getDeck(), *p->getOrder(), p);
        } else {
            cout << "There is no airlift or blockade to be played, only other types" << endl;
        }
    }
    else {
        cout << "Invalid order" << endl;
    }
}


vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    cout << "ERROR! - Benevolent player cannot call toAttack() - return empty vector" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    return attack_territories;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    cout << "toDefend() in Benevolent Strategy called" << endl;
    vector<Territory *> defend_territories = vector<Territory *>();
    Map* m = game->getMap();
    int min = p->getTerritoryList()[0]->getArmies();
    int teriWithMinArmiesIndex = 0;

    // check for the weakest territory
    for (int i = 0; i < p->getTerritoryList().size(); i++) {
        if (p->getTerritoryList()[i]->getArmies() < min) {
            min = p->getTerritoryList()[i]->getArmies();
            teriWithMinArmiesIndex = i;
        }
    }

    defend_territories.push_back(p->getTerritoryList().at(teriWithMinArmiesIndex));
    return defend_territories;
}

// Stream insertion operator overloading
ostream& BenevolentPlayerStrategy::write(ostream &strm) const {
    return strm << "Benevolent Player Strategy";
}


/****************************** Neutral Player Strategy *******************************/
// Default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategies("Neutral") {
    cout << "Neutral Strategy Default constructor called" << endl;
}

// Parameterized constructor
NeutralPlayerStrategy::NeutralPlayerStrategy(Player *pl) : PlayerStrategies(pl, "Neutral") {
    cout << "Neutral Strategy Parameterized constructor called" << endl;
}

void NeutralPlayerStrategy::issueOrder(string type) {
    cout << "ERROR! - Neutral player cannot call issueOrder()" << endl;
}

// Neutral player never issue an order. toAttack() & toDefend() returns an empty vector
vector<Territory*> NeutralPlayerStrategy::toAttack() {
    cout << "ERROR! - Neutral player cannot call toAttack() - return empty vector" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    return attack_territories;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
    cout << "ERROR! -  Neutral player cannot call toDefend() - return empty vector" << endl;
    vector<Territory*> defend_territories = vector<Territory*>();
    return defend_territories;
}

// Stream insertion operator overloading
ostream& NeutralPlayerStrategy::write(ostream &strm) const {
    return strm << "Neutral Player Strategy";
}

/****************************** Cheater Player Strategy *******************************/
// Default constructor
CheaterPlayerStrategy::CheaterPlayerStrategy() : PlayerStrategies("Cheater") {
    cout << "Cheater Strategy Default constructor called" << endl;
}

// Parameterized constructor
CheaterPlayerStrategy::CheaterPlayerStrategy(Player *pl) : PlayerStrategies(pl, "Cheater") {
    cout << "Cheater Strategy Parameterized constructor called" << endl;
}

void CheaterPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Cheater Strategy called" << endl;
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (equalsIgnoreCase("deploy", type)) {
        //Deploy in a random territory on his list
        Deploy* d = new Deploy(p);
        p->addOrderList(d); // Add order to the list
    }
    //TODO : we shouldn't use advance tho because its an automatic ownership of all surrounding territories
    // i would just use also else if so that when they arent doing a deploy they are cheating
    // so the advance code isnt needed either
    // we just want an else if that will set all surrounding territories to be owned by the cheater
    // loop through the players territories and call the getConnectedTerritories(territoryname) and set all those territories in that vector to be owned by the cheater
    // so youll have an embeded loop in your loop for the territories

    else if (equalsIgnoreCase("advance", type)) {   //TODO: what's gonna be the condition here? i already added the 2 loops inside
        vector<Territory*> territoriesToBeStolen = vector<Territory*>();
        Map * m = game->getMap();
        for (Territory * t : p->getTerritoryList()){
            territoriesToBeStolen = m->getConnectedTerritories(t->getName());
            for(Territory * ter: territoriesToBeStolen){
                ter->setOwner(p);
                p->assignTerritory(ter);
                if (ter->getOwner()->getPlayerStrategy()->getType() == "Neutral") {
                    setNeutralAttack(ter->getOwner());
                }
            }
        }
    } else if ((equalsIgnoreCase("card", type))) {
        cout<<"no cards are allowed for this strategy"<<endl;
    } else {
        cout << "Invalid order" << endl;
    }
}

// Cheater does not need to attack or defend to conquer a territory. toAttack() & toDefend() returns an empty vector
vector<Territory*> CheaterPlayerStrategy::toAttack() {
    cout << "ERROR! -  Cheater player cannot call toAttack() - return empty vector" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    return attack_territories;
}

vector<Territory*> CheaterPlayerStrategy::toDefend() {
    cout << "ERROR! -  Cheater player cannot call toDefend() - return empty vector" << endl;
    vector<Territory*> defend_territories = vector<Territory*>();
    defend_territories = p->getTerritoryList();
    return defend_territories;
}


// Stream insertion operator overloading
ostream& CheaterPlayerStrategy::write(ostream &strm) const {
    return strm << "Cheater Player Strategy";
}


/****************************** Free Function *******************************/
// Checks for returns true for strings that are equal ignoring case
bool equalsIgnoreCase(string s1, string s2) {
    // Change to lower case
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

    if (s1 == s2) {
        return true;
    }
    else {
        return false;
    }
}

// Check that a card type is in a specific hand
int checkCardInHand(string type, Hand* h) {
    int index = 0; // Returns index of card in hand, -1 if card is not in hand
    if (h->numCardInHand > 0) {
        for (Card* c : h->hand) {
            if (equalsIgnoreCase(c->getType(), type)) return index;
            index = index + 1;
        }
    } else {
        cout << "NOTIFY! - You have no card" << endl;
    }
    return -1;
}