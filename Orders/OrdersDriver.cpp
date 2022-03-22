#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "Orders.h"

int Ordersmain() {
    /****************************** CREATING A GAME *******************************/
    // Create Map Loader
    MapLoader* loader = new MapLoader();

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player(); player2->setReinforcementPool(12); player2->setName("MJ");
    player_list.push_back(player1); player_list.push_back(player2);

    Map* mainmap = new Map(loader->load("../Orders/canada.map"));

    int playerIndex = 0;
    cout << mainmap->territoriesLength<<endl;
    for (int i = 0; i < mainmap->territoriesLength; i++) {
        Player *tempPlayer = player_list.at(playerIndex);

        mainmap->getTerritories()[i].setOwner(tempPlayer);
        Territory *tempTerr = new Territory(mainmap->getTerritories()[i]);
        tempPlayer->assignTerritory(tempTerr);
        playerIndex++;

        if (playerIndex >= player_list.size()) {
            playerIndex = 0;
        }
    }


    //cout << "****************************** Creating Orders, validate(), execute() and inserting them *******************************" <<endl;

    //	Deploy
    Deploy *deploy1 = new Deploy(player1);
    cout << "Adding to the OrdersList the Order: "<< *deploy1 << endl;
    cout << "Deploy validation: " << endl;
    deploy1->validate();
    cout << "----- Deploy execution ----- " << endl;
    deploy1->execute();
	player1->getOrder()->addOrder(deploy1);
	cout << *player1->getOrder() << "\n" << endl;
    cout << deploy1->stringToLog() << endl;

    Deploy *deploy2 = new Deploy(player1);
    deploy2->validate();
    deploy2->execute();
    player1->getOrder()->addOrder(deploy2);
    cout << *player1->getOrder() << "\n" << endl;
    cout << deploy2->stringToLog() << endl;

    //	Deploy
    cout << "----- Deploy for Player 2 ----- " << endl;
    Deploy *deploy3 = new Deploy(player2);
    deploy3->validate();
    deploy3->execute();
    player2->getOrder()->addOrder(deploy3);
    cout << *player2->getOrder() << "\n" << endl;
    cout << deploy3->stringToLog() << endl;

    Deploy *deploy4 = new Deploy(player2);
    deploy4->validate();
    deploy4->execute();
    player2->getOrder()->addOrder(deploy4);
    cout << *player2->getOrder() << "\n" << endl;
    cout << deploy4->stringToLog() << endl;

	// Advance
//	Advance *advance1 = new Advance(player1);
//	cout << "Adding to the OrdersList the Order: "<< *advance1 << endl;
//    cout << "Checking for validation: " << endl;
//    advance1->validate();
//    cout << "Checking for execution: " ; advance1->execute() ;
//	player1->getOrder()->addOrder(advance1);
//	cout << *player1->getOrder() << "\n" << endl;
//    cout << advance1->stringToLog() <<endl;

    // Airlift
//	Airlift *airlift1 = new Airlift(player1);
//	cout << "Adding to the OrdersList the Order: "<< *airlift1 << endl;
//    cout << "Checking for validation: "  << endl;
//    airlift1->validate();
//    cout << "Checking for execution: " ; airlift1->execute() ;
//	player1->getOrder()->addOrder(airlift1);
//	cout << *player1->getOrder() << "\n" << endl;
//    cout << airlift1->stringToLog() <<endl;

    // Bomb
//	Bomb *bomb1 = new Bomb(player1);
//	cout << "Adding to the OrdersList the Order: "<< *bomb1 << endl;
//    cout << "Checking for validation: " << endl;
//    bomb1->validate();
//    cout << "Checking for execution: " ;
//    bomb1->execute() ;
//	player1->getOrder()->addOrder(bomb1);
//	cout << *player1->getOrder() << "\n" << endl;
//    cout << bomb1->stringToLog();

	// Blockade
//    cout << "----- Blockade ----- " << endl;
//	Blockade *blockade1 = new Blockade(player1);
//    cout << "Validation of Blockade" << endl;
//    blockade1->validate();
//    cout << "Execution of Blockade" << endl;
//    blockade1->execute() ;
//    cout << blockade1->stringToLog() <<endl;


	// Negotiate
//    cout << "----- Negotiate ----- " << endl;
//	Negotiate *negotiate1 = new Negotiate(player1);
////	cout << "Adding to the OrdersList the Order: "<< *negotiate1 << endl;
//    cout << "Validation of Negotiate." << endl;
//    negotiate1->validate();
//    cout << "Execution of Negotiate." ;
//    negotiate1->execute() ;
//    cout<< negotiate1->stringToLog();
//	player1->getOrder()->addOrder(negotiate1);
//	cout << *player1->getOrder() << "\n" << endl;


/* Assignment 1
    cout << "****************************** move() *******************************" << endl;
	//Move()
	cout << "List before the move of Advance to the index 3" <<endl;
	cout << *player1->getOrder() << "\n" <<endl;
	player1->getOrder()->move(1,3);
	cout << "List after the move of Advance to the index 3" <<endl;
	cout << *player1->getOrder() << "\n" <<endl;
    player1->getOrder()->move(3,0);
    cout << "List after the move of Advance to index 0" <<endl;
    cout << *player1->getOrder()<< "\n" <<endl;
    player1->getOrder()->move(0,5);
    cout << "List after the move of Advance to the index 5" <<endl;
    cout << *player1->getOrder() << "\n" <<endl;

    cout << "****************************** remove() *******************************" <<endl;
	//Remove()
	cout << "List before the removal of order #2" <<endl;
	cout << *player1->getOrder() << "\n" <<endl;
    player1->getOrder()->remove(2);
	cout << "List after the removal of order #2" <<endl;
	cout << *player1->getOrder() << "\n" <<endl;

    cout << "****************************** Copy constructor and assignment operator *******************************"<<endl;
    //Create through copy constructor object
    cout << "Creating a deep copy of the OrderList through the Copy constructor" <<endl;
    OrdersList player1List2(*player1->getOrder());
    cout << endl;
    //Create through assignment operator object
    cout << "Creating a deep copy of the OrderList through the assignment operator" <<endl;
    OrdersList player1List3 = player1List2;
    cout << endl;

    cout <<"****************************** Verification of deep copies *******************************" <<endl;
	// Check the deep copies
	cout << "Original, now modified list" << endl;
	cout << *player1->getOrder() << "\n" <<endl;

	cout << "Copy through the copy constructor" << endl;
	cout << player1List2 << "\n" <<endl;

	cout << "Copy through the assignment operator" << endl;
	cout << player1List3 << "\n" <<endl;
*/

	return 0;
}

// Create Map
//    MapLoader* loader = new MapLoader();
//    Map* mainMap = new Map(loader->load("/Users/Amelia/Documents/COMP345-Exercises/Orders/canada.map"));
//    cout << *mainMap << endl;

// Create Deck
//    Deck *mainDeck = new Deck(10);
//    cout << mainDeck << endl;