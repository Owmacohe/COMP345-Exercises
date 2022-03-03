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
    
    //cout << "[Player default constructor]" << endl;
}

// Param constructor
Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o): name(n) {
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

// TO DO
//For now, all that these methods should do is to establish an arbitrary list of territories to be defended, and an arbitrary list of territories that are to be attacked. 
vector<Territory*> Player::toDefend() {
// TODO next assignment
//have to check if territories have surrounding enemies
//for now just returns vector list of the players territories

//check each continent for territories in our list, gives a list of territories that we own versus dont, order them by edges and number of armies on those edges

return territories;
}

// TO DO
vector<Territory*> Player::toAttack() {
// TODO next assignment
//have to check if territories have surrounding enemies
//for now returns vector list of territories that arent players
return territories;
}

// TO DO
void Player::issueOrder(string type = "default") {
    if (type == "deploy"){
        Deploy* o = new Deploy; //order type create
        orders->addOrder(o); //add order to list
    } 
    else if (type == "advance"){
        Advance* o = new Advance;
        orders->addOrder(o);
    } 
    else {
        cout << "Invalid order" << endl;
    }
}

int Player::getNumberOfArmies() {
    int sum = 0;
    for (Territory* i : territories) {
        sum = sum + i->getArmies();
    }
    return sum;
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

string Player::getName() { return name; }
vector<Territory*> Player::getTerritory() { return territories; }
Hand* Player::getHand() { return hand; }
OrdersList* Player::getOrder() { return orders; }
// End of Mutators and Accessors

// Assignment operator
Player& Player::operator = (const Player& p){
    this->name = p.name;
    for (Territory* i : p.territories) {
            this->territories.push_back(i);
    }
    this->hand = p.hand;
    this->orders = p.orders;
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
        "\n    Players orders, " << *p.orders <<endl;
}

