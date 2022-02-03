#include <iostream>
#include <string>
#include <vector>
#include "Cards.h"
#include <cstdlib> /* srand rand */ // Generate random number library

// #include "OrderList.h" // Link the play() method

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
Card* Card::play() const{
    if (type == "bomb"){
       cout << "Play Bomb card" << endl;
       // Bomb* myBomb = new Bomb(); // Create a Bomb object and play as an order
       // oderList.push_back(*myBomb)
    } else if (type == "reinforcement"){
       cout << "Play Reinforcement card" << endl;
       // Reinforcement* myReinforce = new Reinforcement();
       // orderList.push_back(*myReinforce);
    } else if (type == "blockade"){
       cout << "Play Blockade card" << endl;
       // Blockade* myBlockade = new Blockade();
       // orderList.push_back(*myBlockade);
    } else if (type == "airlift"){
       cout << "Play Airlift card" << endl;
       // Airlift* myAirlift = new Airlift();
       // orderList.push_back(*myAirlift);
    } else if (type == "diplomacy"){
       cout << "Play Diplomacy card" << endl;
       // Diplomacy* myDiplomacy = new Diplomacy();
       // orderList.push_back(*myDiplomacy);
    }
    // play is not completed

}

// Overload <<
ostream& operator<<(ostream& os, const Card& c)
{
    os << c.getType();
    return os;

}
/*********************************** DECK ***********************************/

Deck::Deck(){
    srand (time(NULL));
    numCardInDeck = 0;
    deck = vector<Card*>();
}
Deck::Deck(int numCard) {
    srand(time(NULL));
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
}

Deck::Deck(Deck &anotherDeck) {
    srand(time(NULL));
    numCardInDeck = anotherDeck.numCardInDeck;
    deck = anotherDeck.deck;
}
Deck::~Deck(){
    for (int i=0; i<deck.size();i++){
        delete deck.at(i);
    }
}

Card* Deck::draw(){

    // Generate a random number
    int numRandom = rand() %numCardInDeck;

    // Store return card in a temp var -> So as to delete its trace in deck
    // Copy constructor
    Card * temp = new Card(*deck.at(numRandom));

    //    Display the type of card that is drawn
    cout << numRandom << " ";
    cout << *deck.at(numRandom) << endl;

    // Remove the drawn card from Deck
    free(deck.at(numRandom)) ;  // prevent memory leak
    deck.erase(deck.begin()+numRandom);
    numCardInDeck--;

    return temp;
}

// Overload <<
ostream& operator<<(ostream& os, const Deck& d)
{
    os << "Number of card in deck: " << d.numCardInDeck << endl;
    for(int i = 0; i < d.numCardInDeck; i++){
        os << *(d.deck.at(i)) << " | ";
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

Hand::~Hand(){
    for (int i=0;i<hand.size();i++){
        delete hand.at(i);
    }
}
// Overload <<
ostream& operator<<(ostream& os, const Hand& h)
{
    os << "Number of cards on hand: " << h.numCardInHand << endl;
    for(int i = 0; i < h.numCardInHand; i++){
        os << *(h.hand.at(i)) << " | ";
    }
    return os;
}

void Hand::drawCard(Deck& d){
    Card* drawnCard = d.draw();
    // Put the drawn card into Player hand
    hand.push_back(drawnCard);
    numCardInHand++;
}

//void Hand::playCard(Card &c) {
//    Card* playedCard = c.play();
//}
/*********************************** DRAFT ***********************************/
// DRAW CARD BY INDEX
//int Deck::genDistinctNum() {
//    srand(time(NULL)); // initialized the random number generator
//    int numRandom;
//    static vector<int> trace = vector<int>(); // Exist only 1 trace vector->static (avoid creating new vector everytime function called)
//
//    // Generate a Distinct random number from 0 to numCardInDeck
//    bool generated = false;
//    while (!generated) {
//        numRandom = rand() % numCardInDeck;
//
//        if (trace.size() == numCardInDeck) {
//            trace.clear();
//        }
//        if (trace.size() != 0 /* memory reference error*/ &&
//            *find(trace.begin(), trace.end(), numRandom) == numRandom) {
//            continue;
//        } else {
//            generated = true;
//            trace.push_back(numRandom);
//        }
//        return numRandom;
//    }
//}