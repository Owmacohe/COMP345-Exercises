#include <iostream>
<<<<<<< HEAD
//#include "Cards.cpp"
#include "Cards.h"

using namespace std;

int mainCard(){

// Number of card in Deck divisible by 5
Deck mainDeck(10);
Hand playerHand;

cout << "\n---------------------------Display Card in Deck---------------------------" << endl;
cout << mainDeck << endl;

cout <<"\n---------------------------Display Drawn Card---------------------------" << endl;
    playerHand.drawCard(mainDeck);
    playerHand.drawCard(mainDeck);
    playerHand.drawCard(mainDeck);
    playerHand.drawCard(mainDeck);
    playerHand.drawCard(mainDeck);

cout <<"\n\n---------------------------Display Deck after Drawing---------------------------" << endl;
cout << mainDeck << endl;

cout <<"\n---------------------------Display Card in Hand---------------------------" << endl;
    cout << playerHand << endl;

cout <<"\n---------------------------Play Card---------------------------" << endl;
//To play a card, provide the index associated
playerHand.playCard(4, mainDeck);
playerHand.playCard(2, mainDeck);
cout << playerHand << endl;

cout <<"\n---------------------------------------------------------------" << endl;
cout << mainDeck << endl;
return 0;
}

int main(){
    mainCard();
=======
#include <vector>
#include <string>
#include <cstdlib> /* srand rand */ // Generate random number library
#include "Cards.cpp"
using namespace std;

int cardsMain(){
    // Number of card in Deck divisible by 5
    Deck mainDeck(10);
    Hand playerHand;

    cout << "---------------------------Display Card in Deck---------------------------" << endl;
    //for (int i=0; i<mainDeck.numCardInDeck; i++) {
    //    cout << i << " " << *mainDeck.deck.at(i) << endl;
    //}
    cout << mainDeck << endl;
    // Draw 5 cards
    cout <<"\n---------------------------Display Drawn Card---------------------------" << endl;
        playerHand.drawCard(mainDeck);
        playerHand.drawCard(mainDeck);
        playerHand.drawCard(mainDeck);
        playerHand.drawCard(mainDeck);
        playerHand.drawCard(mainDeck);

    cout <<"\n---------------------------Display Card in Hand---------------------------" << endl;
        cout << playerHand << endl;

    cout <<"\n---------------------------Display Deck after Drawing---------------------------" << endl;
        cout << mainDeck << endl;

    cout <<"\n---------------------------Play Card---------------------------" << endl;
    for (int i=0; i<playerHand.hand.size();i++) {
        playerHand.hand.at(i)->play();
    }

    return 0;
>>>>>>> main
}
