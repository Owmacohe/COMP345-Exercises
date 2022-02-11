#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include  "../Cards/Cards.h"

#include "Player.h"

Player::Player() {
    name = "empty player";
    territories = vector<Territory*>();
    hand = new Hand();
    orders = new OrdersList();
}

Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o) : name(n), territories(t), hand(h), orders(o) {
// Intentionally empty
}

Player::Player(const Player &p) {
    name = p.name;
    for (Territory* i : p.territories) {
        this->territories.push_back(new Territory(*i));
    } // Goes through copying vector of territory pointers, creates new pointers based on value and pushes to copied vector
    this->hand = new Hand(*(p.hand));
    this->orders = new OrdersList(*(p.orders));
}

Player::~Player() {
    for (Territory* i : territories) {
        delete i;
        i = NULL;
    }
    delete hand;
    hand = NULL;
    delete orders;
    orders = NULL;

    cout << name << " player destroyed" << endl;
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
    orders->addOrder(Order());
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

Player& Player::operator = (const Player& player){
    this->name = player.name;
    this->territories = player.territories;
    this->hand = player.hand;
    this->orders = player.orders;
    return *this;
}
std::ostream& operator<<(std::ostream &strm, const Player &p) {
    string t = "";
        for (Territory* i : p.territories) {
        t += i->getName() +", ";
    }

    return strm <<
        "PLAYER: " << p.name <<
        "\n    Territories: " << t <<
        "\n    Hand: " << p.hand <<
        "\n    Orders : " << p.orders;
}
