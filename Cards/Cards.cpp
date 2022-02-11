#include "Cards.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
#include "../Orders/Orders.h"

/*********************************** CARD ***********************************/

Card::Card(){
    type = " ";
}
Card::Card(string theType){
//    // Convert the user input of Type to lowercase format
//    /*
//    for_each (theType.begin(), theType.end(), [](char & c)
//    { c = tolower(c);}
//    );
//    */
    type = theType;
}
Card::Card(Card &anotherCard){
    this->type = anotherCard.type;
}

string Card::getType() const {
    return type;
}

void Card::play(OrdersList &playerOrdersList) const{
    //Creat Order of the corresponding type
    if (this->type == "bomb"){
       cout << "Play Bomb card" << endl;
        Bomb* myBomb = new Bomb(true, "bomb"); // Create a Bomb object and play as an order
        playerOrdersList.addOrder(myBomb); // Place it in the OrdersList
    } else if (this->type == "reinforcement"){
       cout << "Play Reinforcement card" << endl;
        Reinforcement* myReinforcement = new Reinforcement(true, "reinforcement");
        playerOrdersList.addOrder(myReinforcement);
    } else if (this->type == "blockade"){
       cout << "Play Blockade card" << endl;
        Blockade* myBlockade = new Blockade(true, "blockade");
        playerOrdersList.addOrder(myBlockade);
    } else if (this->type == "airlift"){
       cout << "Play Airlift card" << endl;
       Airlift* myAirlift = new Airlift(true, "airlift");
       playerOrdersList.addOrder(myAirlift);
    } else if (this->type == "diplomacy"){
       cout << "Play Diplomacy card" << endl;
       Diplomacy* myDiplomacy = new Diplomacy(true, "diplomacy");
       playerOrdersList.addOrder(myDiplomacy);
    }

}

// Overload <<
ostream& operator<<(ostream& os, const Card& c)
{
    os << c.getType();
    return os;
}

Card& Card::operator=( const Card& toAssign){
    type = toAssign.type;
    return *this;
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
    this->numCardInDeck = anotherDeck.numCardInDeck;
    this->deck = anotherDeck.deck;
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
    Card * temp = deck.at(numRandom);

    //Display the type of card that is drawn
    cout << numRandom << "-" << *deck.at(numRandom) << " | ";

    // Remove the drawn card from Deck
    deck.erase(deck.begin()+numRandom);
    numCardInDeck--;
    return temp;
}

// Overload <<
ostream& operator<<(ostream& os, const Deck& d){
    os << "Number of card in deck: " << d.numCardInDeck << endl;
    for(int i = 0; i < d.numCardInDeck; i++){
        os << *(d.deck.at(i)) << " | ";
    }
    return os;
}

// Overload =
Deck& Deck::operator=(const Deck& toAssign){
    numCardInDeck = toAssign.numCardInDeck;
    deck = toAssign.deck;
    return *this;
}
/*********************************** HAND ***********************************/

Hand::Hand(){
    numCardInHand = 0;
    hand = vector<Card*>();
}
Hand::Hand(Hand &anotherHand){
    this->numCardInHand = anotherHand.numCardInHand;
    this->hand = anotherHand.hand;
}

Hand::~Hand(){
    for (int i=0;i<hand.size();i++){
        delete hand.at(i);
    }
}
// Overload <<
ostream& operator<<(ostream& os, const Hand& h)
{
//    os << "Number of cards on hand: " << h.numCardInHand << endl;
    for(int i = 0; i < h.numCardInHand; i++){
        os << i << "-" << *(h.hand.at(i)) << " | ";
    }
    return os;
}

Hand& Hand::operator=(const Hand& toAssign){
    numCardInHand = toAssign.numCardInHand;
    hand = toAssign.hand;
    return *this;
}
void Hand::drawCard(Deck& d){
    Card* drawnCard = d.draw();
    // Put the drawn card into Player hand
    hand.push_back(drawnCard);
    numCardInHand++;
}


void Hand::playCard(int i, Deck &d, OrdersList &l) {
    // Create Order and add Order to OrderList
    hand.at(i)->play(l);

    // Add the played Card back to deck
    Card* playedCard =hand.at(i);
    d.deck.push_back(playedCard);
    d.numCardInDeck++;

    // Remove card from Hand
    hand.erase(hand.begin()+i); // Delete the card object along with its pointer
    numCardInHand--;

}
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