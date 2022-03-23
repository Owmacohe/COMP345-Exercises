#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "Player.h"

// Default constructor
Player::Player() {
    name = "empty player";
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    reinforcePool = 0;
    deployList = new OrdersList;
    //cout << "[Player default constructor]" << endl;
}

// Param constructor
Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o, int r): name(n), reinforcePool(r) {
    territories = vector<Territory*>();
    for (Territory* i : t) {
        territories.push_back(new Territory(*i));
    }

    hand = new Hand(*h);
    orders = new OrdersList(*o);
    //cout << "[Player param constructor]" << endl;
}

// Copy constructor
Player::Player(const Player &p) {
    name = p.name;
    territories = vector<Territory*>();
    for (Territory* i : p.territories) {
        territories.push_back(new Territory(*i));
    } // Goes through copying vector of territory pointers, creates new pointers based on value and pushes to copied vector

    hand = new Hand(*(p.hand));
    orders = new OrdersList(*(p.orders));
    reinforcePool = p.reinforcePool;
    //cout << "[Player copy constructor]" << endl;
}

// Destructor
Player::~Player() {
    for (Territory* i : territories) {
        delete i;
        i = NULL;
        //cout << "[Player territory destructor]" << endl;
    }

    delete hand;
    hand = NULL;
    delete orders;
    orders = NULL;

    //cout << "[Player destructor]" << endl;
}

// Returns a vector list of territories for player to defend in priority
// Priority is determined by which territories are surrounded by the most enemy territories
vector<Territory*> Player::toDefend(Map* m) {
    vector<Territory*> defend_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;
    //cout<<"Begin toDefend"<<endl;
    for (Territory* territory : territories) {
        int number_surrounding = 0;
        string name = territory->getName();
        //cout << "Looking at territory : " << territory->getName() << endl;
        vector<Territory *> surrounded_territories = m->getConnectedTerritories(name);
        //cout<< surrounded_territories.empty()<<endl;
        if (surrounded_territories.empty()) number_surrounding = -1;
            // step 1 check each territories numbers of enemies surrounding
        else {
            for (Territory *t: surrounded_territories) {
                if (t->getOwner()->getName() != name || t->getOwner()->getName() != "Neutral") { // Neutral player is not enemy or player
                    number_surrounding = number_surrounding + 1;
                }
            }
        }
        // step 2 pair territory and their number of surrounding territories, add pair to vector
        if (number_surrounding != 0) {
            //cout<<"Putting in pair : " << territory->getName() <<endl;
            pairs.first = territory->getArmies();
            pairs.second = territory;
            ordering.push_back(pairs);
        }

        for (Territory* i : surrounded_territories) { // Delete the vector of the surrounding to avoid memory leak
            i = NULL;
        }
    }
    // step 3 sort and seperate territories in pair
    sort(ordering.begin(), ordering.end());
    for (pair<int, Territory*> p : ordering) {
        //cout<<"Ordering territory : " << p.second->getName() <<endl;
        defend_territories.insert(defend_territories.end(), p.second); // Pushes them in one by one because they are already sorted (insert at the front because it is sorted small to large)
        p.second = NULL; // Dangling pointer avoidance
    }
    return defend_territories;
}

// Returns a vector list of territories for player to attack based on territories touching edges of players owned territories in priority
// Priority is determined by which enemy territories connected have most armies
vector<Territory*> Player::toAttack(Map* m) {
    cout<<"Begin toAttack"<<endl;
    vector<Territory*> attack_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;

    for (Territory* territory : territories) { // Looping through the player's territories
        cout << "Looking at territory : " << territory->getName() << endl;
        int number_armies = 0;
        string name = territory->getName();

        // step 1 get connected territories

        vector<Territory*> surround_territory = m->getConnectedTerritories(name); // Getting surrounding territories of the player's territory

        if (surround_territory.empty()) { // If the territories do not have any surrounding or connected territories --> ERROR OR VERY RARE, TEMPORARY CONDITION
            cout << "Surround territory vector for that territory is empty." << endl;
            continue; // Go to next Territory to continue searching for a territory to attack
        }
        cout<< "First Territory in the the surrounded Territories" << *(surround_territory.at(0))<<endl;

        // step 2 for each connected territory that's an enemy's count the number armies
        cout << "step 2 for each connected territory that's an enemy's count the number armies" << endl;
        for (Territory* t : surround_territory) {
            if (t->getOwner()->getName() != name || t->getOwner()->getName() != "Neutral") { // Neutral player is not enemy or player
                number_armies = t->getArmies();
                // step 3 pair enemy territory and their number of armies, add pair to vector
                cout<<"Putting in pair : " << t->getName() <<endl;
                pairs.first = number_armies;
                pairs.second = t;
                ordering.push_back(pairs);
            }
        }
        for (Territory* i : surround_territory) { // Delete the vector of the surrounding to avoid memory leak
            i = NULL;
        }
    }

    // step 3 sort and separate territories in pair
    cout << "step 3 sort and separate territories in pair" << endl;
    if(ordering.empty()){ cout << "No territories to Attack." << endl;}

    else {
    sort(ordering.begin(), ordering.end());
    for (pair<int, Territory*> p : ordering) {
        cout<<"Ordering territory : " << p.second->getName() <<endl;
        attack_territories.insert(attack_territories.end(), p.second); // Pushes them in one by one because they are already sorted (insert at the front because it is sorted small to large)
        p.second = NULL; // Dangling pointer avoidance
    }}
    return attack_territories;
}

void Player::issueOrder(string type) { 
    // Set to all lowercase
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "deploy") {
        // Issues deploy orders based on toDefend()
        Deploy* d = new Deploy(this);
        orders->addOrder(d); // Add order to list
    }
    else if (type == "advance") {
        Advance* a = new Advance(this);
        orders->addOrder(a);
    }
    // Orders that involve card will be issued using playCard()
    else {
        cout << "Invalid order" << endl;
    }
}

// Return number of armies player has
int Player::getNumberOfArmies() {
    int sum = 0;
    for (Territory* i : territories) {
        sum = sum + i->getArmies();
    }
    return sum;
}

// Return number of territories player has
int Player::getNumberOfTerritories() {
    int sum = 0;
    for (Territory* i : territories) {
        sum = sum + 1;
    }
    return sum;
}

// Return an origin territory adjacent to a target territory
Territory* Player::getOriginTerritory(Territory *target_territory, Map* m) {
    vector<Territory*> surround_territory = m->getConnectedTerritories(target_territory->getName());
    for (Territory* t : surround_territory) {
        if (t->getOwner()->getName() == name) return t;
    }

    return NULL;
}

// Return deploy list
OrdersList* Player::getDeployList() {
    return deployList;
}

void Player::addToReinforcePool(int armies) {
    reinforcePool += armies;
}

void Player::removeFromReinforcePool(int armies) {
    reinforcePool -= armies;
}

// Mutators and Accessors
void Player::setName(string n) { name = n; }
void Player::setTerritory(vector<Territory*> t) {
    for (Territory* i : t) {
        territories.push_back(i);
    }
}
void Player::assignTerritory(Territory* t){
    territories.push_back(t);
}
void Player::setHand(Hand* h) { hand = h; }
void Player::setOrder(OrdersList* o) { orders = o; }
void Player::setReinforcementPool(int armies) {reinforcePool = armies;}

string Player::getName() { return name; }
vector<Territory*> Player::getTerritoryList() { return territories; }
Hand* Player::getHand() { return hand; }
OrdersList* Player::getOrder() { return orders; }
int Player::getReinforcePool(){ return reinforcePool;}

// End of Mutators and Accessors

// Assignment operator
Player& Player::operator = (const Player& p){
    this->name = p.name;
    for (Territory* i : p.territories) {
        this->territories.push_back(i);
    }
    this->hand = p.hand;
    this->orders = p.orders;
    this->reinforcePool = p.reinforcePool;
    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream &strm, const Player &p) {
    string t = "";
    for (Territory* i : p.territories) {
        t += (*i).getName() +" | ";
    }

    return strm <<
                "PLAYER: " << p.name <<
                "\n    Territories: " <<endl<< t.substr(0, t.length() - 2) <<
                "\n    Players hand, " << *p.hand <<
                "\n    Players orders, " << *p.orders <<
                "\n    Players reinforcement pool has, " << p.reinforcePool << " armies"<<endl;
}

