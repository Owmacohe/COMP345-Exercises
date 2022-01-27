#include "Player.h"

Player::Player() {
    name = "";
    //territories = ;
    //hand = ;
    //orders = ;
}

Player::Player(string n, list<Territory> t, Card h, list<Order> o) {
    name = n;
    territories = t;
    hand = h;
    orders = o;
}

list<Territory> Player::toDefend() {
   //players territories
}

list<Territory> Player::toAttack() {
    //get all territories on map and return ones not players
}

int Player::issueOrder() {
    return 0;
}

int Player::setName(string n) {
    name = n;
}
int Player::setTerritory(Territory t) {
    territories = t; //deep copy the list
}
int Player::setHand(Cards h) {
    //copy constructor for cards ?
}
int Player::setOrder(Orders o) {
    orders = o; //deep copy the list
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
list<Order> getOrder() {
    return orders;
}

std::ostream& operator<<(std::ostream& strm, const Player& p) {
    string t = "";
    string o = "";

    for (Territory j : p.territories) {
        t += j.name + ", ";
    };

    for (Orders i : p.orders) {
        o += i.name + ", ";
    };

    return strm <<
        "PLAYER: " << p.name << 
        "\n    Territories: " << t <<
        "\n    Hand: " << p.hand << // Card should include its own print so hopefully this would be alright
        "\n    Orders: " << o;
}