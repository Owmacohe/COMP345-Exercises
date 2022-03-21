#include "Orders.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "GameEngine/GameEngine.h"
#include "../Map/Map.h"

int Ordermain() {

    Player* player1 = new Player();
    player1->setReinforcementPool(10);
    player1->setName("Audrey");
    Player* player2 = new Player();
    player2->setReinforcementPool(12);
    player2->setName("MJ");

//    Territory* vietnam = new Territory("Vietnam", "Asia", player1, 2);
//    Territory* canada = new Territory("Canada", "North America", player2, 4);

//    cout << "Player 1" << " - name: " << player1->getName() << endl;
//    cout << "reinforcement pool: " << player1->getReinforcePool() << endl;

//    cout << "Player 2" << " - name: " << player2->getName() << endl;
//    cout << "reinforcement pool: " << player2->getReinforcePool() << endl;

//    cout << "Territories:" << endl;
//    cout << vietnam->getName() << " - armies: " << vietnam->getArmies() << endl;
//    cout << canada->getName() << " - armies: " << canada->getArmies() << endl;

//		Create OrderList object
//    OrdersList player1List;
//    Player* player1 = new Player();
//    player1->setReinforcementPool(10);
//    player1->setName("Audrey");
//    Player* player2 = new Player();
//    player2->setReinforcementPool(12);
//    player2->setName("MJ");
//
//    Territory* vietnam = new Territory("Vietnam", "Asia", player1, 2);
//    Territory* canada = new Territory("Canada", "North America", player2, 4);
//
//    cout << "Player 1" << " - name: " << player1->getName() << endl;
//    cout << "reinforcement pool: " << player1->getReinforcePool() << endl;
//
//    cout << "Player 2" << " - name: " << player2->getName() << endl;
//    cout << "reinforcement pool: " << player2->getReinforcePool() << endl;
//
//    cout << "Territories:" << endl;
//    cout << vietnam->getName() << " - armies: " << vietnam->getArmies() << endl;
//    cout << canada->getName() << " - armies: " << canada->getArmies() << endl;
//
//    cout << "****************************** Creating Orders, validate(), execute() and inserting them *******************************" <<endl;
//	Deploy
	Deploy *deploy1 = new Deploy(player1);
	cout << "Adding to the OrdersList the Order: "<< *deploy1 << endl;
//    cout << "Deploy validation: " << endl;
//    deploy1->validate();
//    cout << "----- Deploy execution ----- " << endl;
//    deploy1->execute();

//    cout << player1->getName() << " reinforcement pool: " << player1->getReinforcePool() << " armies" << endl; //Check if player1 reinforcement pool decreases
//    cout << vietnam->getName() << " armies: " << vietnam->getArmies() << " armies" << endl; //Check if numArmies in territory increases
	player1->getOrder()->addOrder(deploy1);
	cout << *player1->getOrder() << "\n" << endl;

     /****************************** CREATING A GAME *******************************/
//
//    GameEngine* game;
//
//     //Create Map
//        MapLoader loader;
//        Map m = Map();
//        m = loader.load("canada.map");
//
//        // Create Players
//        vector<Player*> player_list;
//        Player* player1 = new Player();
//        player1->setReinforcementPool(10);
//        player1->setName("Audrey");
//
//        Player* player2 = new Player();
//        player2->setReinforcementPool(12);
//        player2->setName("MJ");
//
//        player_list.push_back(player1);
//        player_list.push_back(player2);
//
//        game->setplayer_list(player_list);
//
//        // Assign Territories to Player 1
//        game->getMap()->getTerritories()[0].setOwner(player1); // New Brunswick -- Not adjacent to any of the others
//        Territory *NewBrunswick= new Territory(game->getMap()->getTerritories()[0]);
//        player1->getTerritory().push_back(NewBrunswick);
//
//        game->getMap()->getTerritories()[5].setOwner(player1); // Quebec North
//        Territory *QuebecNorth = new Territory(game->getMap()->getTerritories()[5]);
//        player1->getTerritory().push_back(QuebecNorth);
//
//        game->getMap()->getTerritories()[6].setOwner(player1); // Quebec Central -- Adjacent with the previous one
//        Territory *QuebecCentral = new Territory(game->getMap()->getTerritories()[6]);
//        player1->getTerritory().push_back(QuebecCentral);
//
//        // Assign Territories to Player 2
//        game->getMap()->getTerritories()[30].setOwner(player1); // Yukon -- Not adjacent to any of the others
//        Territory *Yukon = new Territory(game->getMap()->getTerritories()[30]);
//        player1->getTerritory().push_back(Yukon);
//
//        game->getMap()->getTerritories()[7].setOwner(player1); // Quebec South
//        Territory *QuebecSouth = new Territory(game->getMap()->getTerritories()[7]);
//        player1->getTerritory().push_back(QuebecSouth);
//
//        game->getMap()->getTerritories()[9].setOwner(player1); // Ontario South -- Adjacent with the previous one
//        Territory *OntarioSouth = new Territory(game->getMap()->getTerritories()[9]);
//        player1->getTerritory().push_back(OntarioSouth);
//
//        // Assign Territories to Neutral Player
//
//        game->getMap()->getTerritories()[9].setOwner(game->getNeutralPlayer()); // Ontario west -- Adjacent with the previous one
//        Territory *OntarioWest = new Territory(game->getMap()->getTerritories()[9]);
//        game->getNeutralPlayer()->getTerritory().push_back(OntarioWest);
//

//    	Deploy *deploy1 = new Deploy(player1, QuebecNorth);
//	cout << "Adding to the OrdersList the Order: "<< *deploy1 << endl;
//    cout << "Deploy validation: ";
//    deploy1->validate();
//    cout << "----- Deploy execution ----- " << endl;
//    deploy1->execute();
//    cout << deploy1->stringToLog(); // we can use this to print a summary of what happened

	// Advance
	Advance *advance1 = new Advance(player1);
	cout << "Adding to the OrdersList the Order: "<< *advance1 << endl;
//    cout << "Checking for validation: " << advance1->validate() << endl;
//    cout << "Checking for execution: " ; advance1->execute() ;
	player1->getOrder()->addOrder(advance1);
	cout << *player1->getOrder() << "\n" << endl;

    // Airlift
	Airlift *airlift1 = new Airlift(player1);
	cout << "Adding to the OrdersList the Order: "<< *airlift1 << endl;
//    cout << "Checking for validation: " << airlift1->validate() << endl;
//    cout << "Checking for execution: " ; airlift1->execute() ;
	player1->getOrder()->addOrder(airlift1);
	cout << *player1->getOrder() << "\n" << endl;

    // Bomb
	Bomb *bomb1 = new Bomb(player1);
	cout << "Adding to the OrdersList the Order: "<< *bomb1 << endl;
//    cout << "Checking for validation: " << bomb1->validate() << endl;
//    cout << "Checking for execution: " ; bomb1->execute() ;
	player1->getOrder()->addOrder(bomb1);
	cout << *player1->getOrder() << "\n" << endl;

	// Blockade
	Blockade *blockade1 = new Blockade(player1);
	cout << "Adding to the OrdersList the Order: "<< *blockade1 << endl;
//    cout << "Checking for validation: " << blockade1->validate() << endl;
//    cout << "Checking for execution: " ; blockade1->execute() ;
	player1->getOrder()->addOrder(blockade1);
	cout << *player1->getOrder() << "\n" << endl;


	// Negotiate
//	Negotiate *negotiate1 = new Negotiate(player1);
//	cout << "Adding to the OrdersList the Order: "<< *negotiate1 << endl;
//    cout << "Checking for validation: " << negotiate1->validate() << endl;
//    cout << "Checking for execution: " ; negotiate1->execute() ;
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

