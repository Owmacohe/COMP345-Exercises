#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "Orders.h"

int Ordersmain() {
    /****************************** CREATING A GAME *******************************/

    // Create Map Loader
//    MapLoader* loader = new MapLoader();
//    Map* mainmap = new Map(loader->load("../Orders/canada.map"));

    MapLoader* loader;
    Map* mainmap = new Map(loader->load("../Orders/canada.map"));


    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player(); player2->setReinforcementPool(12); player2->setName("MJ");
    player_list.push_back(player1); player_list.push_back(player2);

    // Create & Set up Game Engine
    GameEngine* mainGE = new GameEngine();
    mainGE->setMap(*mainmap);
    mainGE->setplayer_list(player_list);
    mainGE->setDeck(*new Deck(20));
    Order::game = mainGE;

    cout << "Before Assigning" <<endl;
    cout << "mainmap directly "<< mainmap->getTerritories()[0] << endl;
    cout << " From Order " << Order::game->getMap()->getTerritories()[0] << endl;
    cout << "From mainGE "<< mainGE->getMap()->getTerritories()[0] << endl;

    // Assign Territories to Players
    int playerIndex = 0;
    for (int i = 0; i < mainmap->territoriesLength; i++) {

        mainmap->getTerritories()[i].setOwner(player_list.at(playerIndex));
        player_list.at(playerIndex)->assignTerritory(new Territory(mainmap->getTerritories()[i]));

        playerIndex++;

        if (playerIndex >= player_list.size()) {
            playerIndex = 0;
        }
    }

    cout << "After Assigning" <<endl;
    cout << "mainmap directly "<< mainmap->getTerritories()[0] << endl;
    cout << " From Order " << Order::game->getMap()->getTerritories()[0] << endl;
    cout << "From mainGE "<< mainGE->getMap()->getTerritories()[0] << endl;

    // Display Player list of Territories
    cout << endl;
    for (int i=0; i<player_list.size();i++){
        cout << player_list.at(i)->getName() << "'s territories: ";
        for(auto teri : player_list.at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }

    //	Testing Orders


    // Deploy
    cout << "\n--------------- DEPLOY ---------------\n" << endl;
    Deploy *deploy1 = new Deploy(player1);
    cout << "Order: "<< *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();
    cout << deploy1->stringToLog() << endl;

//    vector<Territory*> teri = player1->toDefend(mainmap);
//    cout << teri.empty() << endl;
//    for (Territory* t : teri){
//        cout <<*t<<endl;
//    }

    Deploy *deploy2 = new Deploy(player1);
    cout << "Order: "<< *deploy2 << endl;
    deploy2->validate();
    deploy2->execute();
    cout << deploy2->stringToLog() << endl;

//    teri = player1->toDefend(mainmap);
//    for (Territory* t : teri){
//        cout <<*t<<endl;
//    }

    Deploy *deploy3 = new Deploy(player2);
    cout << "Order: "<< *deploy3 << endl;
    deploy3->validate();
    deploy3->execute();
    cout << deploy3->stringToLog() << endl;

//    teri = player2->toDefend(mainmap);
//    for (Territory* t : teri){
//        cout <<*t<<endl;
//    }

    Deploy *deploy4 = new Deploy(player2);
    cout << "Order: "<< *deploy4 << endl;
    deploy4->validate();
    deploy4->execute();
    cout << deploy4->stringToLog() << endl;

//    teri = player2->toDefend(mainmap);
//    for (Territory* t : teri){
//        cout <<*t<<endl;
//    }



//   cout << "TESTING CONNECTED TERRITORIES" <<endl;
//    vector<Territory*> connected_terries = mainmap->getConnectedTerritories(player1->getTerritoryList().at(0)->getName());
//    for (Territory* t : connected_terries){
//        cout <<*t<<endl;
//    }


    cout << "TESTING TO ATTACK" <<endl;
    vector<Territory*> terri = player1->toAttack(mainmap);
    cout << "To Attack is Empty:"<< terri.empty() <<endl;
    for (Territory* t : terri){
        cout <<*t<<endl;
    }

	// Advance
//	Advance *advance1 = new Advance(player1);
//	cout << "Adding to the OrdersList the Order: "<< *advance1 << endl;
//    cout << "Checking for validation: " << endl;
//    advance1->validate();
//    cout << "Checking for execution: " ; advance1->execute() ;
//	player1->getOrder()->addOrder(advance1);
//	cout << *player1->getOrder() << "\n" << endl;
//    cout << advance1->stringToLog() <<endl;

/*
    // Airlift
    cout << "\n--------------- AIRLIFT ---------------\n" << endl;
	Airlift *airlift1 = new Airlift(player1);
    cout << "Order: "<< *airlift1 << endl;
    airlift1->validate();
    airlift1->execute() ;
    cout << airlift1->stringToLog() <<endl;

    Airlift *airlift2 = new Airlift(player1);
    cout << "Order: "<< *airlift2 << endl;
    airlift2->validate();
    airlift2->execute() ;
    cout << airlift2->stringToLog() <<endl;

    Airlift *airlift3 = new Airlift(player2);
    cout << "Order: "<< *airlift3 << endl;
    airlift3->validate();
    airlift3->execute() ;
    cout << airlift3->stringToLog() <<endl;

    Airlift *airlift4 = new Airlift(player2);
    cout << "Order: "<< *airlift4 << endl;
    airlift4->validate();
    airlift4->execute() ;
    cout << airlift4->stringToLog() <<endl;
*/

//    cout << "--------------- BOMB ---------------" << endl;
//    // Bomb
//	Bomb *bomb1 = new Bomb(player1);
//    cout << "Order:"  << *bomb1 << endl;
//    bomb1->validate();
//    bomb1->execute() ;
//    cout << bomb1->stringToLog();

/*
	// Blockade
    cout << "\n--------------- BLOCKADE ---------------\n" << endl;
	Blockade *blockade1 = new Blockade(player1);
    cout << "Order: "<< *blockade1 << endl;
    blockade1->validate();
    blockade1->execute() ;
    cout << blockade1->stringToLog() <<endl;

    Blockade *blockade2 = new Blockade(player1);
    cout << "Order: "<< *blockade2 << endl;
    blockade2->validate();
    blockade2->execute() ;
    cout << blockade2->stringToLog() <<endl;

    Blockade *blockade3 = new Blockade(player2);
    cout << "Order: "<< *blockade3 << endl;
    blockade3->validate();
    blockade3->execute() ;
    cout << blockade3->stringToLog() <<endl;

    Blockade *blockade4 = new Blockade(player2);
    cout << "Order: "<< *blockade4 << endl;
    blockade4->validate();
    blockade4->execute() ;
    cout << blockade4->stringToLog() <<endl;
*/

    // Negotiate
//    cout << "--------------- NEGOTIATE ---------------" << endl;
//	Negotiate *negotiate1 = new Negotiate(player1);
//	cout << "Order: "<< *negotiate1 << endl;
//    negotiate1->validate();
//    negotiate1->execute() ;
//    cout<< negotiate1->stringToLog();

//    Negotiate *negotiate2 = new Negotiate(player1);
//    cout << "Order: "<< *negotiate2<< endl;
//    negotiate2->validate();
//    negotiate2->execute() ;
//    cout<< negotiate2->stringToLog();
//
//    Negotiate *negotiate3 = new Negotiate(player2);
//    cout << "Order: "<< *negotiate3 << endl;
//    negotiate3->validate();
//    negotiate3->execute() ;
//    cout<< negotiate3->stringToLog();

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