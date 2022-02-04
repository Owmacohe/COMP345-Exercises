#include "Player.h"

#include "../Map/Map.cpp"
#include "../Orders/Orders.cpp"
#include  "../Cards.cpp"

Player::Player() {
    name = "";
    territories = vector<Territory*>();
    hand = new Hand();
    orders = new OrdersList();
}

Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o) {
    name = n;
    territories = t;
    hand = h;
    orders = o;
}

Player::Player(Player& p) {
    //copy
}

Player::~Player() {
    cout << name << " player destroyed" << endl;
}

vector<Territory*> Player::toDefend() {
   //list of orders or territories but the rubric says both i think territories
   Map* m = new Map();
   m = NULL;
   delete m;
}

vector<Territory*> Player::toAttack() {
    //list of orders or territories but the rubric says both i think territories
}

int Player::issueOrder() {
    //create new order and add to OrderList
    return 0;
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

// NEED TO ADD : std::ostream& operator<<(std::ostream& strm, const Player& p)
