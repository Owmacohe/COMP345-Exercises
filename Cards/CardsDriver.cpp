#include <iostream>
#include "Cards.h"
using namespace std;

int main(){

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

}
