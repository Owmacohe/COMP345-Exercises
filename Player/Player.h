#pragma once

class Player {
public:
    string name; // Name of Player
    list<Territory> territories; // MAYBE VECTOR INSTEAD OF LIST Player needs to own a collection of Territories ( list of territories or list of pointers to territories ) POINTER
    Cards hand; // Player needs to have a hand ( a card hand object or pointer ? ) POINTER
    OrdersList orders; // Player needs to have a list of orders to be created and executed at their turn POINTER

    Player(); // Default constructor
    Player(string, list<Territory>, Cards, OrdersList); // Parameterized constructor

    list<Territory> toDefend();
    list<Territory> toAttack();

    int issueOrder();

    //setter and getters
    int setName(string n);
    int setTerritory(Territory t); //add to list
    int setHand(Cards h);
    int setOrder(OrdersList o);

    string getName();
    list<Territory> getTerritory();
    Cards getHand();
    OrdersList getOrder();
    //end setters and getters
    
};