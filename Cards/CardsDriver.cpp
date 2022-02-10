#include "Cards.h"
#include "../Orders/Orders.h"

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
