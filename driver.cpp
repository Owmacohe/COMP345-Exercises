#include <iostream>
using namespace std;

#include "Cards/Cards.h"
//#include "Map/Map.h"
#include "Orders/Orders.h"
//#include "Player/Player.h"

<<<<<<< Updated upstream
//#include "Cards/CardsDriver.cpp"
#include "GameEngine/GameEngineDriver.cpp"
#include "Map/MapDriver.cpp"
//#include "Orders/Orders.cpp"
//#include "Player/Player.cpp"

int main() {
    cout << endl;
=======
//#include "Map/MapDriver.cpp"
//#include "GameEngine/GameEngineDriver.cpp"
//#include "Cards/CardsDriver.cpp"
//#include "Player/PlayerDriver.cpp"
//#include "Orders/OrdersDriver.cpp"

int main() {
/***************************** Order *****************************/
    OrdersList player1List;
    cout << player1List;
>>>>>>> Stashed changes

    //Deploy
    Deploy *deploy1 = new Deploy(true, "deploy");
    cout << "Adding to the OrdersList, Order: "<< *deploy1 << endl;
    player1List.addOrder(deploy1);
    cout << player1List << endl;

    // Advance
    Advance *advance1 = new Advance( true, "advance");
    cout << "Adding to the OrdersList, Order: "<< *advance1 << endl;
    player1List.addOrder(advance1);
    cout << player1List;

    // Bomb
    Bomb *bomb1 = new Bomb(true, "bomb");
    cout << "Adding to the OrdersList, Order: "<< *bomb1 << endl;
    player1List.addOrder(bomb1);
    cout << player1List;

    // Blockade
    Blockade *blockade1 = new Blockade(true, "blockade");
    cout << "Adding to the OrdersList, Order: "<< *blockade1 << endl;
    player1List.addOrder(blockade1);
    cout << player1List;

    // Airlift
    Airlift *airlift1 = new Airlift(true, "airlift");
    cout << "Adding to the OrdersList, Order: "<< *airlift1 << endl;
    player1List.addOrder(airlift1);
    cout << player1List;

    //Negotiate
    Negotiate *negotiate1 = new Negotiate(true, "negotiate");
    cout << "Adding to the OrdersList, Order: "<< *negotiate1 << endl;
    player1List.addOrder(negotiate1);
    cout << player1List;

/***************************** Deck *****************************/
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
//    To play a card, provide the index associated
    playerHand.playCard(3, mainDeck, player1List);
    playerHand.playCard(1, mainDeck, player1List);
    playerHand.playCard(2, mainDeck, player1List);
    playerHand.playCard(0, mainDeck, player1List);
    playerHand.playCard(0, mainDeck, player1List);

    cout << playerHand << endl;

    cout <<"\n---------------------------------------------------------------" << endl;
    cout << mainDeck << endl;

    cout << player1List;
    return 0;
}