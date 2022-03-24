#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "Orders.h"

int main() {
    /****************************** CREATING A GAME *******************************/

    // Create Map Loader
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

//    cout << "Before Assigning" <<endl;
//    cout << "mainmap directly "<< *(mainmap->getTerritories().at(0)) << endl;
//    cout << " From Order " << *(Order::game->getMap()->getTerritories()[0]) << endl;
//    cout << "From mainGE "<< *(mainGE->getMap()->getTerritories()[0]) << endl;

    // Assign Territories to Players
    int playerIndex = 0;
    cout << mainmap->getTerritories().size()<<endl;
    for (Territory *i : mainmap->getTerritories()) {
        Player *tempPlayer = player_list.at(playerIndex);
        i->setOwner(tempPlayer);
        tempPlayer->assignTerritory(i);

        playerIndex++;
        if (playerIndex >= player_list.size()) {
            playerIndex = 0;
        }
    }

//    cout << "After Assigning" <<endl;
//    cout << "mainmap directly "<< *(mainmap->getTerritories()[0]) << endl;
//    cout << " From Order " << *(Order::game->getMap()->getTerritories()[0]) << endl;
//    cout << "From mainGE "<< *(mainGE->getMap()->getTerritories()[0]) << endl;

    // Display Player list of Territories
    cout << endl;
    for (int i=0; i<player_list.size();i++){
        cout << player_list.at(i)->getName() << "'s territories: ";
        for(auto teri : player_list.at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }

    // ******************************* Testing Orders Constructor *******************************
    // Create Territories for testing
    Territory* Yukon_Territory = Order::game->getMap()->getTerritories().at(30); Yukon_Territory->setArmies(4);
    Territory* Ontario_South = Order::game->getMap()->getTerritories().at(8); Ontario_South->setArmies(0);
    Territory* Ontario_North = Order::game->getMap()->getTerritories().at(10); Ontario_North->setArmies(0);
    Territory* Quebec_Central = Order::game->getMap()->getTerritories().at(6); Quebec_Central->setArmies(4);
    Territory* Manitoba_South = Order::game->getMap()->getTerritories().at(11); Manitoba_South->setArmies(4);

    Territory* Ontario_West = Order::game->getMap()->getTerritories().at(9); Ontario_West->setArmies(4);
    Territory* Quebec_South = Order::game->getMap()->getTerritories().at(7); Quebec_South->setArmies(0);
    Territory* Quebec_North = Order::game->getMap()->getTerritories().at(5); Quebec_North->setArmies(0);
/*
    cout << "\n-------------------- DEPLOY --------------------" << endl;
    Deploy* deploy1 = new Deploy(player1, Ontario_South);
    cout << "Order: " << *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();
    cout << deploy1->stringToLog() << endl;

    Deploy* deploy2 = new Deploy(player2, Quebec_North);
    cout << "Order: " << *deploy2 << endl;
    deploy2->validate();
    deploy2->execute();
    cout << deploy2->stringToLog() << endl;

    // Target territory belongs to enemy -> failed
    Deploy* deploy3 = new Deploy(player1, Ontario_West);
    cout << "Order: " << *deploy3 << endl;
    deploy3->validate();
    deploy3->execute();
    cout << deploy3->stringToLog() << endl;


    cout << "\n-------------------- AIRLIFT --------------------" << endl;
    Airlift* airlift1 = new Airlift(player1, Ontario_South, Ontario_North);
    cout << "Order: " << *airlift1 << endl;
    airlift1->validate();
    airlift1->execute();
    cout << airlift1->stringToLog() << endl;

    // Target territory belongs to enemy -> failed
    Airlift* airlift2 = new Airlift(player1, Ontario_South, Ontario_West);
    cout << "Order: " << *airlift2 << endl;
    airlift2->validate();
    airlift2->execute();
    cout << airlift2->stringToLog() << endl;

    // Origin territory is not yours -> failed
    Airlift* airlift3 = new Airlift(player1, Ontario_West, Ontario_South);
    cout << "Order: " << *airlift3 << endl;
    airlift3->validate();
    airlift3->execute();
    cout << airlift3->stringToLog() << endl;



    cout << "\n-------------------- BOMB --------------------" << endl;
    Bomb* bomb1 = new Bomb(player2, Ontario_West, Ontario_South);
    cout << "Order: " << *bomb1 << endl;
    bomb1->validate();
    bomb1->execute();
    cout << bomb1->stringToLog() << endl;

    // Target territory is your own territory -> failed
    Bomb* bomb2 = new Bomb(player1, Ontario_South, Ontario_North);
    cout << "Order: " << *bomb2 << endl;
    bomb2->validate();
    bomb2->execute();
    cout << bomb2->stringToLog() << endl;

    // Origin territory is not your -> failed
//    Bomb* bomb3 = new Bomb(player1, Ontario_West, Quebec_North);
//    cout << "Order: " << *bomb3 << endl;
//    bomb3->validate();
//    bomb3->execute();
//    cout << bomb3->stringToLog() << endl;

    // Target territory is not adjacent -> failed
    Bomb* bomb6 = new Bomb(player1, Yukon_Territory, Quebec_North);
    cout << "Order: " << *bomb6 << endl;
    bomb6->validate();
    bomb6->execute();
    cout << bomb6->stringToLog() << endl;

    cout << "\n-------------------- BLOCKADE --------------------" << endl;
    Blockade* blockade1 = new Blockade(player2, Ontario_West);
    cout << "Order: " << *blockade1 << endl;
    blockade1->validate();
    blockade1->execute();
    cout << blockade1->stringToLog() << endl;

    Blockade* blockade2 = new Blockade(player1, Quebec_Central);
    cout << "Order: " << *blockade2 << endl;
    blockade2->validate();
    blockade2->execute();
    cout << blockade2->stringToLog() << endl;

    // Target territory belongs to enemy -> failed + The effect of Neural Player persist
    Blockade* blockade3 = new Blockade(player2, Quebec_Central);
    cout << "Order: " << *blockade3 << endl;
    blockade3->validate();
    blockade3->execute();
    cout << blockade3->stringToLog() << endl;

    // Territory is under protection of blockade -> failed
    Bomb* bomb4 = new Bomb(player2, Quebec_South, Quebec_Central);
    cout << "Order: " << *bomb4 << endl;
    bomb4->validate();
    bomb4->execute();
    cout << bomb4->stringToLog() << endl;

    cout << "\n-------------------- NEGOTIATE --------------------" << endl;
    Negotiate* negotiate1 = new Negotiate(player1, player2);
    cout << "Order: " << *negotiate1 << endl;
    negotiate1->validate();
    negotiate1->execute();
    cout << negotiate1->stringToLog() << endl;

    // Target player is yourself -> failed
    Negotiate* negotiate2 = new Negotiate(player1, player1);
    cout << "Order: " << *negotiate2 << endl;
    negotiate2->validate();
    negotiate2->execute();
    cout << negotiate2->stringToLog() << endl;

    cout << "********** Testing the effect of negotiation **********" << endl;
    // Target territory is under negotiate, cannot be bombed -> failed
    Bomb* bomb5 = new Bomb(player2, Quebec_North, Ontario_North);
    cout << "Order: " << *bomb5 << endl;
    bomb5->validate();
    bomb5->execute();
    cout << bomb5->stringToLog() << endl;
*/

    // ******************************* Testing Orders Constructor for GameLoop *******************************
    // ToDefend() & toAttack()

    // Testing GetConnected
//    cout << "Testing GetConnected" << endl;
//    string terriName = player1->getTerritoryList().at(0)->getName();
//    vector<Territory*> territoriesConnected = mainmap->getConnectedTerritories(terriName);
//    for(auto teri : territoriesConnected){
//        cout << *teri << endl;
//    }

    // Testing ToDefend
//    cout << "Testing ToDefend" << endl;
//    vector<Territory*> territoriesToDefend = player1->toDefend(mainmap);
//    for(auto teri : territoriesToDefend){
//        cout << *teri << endl;
//    }

    // Testing ToAttack
//    cout << "Testing ToAttack" << endl;
//    vector<Territory*> territoriesToAttack = player1->toAttack(mainmap);
//    for(auto teri : territoriesToAttack){
//        cout << *teri << endl;
//    }

/*
    // Deploy
    cout << "\n-------------------- DEPLOY --------------------\n" << endl;
    Deploy *deploy1 = new Deploy(player1);
    cout << "Order: "<< *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();
    cout << deploy1->stringToLog() << endl;

    Deploy *deploy2 = new Deploy(player1);
    cout << "Order: "<< *deploy2 << endl;
    deploy2->validate();
    deploy2->execute();
    cout << deploy2->stringToLog() << endl;

    Deploy *deploy3 = new Deploy(player2);
    cout << "Order: "<< *deploy3 << endl;
    deploy3->validate();
    deploy3->execute();
    cout << deploy3->stringToLog() << endl;

    Deploy *deploy4 = new Deploy(player2);
    cout << "Order: "<< *deploy4 << endl;
    deploy4->validate();
    deploy4->execute();
    cout << deploy4->stringToLog() << endl;
*/

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
    cout << "\n-------------------- AIRLIFT --------------------\n" << endl;
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

/*
    // Bomb
    cout << "-------------------- BOMB --------------------" << endl;

    Bomb* bomb1 = new Bomb(player1);
    cout << "Order: " << *bomb1 << endl;
    bomb1->validate();
    bomb1->execute();
    cout << bomb1->stringToLog() << endl;

    // Target territory is your own territory -> failed
    Bomb* bomb2 = new Bomb(player2);
    cout << "Order: " << *bomb2 << endl;
    bomb2->validate();
    bomb2->execute();
    cout << bomb2->stringToLog() << endl;
*/

/*
	// Blockade
    cout << "\n-------------------- BLOCKADE --------------------\n" << endl;
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

/*
    // Negotiate
    cout << "-------------------- NEGOTIATE --------------------" << endl;
	Negotiate *negotiate1 = new Negotiate(player1);
	cout << "Order: "<< *negotiate1 << endl;
    negotiate1->validate();
    negotiate1->execute() ;
    cout<< negotiate1->stringToLog();

    Negotiate *negotiate2 = new Negotiate(player1);
    cout << "Order: "<< *negotiate2<< endl;
    negotiate2->validate();
    negotiate2->execute() ;
    cout<< negotiate2->stringToLog();

    Negotiate *negotiate3 = new Negotiate(player2);
    cout << "Order: "<< *negotiate3 << endl;
    negotiate3->validate();
    negotiate3->execute() ;
    cout<< negotiate3->stringToLog();
*/
	return 0;
}



