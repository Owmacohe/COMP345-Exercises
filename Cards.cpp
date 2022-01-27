#include <iostream>
#include <string>
#include <vector>
#include "Cards.h"
#include <stdlib.h>     /* srand, rand */ // Generate random number library

// #include "OrderList.h" // Linked with the play() method

using namespace std;

/*********************************** CARD ***********************************/

Card::Card(){
    type = " ";
}
Card::Card(string theType){
    // Convert the user input of Type to lowercase format
    for_each (theType.begin(), theType.end(), [](char & c)
    { c = tolower(c);}
    );
    type = theType;
}
Card::Card(Card &anotherCard){
    type = anotherCard.type;
}

string Card::getType() const {
    return type;
}

// Whenever play() is called, it creates an object of the corresponding order from Order class
void Card::play() const{
    if (type == "bomb"){
       cout << "Play Bomb card" << endl;
       // Bomb myBomb; // Create a Bomb object and play as an order
    } else if (type == "reinforcement"){
       cout << "Play Reinforcement card" << endl;
       // Reinforcement myReinforce;
    } else if (type == "blockade"){
       cout << "Play Blockade card" << endl;
       // Blockade myBlockade;
    } else if (type == "airlift"){
       cout << "Play Airlift card" << endl;
       // Airlift myAirlift;
    } else if (type == "diplomacy"){
       cout << "Play Diplomacy card" << endl;
       // Diplomacy myDiplomacy;
    }
    // the Play method is not complete
    // missing the remove Hand
}

// Overload <<
ostream& operator<<(ostream& os, const Card& c)
{
    os << c.getType();
    return os;

}
/*********************************** DECK ***********************************/

Deck::Deck(){
    numCardInDeck = 0;
    deck = vector<Card*>();
}
Deck::Deck(int numCard) {
    numCardInDeck = numCard;
    if (numCardInDeck % 5 != 0) {
        cout << "The number of cards you entered is not divisible by 5. "
                "A default deck of 50 cards will be used instead." << endl;
        numCardInDeck = 50;
    }
        // Create the Deck of Card
        for (int i = 0; i < numCardInDeck; i++) {
            if (i % 5 == 0) {
                deck.push_back(new Card("bomb"));
            } else if (i % 5 == 1) {
                deck.push_back(new Card("reinforcement"));
            } else if (i % 5 == 2) {
                deck.push_back(new Card("blockade"));
            } else if (i % 5 == 3) {
                deck.push_back(new Card("airlift"));
            } else {
                deck.push_back(new Card("diplomacy"));
            }
        }

//        // Display Deck
//        for (int i=0; i<numCardInDeck; i++){
//            cout << *deck.at(i) << endl;
//        }

//    cout << "The Deck is created with " << numCardInDeck << " and each type has "
//            << numCardInDeck/5 << endl;
    }

Deck::Deck(Deck &anotherDeck){
    numCardInDeck = anotherDeck.numCardInDeck;
    deck = anotherDeck.deck;

//    // Display Deck
//    for (int i=0; i<numCardInDeck; i++){
//        cout << *deck.at(i) << endl;
//    }

     cout << "The Deck is created with " << numCardInDeck << " and each type has "
            << numCardInDeck/5 << "card" << endl;
}

void Deck::draw(Hand &h){
    // Generate a distinct random number so that no card will be repeated
    int x = genDistinctNum();

//    Display the type of card that is generated
    cout << x << " ";
    cout << *deck.at(x) << endl;
    h.hand.push_back(deck.at(x));
}

int Deck::genDistinctNum(){
    srand (time(NULL)); // initialized the random number generator
    int numRandom;
    static vector<int> trace = vector<int>(); // Exist only 1 trace vector->static (avoid creating new vector everytime function called)

    // Generate a Distinct random number from 0 to numCardInDeck
    bool generated = false;
    while (!generated){
        numRandom = rand() % numCardInDeck;

        if (trace.size() == numCardInDeck){
            trace.clear();
        }
        if (trace.size() != 0 /* memory reference error*/ && *find(trace.begin(), trace.end(),numRandom) == numRandom){
            continue;
        } else{
            generated = true;
            trace.push_back(numRandom);
        }
    }

//    Display the random number generate
//    cout << numRandom << " ";

    return numRandom;
}

// Overload <<
ostream& operator<<(ostream& os, const Deck& d)
{
    for(int i = 0; i < d.numCardInDeck; i++){
        os << *(d.deck.at(i));
    }
    return os;
}

/*********************************** HAND ***********************************/

Hand::Hand(){
    numCardInHand = 0;
    hand = vector<Card*>();
}
Hand::Hand(Hand &anotherHand){
    numCardInHand = anotherHand.numCardInHand;
    hand = anotherHand.hand;
}


// Overload <<
ostream& operator<<(ostream& os, const Hand& h)
{
    for(int i = 0; i < h.numCardInHand; i++){
        os << *(h.hand.at(i));
    }
    return os;
}