#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include "Player.h"

Player::Player() {
    name = "empty player";
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    cout << "[Player default constructor]" << endl;
}

Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o): name(n) {
    territories = vector<Territory*>();
    for (Territory* i : t) {
        territories.push_back(new Territory(*i));
    }
    
    hand = new Hand(*h);
    orders = new OrdersList(*o);
    cout << "[Player param constructor]" << endl;
}

Player::Player(const Player &p) {
    name = p.name;

    territories = vector<Territory*>();
    for (Territory* i : p.territories) {
        territories.push_back(new Territory(*i));
    } // Goes through copying vector of territory pointers, creates new pointers based on value and pushes to copied vector

    hand = new Hand(*(p.hand));
    orders = new OrdersList(*(p.orders));
    cout << "[Player copy constructor]" << endl;
}

Player::~Player() {
    for (Territory* i : territories) {
        delete i;
        i = NULL;
        cout << "[Player territory destructor]" << endl;
    }

    delete hand;
    hand = NULL;
    delete orders;
    orders = NULL;

    cout << "[Player destructor]" << endl;
}

//For now, all that these methods should do is to establish an arbitrary list of territories to be defended, and an arbitrary list of territories that are to be attacked. 
vector<Territory*> Player::toDefend() {
// TODO next assignment
//have to check if territories have surrounding enemies
//for now just returns vector list of the players territories
return territories;
}

vector<Territory*> Player::toAttack() {
// TODO next assignment
//have to check if territories have surrounding enemies
//for now returns vector list of territories that arent players
return territories;
}

void Player::issueOrder() {
    Order* o = new Order;
    orders->addOrder(o);
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

Player& Player::operator = (const Player& p){
    this->name = p.name;
    for (Territory* i : p.territories) {
            this->territories.push_back(i);
    }
    this->hand = p.hand;
    this->orders = p.orders;
    return *this;
}

std::ostream& operator<<(std::ostream &strm, const Player &p) {
    string t = "";
    for (Territory* i : p.territories) {
        t += (*i).getName() +", ";
    }

    return strm <<
        "PLAYER: " << p.name <<
        "\n    Territories: " << t <<
        "\n    Players hand, " << *p.hand <<
        "\n    Players orders, " << *p.orders;
}
