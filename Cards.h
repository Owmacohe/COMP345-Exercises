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
    void play() const;
    friend ostream& operator<<(ostream& os, const Card& card); // Over load << operator to print out value in Hand

private:
    string type;
};

class Hand; // forward declaration cause draw() method need to call Hand

class Deck{
public:
    // Constructor
    Deck();
    Deck(int numCard);
    Deck(Deck &anotherDeck);
    void draw(Hand &h);
    int genDistinctNum();
    friend ostream& operator<<(ostream& os, const Deck& deck); // Overload the << operator to print out value in Deck
    vector <Card*> deck; // Deck is a vector of Card object
    int numCardInDeck;

};

class Hand{
public:
    // Constructor
    Hand();
    Hand(Hand &anotherHand);
    friend ostream& operator<<(ostream& os, const Hand& hand);
    friend void Deck::draw(Hand &h); // allow the call of (private) hand in Deck
    vector <Card*> hand;
    int numCardInHand;
};





