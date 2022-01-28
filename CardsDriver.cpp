#include <iostream>
#include "Cards.h"
using namespace std;

int main(){
// Number of card in Deck divisible by 5
Deck mainDeck(10);
cout << "------------- Display the Deck of Card Divisible by 5 -------------" << endl;
for (int i=0; i<mainDeck.numCardInDeck; i++) {
    cout << i << " " << *mainDeck.deck.at(i) << endl;
}
cout << "-------------------------------------------------------------------" << endl;

// Number of card in Deck not divisible by 5
Deck sideDeck(7);
cout << "------------- Display the Deck of Card not Divisible by 5 -------------" << endl;
for (int i=0; i<sideDeck.numCardInDeck; i++) {
    cout << *sideDeck.deck.at(i) << endl;
}


Hand playerHand;

// Draw 5 card
cout <<"\n------------- Display Card in Hand -------------" << endl;
    mainDeck.draw(playerHand);
    mainDeck.draw(playerHand);
    mainDeck.draw(playerHand);
    mainDeck.draw(playerHand);
    mainDeck.draw(playerHand);
cout <<"\n------------------------------------------------" << endl;

for (int i=0; i<playerHand.hand.size();i++) {
    playerHand.hand.at(i)->play();
}
cout << endl;

}
