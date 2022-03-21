#include "Orders.h"

#include <iostream>
using namespace std;

int main() {
    /****************************** CREATING A GAME *******************************/
    // Create Map Loader
    MapLoader* loader = new MapLoader();

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player(); player2->setReinforcementPool(12); player2->setName("MJ");
    player_list.push_back(player1); player_list.push_back(player2);

    // Create && set up gameEngine
    GameEngine* mainGE = new GameEngine();
    mainGE->setplayer_list(player_list);
    mainGE->setDeck(*(new Deck(10)));
    mainGE->setMap(*(new Map(loader->load("/Users/Amelia/Documents/COMP345-Exercises/Orders/canada.map"))));

    // Set up Order gameEngine
    Order::game = mainGE;

    // Assign Territories to Player 1
    Order::game->getMap()->getTerritories()[0].setOwner(player1); // New Brunswick -- Not adjacent to any of the others
    Territory *NewBrunswick= new Territory(Order::game->getMap()->getTerritories()[0]);
    player1->getTerritory().push_back(NewBrunswick);

    Order::game->getMap()->getTerritories()[5].setOwner(player1); // Quebec North
    Territory *QuebecNorth = new Territory(Order::game->getMap()->getTerritories()[5]);
    player1->getTerritory().push_back(QuebecNorth);

    Order::game->getMap()->getTerritories()[6].setOwner(player1); // Quebec Central -- Adjacent with the previous one
    Territory *QuebecCentral = new Territory(Order::game->getMap()->getTerritories()[6]);
    player1->getTerritory().push_back(QuebecCentral);

    // Assign Territories to Player 2
    Order::game->getMap()->getTerritories()[30].setOwner(player2); // Yukon -- Not adjacent to any of the others
    Territory *Yukon = new Territory(Order::game->getMap()->getTerritories()[30]);
    player1->getTerritory().push_back(Yukon);

    Order::game->getMap()->getTerritories()[7].setOwner(player2); // Quebec South
    Territory *QuebecSouth = new Territory(Order::game->getMap()->getTerritories()[7]);
    player1->getTerritory().push_back(QuebecSouth);

    Order::game->getMap()->getTerritories()[9].setOwner(player2); // Ontario South -- Adjacent with the previous one
    Territory *OntarioSouth = new Territory(Order::game->getMap()->getTerritories()[9]);
    player1->getTerritory().push_back(OntarioSouth);

    // Assign Territories to Neutral Player
    Order::game->getMap()->getTerritories()[9].setOwner(Order::game->getNeutralPlayer()); // Ontario west -- Adjacent with the previous one
    Territory *OntarioWest = new Territory(Order::game->getMap()->getTerritories()[9]);
    Order::game->getNeutralPlayer()->getTerritory().push_back(OntarioWest);



    cout << "****************************** Creating Orders, validate(), execute() and inserting them *******************************" <<endl;

    //	Deploy
    Deploy *deploy1 = new Deploy(player1);
    cout << "Adding to the OrdersList the Order: "<< *deploy1 << endl;
    cout << "Deploy validation: " << endl;
//    deploy1->validate();
//    cout << "----- Deploy execution ----- " << endl;
//    deploy1->execute();
	player1->getOrder()->addOrder(deploy1);
	cout << *player1->getOrder() << "\n" << endl;

	// Advance
//	Advance *advance1 = new Advance(player1);
//	cout << "Adding to the OrdersList the Order: "<< *advance1 << endl;
//    cout << "Checking for validation: " << advance1->validate() << endl;
//    cout << "Checking for execution: " ; advance1->execute() ;
//	player1->getOrder()->addOrder(advance1);
//	cout << *player1->getOrder() << "\n" << endl;

    // Airlift
//	Airlift *airlift1 = new Airlift(player1);
//	cout << "Adding to the OrdersList the Order: "<< *airlift1 << endl;
//    cout << "Checking for validation: " << airlift1->validate() << endl;
//    cout << "Checking for execution: " ; airlift1->execute() ;
//	player1->getOrder()->addOrder(airlift1);
//	cout << *player1->getOrder() << "\n" << endl;

    // Bomb
//	Bomb *bomb1 = new Bomb(player1);
//	cout << "Adding to the OrdersList the Order: "<< *bomb1 << endl;
//    cout << "Checking for validation: " << bomb1->validate() << endl;
//    cout << "Checking for execution: " ; bomb1->execute() ;
//	player1->getOrder()->addOrder(bomb1);
//	cout << *player1->getOrder() << "\n" << endl;

	// Blockade
//	Blockade *blockade1 = new Blockade(player1);
//	cout << "Adding to the OrdersList the Order: "<< *blockade1 << endl;
//    cout << "Checking for validation: " << blockade1->validate() << endl;
//    cout << "Checking for execution: " ; blockade1->execute() ;
//	player1->getOrder()->addOrder(blockade1);
//	cout << *player1->getOrder() << "\n" << endl;


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

// Create Map
//    MapLoader* loader = new MapLoader();
//    Map* mainMap = new Map(loader->load("/Users/Amelia/Documents/COMP345-Exercises/Orders/canada.map"));
//    cout << *mainMap << endl;

// Create Deck
//    Deck *mainDeck = new Deck(10);
//    cout << mainDeck << endl;