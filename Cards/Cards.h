#pragma once
#include <vector>
#include <string>
using namespace std;

class Card{
public:
    Card(); // Default Constructor - initialize card type to null
    Card(string type);  // Parameterized Constructor - initialize type of card
    Card(Card &anotherCard);  // Copy Constructor

    string getType() const;
    Card* play() const;
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
    friend ostream& operator<<(ostream& os, const Deck& deck); // Overload the << operator to print out value in Deck
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
    friend ostream& operator<<(ostream& os, const Hand& hand);
    void drawCard(Deck &d);
    void playCard(Card &c);

    vector <Card*> hand;
    int numCardInHand;
};









