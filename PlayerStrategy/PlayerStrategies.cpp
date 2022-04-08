#include "PlayerStrategies.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"

// Initialize the Game Engine
GameEngine* PlayerStrategies::game = new GameEngine();
/****************************** Player Strategy *******************************/
// Default Constructor
PlayerStrategies::PlayerStrategies() {
    cout << "PlayerStrategies constructor called" << endl;
    type = "";
}

// Parameterized Constructor
PlayerStrategies::PlayerStrategies(string type) {
    this->type = type;
}

Player* PlayerStrategies::getPlayer() { return p; }
string PlayerStrategies::getType() { return type;}

void PlayerStrategies::setPlayer(Player *pl) { p = pl; }

// Stream insertion operator overloading
ostream& operator<< (ostream& os, const PlayerStrategies& ps){
    os << "Player Strategy";
    return os;
}


/****************************** Human Player Strategy *******************************/
/*
 * Requires user interaction :
 * User chooses whether advance is to move or to attack
 * User chooses which territory is returned from their toAttack() method
 * User chooses which territory is returned from their toDefend() method
 */

// Default Constructor
HumanPlayerStrategy::HumanPlayerStrategy(): PlayerStrategies("Human"){
    cout << "Human Strategy Default constructor called" << endl;
}

void HumanPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Strategy called" << endl;
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    string input;

    if (equalsIgnoreCase("deploy", type)) {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        p->addOrderList(d);// Add order to list
    }
    else if (equalsIgnoreCase("advance", type)) {
        cout << "\nWhat type of advance would " << p->getName() << " Player like to issue ? (move, attack, none)" << endl;
        cin >> input;
        while (!equalsIgnoreCase("move", input) || !equalsIgnoreCase("attack", input) || !equalsIgnoreCase("none", input)) {
            cout << "\nInvalid input ! Try Again." << endl;
            cin >> input;
        }
        if (!equalsIgnoreCase("none", input)) {
            Advance* a = new Advance(p, input);
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
                    cout << "\nInvalid input" << p->getName() << " does not have that card type in hand"
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
    cout << "toAttack() in Strategy called" << endl;
    Map* m = game->getMap();
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would" << p->getName() << " Player like to attack from ?" << endl;
    cin >> input;

    while (p->checkTerritoryOwn(input) == NULL) {
        cout << "\nInvalid input " << p->getName() << "Player does not own territory ! Try Again." << endl;
        cin >> input;
    }

    Territory* territory = p->checkTerritoryOwn(input);
    vector<Territory*> territories = m->getConnectedTerritories(territory->getName());

    cout << "\nChosen territory : " << input <<". What territory would" << p->getName() << " Player like to attack ?" << endl;
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
    return returnTerritories;
}

vector<Territory*> HumanPlayerStrategy::toDefend() {
    cout << "toDefend() in Strategy called" << endl;
    Map* m = game->getMap();
    vector<Territory*> returnTerritories;
    string input;

    cout << "\nWhat territory would" << p->getName() << " Player like to defend ?" << endl;
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
ostream& operator<< (ostream& os, const HumanPlayerStrategy& ps){
    os << "Human Player Strategy";
    return os;
}


/****************************** Aggressive Player Strategy *******************************/
/* computer player that focuses on attack
 * deploys or advances armies on its strongest country
 * always advances to enemy territories until it cannot do so anymore
 */

// Default constructor
AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategies("Aggressive"){
    cout << "Aggressive Strategy Default constructor called" << endl;
}

void AggressivePlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Strategy called" << endl;
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (equalsIgnoreCase("deploy", type)) {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(p);
        p->addOrderList(d); // Add order to the list
    }
    else if (equalsIgnoreCase("advance", type)) {
        Advance* a = new Advance(p, "attack");
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
    cout << "toAttack() in Strategy called" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;
    Map* m = game->getMap();

    for (Territory* territory : p->getTerritoryList()) { // Looping through the player's territories
        int number_armies = 0;
        string name = territory->getName();

        // step 1 get connected territories
        vector<Territory*> surround_territory = m->getConnectedTerritories(name); // Getting surrounding territories of the player's territory

        if (surround_territory.empty()) { // If the territories do not have any surrounding or connected territories
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

        for (Territory* i : surround_territory) { // Delete the vector of the surrounding to avoid memory leak
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

    return attack_territories;
}

vector<Territory*> AggressivePlayerStrategy::toDefend() {
    cout << "toDefend() in Strategy called" << endl;
    vector<Territory *> defend_territories = vector<Territory *>();
    pair<int, Territory *> pairs;
    vector<pair<int, Territory *>> ordering;
    Map* m = game->getMap();

    for (Territory *territory: p->getTerritoryList()) { // Looping through the player's territories

        int number_surrounding = 0;
        string name = territory->getName();

        vector<Territory *> surrounded_territories = m->getConnectedTerritories(name);

        if (surrounded_territories.empty()) {
            number_surrounding = -1;
        }
            // step 1 check each territories numbers of enemies surrounding
        else {
            for (Territory *t: surrounded_territories) {
                if ((t->getOwner()->getName() != p->getName())) {
                    number_surrounding = number_surrounding + 1;
                }
            }
        }

        // step 2 pair territory and their number of surrounding territories, add pair to vector
        if (number_surrounding != 0) {
            pairs.first = territory->getArmies();
            pairs.second = territory;
            ordering.push_back(pairs);
        }

        for (Territory *i: surrounded_territories) { // Delete the vector of the surrounding to avoid memory leak
            i = nullptr;
        }

        // step 3 sort and seperate territories in pair
        sort(ordering.begin(), ordering.end());

        for (pair<int, Territory *> p: ordering) {
            defend_territories.insert(defend_territories.begin(),
                                      p.second);// Pushes them in one by one because they are already sorted (insert at the front because it is highest number of armies to smallest)
            p.second = nullptr; // Dangling pointer avoidance
        }

        return defend_territories;
    }
}

// Stream insertion operator overloading
ostream& operator<< (ostream& os, const AggressivePlayerStrategy& ps){
    os << "Aggressive Player Strategy";
    return os;
}


/****************************** Benevolent Player Strategy *******************************/
/* computer player that focuses on protecting its weak countries
 * deploys or advances armies on its weakest countries
 * never advances to enemy territories
 */

// Default constructor
BenevolentPlayerStrategy::BenevolentPlayerStrategy() : PlayerStrategies("Benevolent"){
    cout << "Benevolent Strategy Default constructor called" << endl;
}

void BenevolentPlayerStrategy::issueOrder(string type){
    cout << "issueOrder() in Strategy called" << endl;

}

// TODO :: Benevolent only defend and never advance to enemy territories -> no use for toAttack()
vector<Territory*> BenevolentPlayerStrategy::toAttack() {
    cout << "toAttack() in Strategy called" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    Map* m = game->getMap();

    return attack_territories;
}

vector<Territory*> BenevolentPlayerStrategy::toDefend() {
    cout << "toDefend() in Strategy called" << endl;
    vector<Territory *> defend_territories = vector<Territory *>();
    Map* m = game->getMap();
    return defend_territories;
}

// Stream insertion operator overloading
ostream& operator<< (ostream& os, const BenevolentPlayerStrategy& ps){
    os << "Benevolent Player Strategy";
    return os;
}


/****************************** Neutral Player Strategy *******************************/
/*
 * Player never issues any orders
 * If a Neutral player is attacked, it becomes an Aggressive player
 */

// Default constructor
NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategies("Benevolent"){
    cout << "Neutral Strategy Default constructor called" << endl;
}

// TODO :: Neutral player doesn't issue orders, and therefore has no use for a toAttack() & toDefend() & issueOrder() is empty
void NeutralPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Strategy called" << endl;
}

vector<Territory*> NeutralPlayerStrategy::toAttack() {
    cout << "toAttack() in Strategy called" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    return attack_territories;
}

vector<Territory*> NeutralPlayerStrategy::toDefend() {
    cout << "toDefend() in Strategy called" << endl;
    vector<Territory*> defend_territories = vector<Territory*>();
    return defend_territories;
}

// Stream insertion operator overloading
ostream& operator<< (ostream& os, const NeutralPlayerStrategy& ps){
    os << "Neutral Player Strategy";
    return os;
}


/****************************** Cheater Player Strategy *******************************/
/* computer player that automatically conquers all territories that are adjacent to its own territories
 * only once per turn
 */

// Default constructor
CheaterPlayerStrategy::CheaterPlayerStrategy() : PlayerStrategies("Cheater"){
    cout << "Cheater Strategy Default constructor called" << endl;
}

void CheaterPlayerStrategy::issueOrder(string type) {
    cout << "issueOrder() in Strategy called" << endl;

}

// TODO :: Cheater does not need to attack or defend to conquered a territory, no use for toAttack() & toDefend()
vector<Territory*> CheaterPlayerStrategy::toAttack() {
    cout << "toAttack() in Strategy called" << endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    Map* m = game->getMap();
    return attack_territories;
}

vector<Territory*> CheaterPlayerStrategy::toDefend() {
    cout << "toDefend() in Strategy called" << endl;
    vector<Territory*> defend_territories = vector<Territory*>();
    Map* m = game->getMap();
    return defend_territories;
}


// Stream insertion operator overloading
ostream& operator<< (ostream& os, const CheaterPlayerStrategy& ps){
    os << "Cheater Player Strategy";
    return os;
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

    for (Card* c : h->hand) {
        if (equalsIgnoreCase(c->getType(), type)) return index;
        index = index + 1;
    }

    return -1;
}