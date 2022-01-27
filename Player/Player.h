#pragma once

class Player {
public:
    string name; // Name of Player
    list<Territory> territories; // Player needs to own a collection of Territories ( list of territories or list of pointers to territories )
    Cards hand; // Player needs to have a hand ( a card hand object or pointer ? )
    list<Orders> orders; // Player needs to have a list of orders to be created and executed at their turn

    Player(); // Default constructor
    Player(string, list<Territory>, Card, Orders); // Parameterized constructor

    list<Territory> toDefend(); //  return list of territories that are to be defended
    list<Territory> toAttack();

    int issueOrder();

    //setter and getters
    int setName(string n);
    int setTerritory(Territory t); //add to list
    int setHand(Cards h);
    int setOrder(Orders o); //add to list

    string getName();
    list<Territory> getTerritory();
    Cards getHand();
    list<Orders> getOrder();
    //end setters and getters
    
};