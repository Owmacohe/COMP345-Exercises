#pragma once
#include <vector>
#include "Orders.h"
//using namespace std;

class Hand;
class Card{
public:
    Card(); // Default Constructor - initialize card type to null
    Card(string type);  // Parameterized Constructor - initialize type of card
    Card(Card &anotherCard);  // Copy Constructor

    string getType() const;
    void play(/*OrdersList &ordersList*/) const;
    friend ostream& operator<<(ostream& os, const Card& card); // Over load << operator to print out value in Hand

private:
    string type;
};

class Deck{
public:
    // Constructor
    Deck();
    Deck(int numCard);
    Deck(Deck &anotherDeck);
    ~Deck();
    friend ostream& operator<<(ostream& os, const Deck& deck); //  << Overloading operator to print out value in Deck
    Deck& operator = (const Deck& toAssign); // assignment Overloading
    Card* draw();

    vector <Card*> deck; // Deck is a vector of Card object
    int numCardInDeck;

//    int genDistinctNum();
};

class Hand{
public:
    // Constructor
    Hand();
    Hand(Hand &anotherHand);
    ~Hand();
    friend ostream& operator<<(ostream& os, const Hand& hand);  // << Overloading stream insertion outputs hand vector of Card pointers
    Hand& operator =(const Hand& toAssign);    // = assignment operator Overloading

    void drawCard(Deck &d);
    void playCard(int i, Deck &d);

    vector <Card*> hand;
    int numCardInHand;
};









