#include "Player.h"

#include "../Map/Map.cpp"
#include "../Orders/Orders.cpp"
//#include  "C:/Users/Gabrielle/Documents/GitHub/COMP345-Assignment1/Cards/Cards.cpp"

Player::Player() {
    name = "";
    territories = list<Territory>;
    //hand = ;
    orders = new OrdersList();
}

Player::Player(string n, list<Territory> t, Cards h, OrdersList o) {
    name = n;
    territories = t;
    hand = h;
    orders = o;
}

list<Territory> Player::toDefend() {
   //list of orders or territories but the rubric says both i think territories
}

list<Territory> Player::toAttack() {
    //list of orders or territories but the rubric says both i think territories
}

int Player::issueOrder() {
    //create new order and add to OrderList
    return 0;
}

int Player::setName(string n) {
    name = n;
}
int Player::setTerritory(Territory t) {
    //deep copy the list
}
int Player::setHand(Cards h) {
    //copy constructor for cards ?
}
int Player::setOrder(OrderList o) {
    orders = o;
}
string Player::getName() {
    return name;
}
list<Territory> getTerritory() {
    return territories;
}
Cards getHand() {
    return hand;
}
OrdersList getOrder() {
    return orders;
}

std::ostream& operator<<(std::ostream& strm, const Player& p) {
    string t = "";

    for (Territory j : p.territories) {
        t += j.getName() + ", ";
    };

    return strm <<
        "PLAYER: " << p.name << 
        "\n    Territories: " << t <<
        "\n    Hand: " << p.hand; // Card should include its own print so hopefully this would be alright
}