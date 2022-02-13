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
//    playerHand.playCard(1, mainDeck,player1List);
//    playerHand.playCard(0, mainDeck,player1List);
    cout << playerHand << endl;

    cout <<"\n---------------------------------------------------------------" << endl;
    cout << mainDeck << "\n" << endl;

//  Assignemnt operator
    Deck assignDeck = mainDeck;
    playerHand.drawCard(assignDeck);
    playerHand.drawCard(assignDeck);
    cout << "\n" << endl;
    cout << assignDeck << endl;

    Hand assignHand = playerHand;
    cout << endl;
    cout << assignHand << "\n" << endl;
    assignHand.playCard(0,assignDeck,player1List);
    assignHand.playCard(2,assignDeck,player1List);
    assignHand.playCard(1,assignDeck,player1List);
    assignHand.playCard(0,assignDeck,player1List);
    cout << endl;
    cout << assignHand << "\n" << endl;

// Copy constructor
    Hand copyHand(assignHand);
    Deck copyDeck(mainDeck);

    cout << endl;
    cout << copyHand << "\n";
    cout << copyDeck << "\n" << endl;
    return 0;
}

int main(){
    cardsMain();
    return 0;
}