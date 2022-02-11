#include "Cards.h"
#include "../Orders/Orders.h"

int cardsMain() {
    // Number of card in Deck divisible by 5
    Deck mainDeck(10);
    Hand playerHand;
    OrdersList player1List;

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
    playerHand.playCard(4, mainDeck, player1List);
    playerHand.playCard(2, mainDeck, player1List);
    playerHand.playCard(2, mainDeck,player1List);
    playerHand.playCard(1, mainDeck,player1List);
    playerHand.playCard(0, mainDeck,player1List);
    cout << playerHand << endl;

    cout <<"\n---------------------------------------------------------------" << endl;
    cout << mainDeck << endl;

//  Assignemnt operator
    Deck assignDeck = mainDeck;
    cout << endl;
    cout << assignDeck;

    Hand assignHand = playerHand;
    cout << endl;
    cout << assignHand;
// Copy constructor
    Hand copyHand(playerHand);
    Deck copyDeck(mainDeck);

    cout << endl;
    cout << copyHand;
    cout << endl;
    cout << copyDeck;
    return 0;
}

//int main(){
//    cardsMain();
//    return 0;
//}