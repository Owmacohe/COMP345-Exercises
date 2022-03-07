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

vector<Territory*> Player::toDefend(Map m) {
    vector<Territory*> defend_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;

    for (Territory* territory : territories) {
        int number_surrounding = 0;
        string name = territory->getName();
        vector<Territory*> surround_territory = m.getConnectedTerritories(name);
        //step 1 check each territories numbers of enemies surrounding 
        for (Territory* t : surround_territory) {
            if (t->getOwner()->getName() != name) {
                number_surrounding = number_surrounding + 1;
            }
        }
        //step 2 pair territory and their number of surrounding territories, add pair to vector
        pairs.first = number_surrounding;
        pairs.second = territory;

        ordering.push_back(pairs);

        for (Territory* i : surround_territory) { // delete the vector of the surrounding to avoid memory leak
            delete i;
            i = NULL;
        }
    }
    //step 3 sort and seperate territories in pair 
    sort(ordering.begin(), ordering.end());
    for (pair<int, Territory*> p : ordering) {
        defend_territories.push_back(p.second); //pushes them in one by one because they are already sorted
        delete p.second; // delete the vector of pairs to avoid memory leak
        p.second = NULL;
    }
    return defend_territories;
}

// Returns a vector list of territories for player to attack based on territories touching edges of players owned territories in priority
// Priority is determined by which territories are surrounded by the most player owned territories
vector<Territory*> Player::toAttack(Map m) {
    vector<Territory*> attack_territories = vector<Territory*>();
    pair<int, Territory*> pairs;
    vector<pair<int, Territory*>> ordering;

    for (Territory* territory : territories) {
        int number_surrounding = 0;
        string name = territory->getName();
        vector<Territory*> surround_territory = m.getConnectedTerritories(name);
        //step 1 check each territories numbers of enemies surrounding 
        for (Territory* t : surround_territory) {
            if (t->getOwner()->getName() == name) { //FIX CURRENTLY RETURNS THE PLAYERS OWN TERRITORIES LOL JUST FIX LOGIC
                number_surrounding = number_surrounding + 1;
            }
        }
        //step 2 pair territory and their number of surrounding territories, add pair to vector
        pairs.first = number_surrounding;
        pairs.second = territory;

        ordering.push_back(pairs);

        for (Territory* i : surround_territory) { // delete the vector of the surrounding to avoid memory leak
            delete i;
            i = NULL;
        }
    }
    //step 3 sort and seperate territories in pair 
    sort(ordering.begin(), ordering.end());
    for (pair<int, Territory*> p : ordering) {
        attack_territories.push_back(p.second); //pushes them in one by one because they are already sorted
        delete p.second; // delete the vector of pairs to avoid memory leak
        p.second = NULL;
    }
    return attack_territories;
}
// NOW I AM THINKING THAT ISSUE ORDER JUST PUTS THEM IN THE LIST
// AND SO IN GAMEENGINE WE CHECK THE CARD AND WE CAN STILL ISSUE AN ORDER AS LONG AS THEY HAVE CARD
// so in game engine it will loop issue order for deploy and in game engine it will check card and check advacne loop,
// all that issue does is put it in its list of things to do

void Player::issueOrder(string type) { // HAVE IT GIVE PLAYER THIS->PLAYER
    if (type == "deploy") {
        Deploy* o = new Deploy; //order type create
        orders->addOrder(o); //add order to list
    }
    else if (type == "advance") {
        Advance* o = new Advance;
        orders->addOrder(o);
    }
    else if (type == "bomb") {
        Bomb* o = new Bomb;
        orders->addOrder(o);
    }
    else if (type == "blockade") {
        Blockade* o = new Blockade;
        orders->addOrder(o);
    }
    else if (type == "airlift") {
        Airlift* o = new Airlift;
        orders->addOrder(o);
    }
    else if (type == "negotiate") {
        Negotiate* o = new Negotiate;
        orders->addOrder(o);
    }
    else if (type == "reinforcement") {
        Reinforcement* o = new Reinforcement;
        orders->addOrder(o);
    }
    else {
        cout << "Invalid order" << endl;
    }
}
// void Player::issueOrder(int reinforcements) {
//     //add deploy for all of the territories returned by toDefend() and will be pulled for deploylist ??
//     //for loo adds deploy to orderlist for the number of armies in reinforcements
//     for (int i = 0; i < reinforcements ; i++) {
//         Deploy* o = new Deploy; //order type create
//         orders->addOrder(o); //add order to list
//     }
// }

// Return number of armies player has
int Player::getNumberOfArmies() {
    int sum = 0;
    for (Territory* i : territories) {
        sum = sum + i->getArmies();
    }
    return sum;
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
void Player::setHand(Hand* h) { hand = h; }
void Player::setOrder(OrdersList* o) { orders = o; }
void Player::setReinforcementPool(int armies) {reinforcePool = armies;}

string Player::getName() { return name; }
vector<Territory*> Player::getTerritory() { return territories; }
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

