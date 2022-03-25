#include "../Player/Player.h"
#include "../Map/Map.h"
#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"

#include <iostream>
using namespace std;

int main() {
    // Create Map Loader
    MapLoader loader;
    Map *mainmap = new Map(loader.load("../Orders/canada.map"));

    // Create Players List
    vector<Player *> players;
    Player *player1 = new Player();
    player1->setName("Normal_Player");
    Player *player2 = new Player();
    player2->setName("Player_with_1_Territory");
    Player *player3 = new Player();
    player3->setName("Player_with_Continent");
    players.push_back(player1);
    players.push_back(player2);
    players.push_back(player3);

    // Create && set up gameEngine
    GameEngine *mainGE = new GameEngine();
    mainGE->setplayer_list(players);
    Deck *deck = new Deck(10);
    mainGE->setDeck(*deck);
    mainGE->setMap(*mainmap);

    // Assign Territories to Players
    // The following will assign equal territories for each player, but I will not be doing this for demonstrative purposes :
    //    int playerIndex = 0;
    //    for (int i = 0; i < mainmap->territoriesLength; i++) {
    //         player_list.at(playerIndex)->assignTerritory(new Territory(mainmap->getTerritories()[i]));
    //         mainmap->getTerritories()[i].setOwner(player_list.at(playerIndex));
    //        playerIndex++;
    //        if (playerIndex >= player_list.size()) { playerIndex = 0; }
    //    }
    // One player with territories normal, one without many territories, and one with a whole continent
    // Player 3
    string continent = mainmap->getContinents().at(0);
    for (Territory *t: mainmap->getTerritories()) {
        if (t->getContinent() == continent) {
            player3->assignTerritory(t);
            t->setOwner(player3);
        }
    }
    // Player 2
    Territory *player2_territory;
    for (Territory *t: mainmap->getTerritories()) {
        if (t->getContinent() != continent) {
            player2->assignTerritory(t);
            t->setOwner(player2);
            player2_territory = t;
            break;
        }
    }
    // Player 1
    for (Territory *t: mainmap->getTerritories()) {
        if (t->getContinent() != continent && t->getName() != player2_territory->getName()) {
            player1->assignTerritory(t);
            t->setOwner(player1);
        }
    }

    // Set up player order
    int *tempOrder = new int[(mainGE->getplayer_list()).size()];
    for (int j = 0; j < (mainGE->getplayer_list()).size(); j++) {
        tempOrder[j] = j;
    }
    for (int i = 0; i < (mainGE->getplayer_list()).size(); i++) {
        int index = (int) (rand() % ((mainGE->getplayer_list()).size() - i));
        int temp = tempOrder[i];
        tempOrder[i] = tempOrder[index];
        tempOrder[index] = temp;
    }
    mainGE->setPlayerOrder(tempOrder);
//    for (int j = 0; j < (mainGE->getplayer_list()).size(); j++) {
//        cout << mainGE->getPlayerOrder()[j] << endl;
//    }

//    // Determine randomly the order of play of the players in the game
//
//    int *tempOrder = new int[player_list.size()];
//
//    for (int j = 0; j < player_list.size(); j++) {
//        tempOrder[j] = rand() % (player_list.size() - j) + j;
//    }
//
//    setPlayerOrder(tempOrder);

    // Initial state of player
    for (Player *k: mainGE->getplayer_list()) {
        // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
        k->addToReinforcePool(10);

        // Let each player draw 2 initial cards from the deck using the deck’s draw() method
        k->getHand()->drawCard(*deck);
        k->getHand()->drawCard(*deck);
    }
    cout<<endl;

    //(1) a player receives the correct number of armies in the reinforcement phase (showing different cases);
    cout <<"---a player receives the correct number of armies in the reinforcement phase---"<<endl;
    mainGE->setNumberOfPlayers((mainGE->getplayer_list()).size());
    cout << "Number of territories : " << mainmap->getTerritories().size() << endl;
    cout << "Player 1 number territories : " << player1->getNumberOfTerritories() << endl;
    cout << "Player 2 number territories : " << player2->getNumberOfTerritories() << endl;
    cout << "Player 3 number territories : " << player3->getNumberOfTerritories() << endl;

    cout << "number of reinforcement for player 1 (" << player1->getName() << ") before reinforcement phase : "
         << player1->getReinforcePool() << endl;
    cout << "number of reinforcement for player 2 (" << player2->getName() << ") before reinforcement phase : "
         << player2->getReinforcePool() << endl;
    cout << "number of reinforcement for player 3 (" << player3->getName() << ") before reinforcement phase : "
         << player3->getReinforcePool() << endl;
    mainGE->assignReinforcementPhase();
    cout << "number of reinforcement for player 1 (" << player1->getName() << ") after reinforcement phase : "
         << player1->getReinforcePool() << endl;
    cout << "number of reinforcement for player 2 (" << player2->getName() << ") after reinforcement phase : "
         << player2->getReinforcePool() << endl;
    cout << "number of reinforcement for player 3 (" << player3->getName() << ") after reinforcement phase : "
         << player3->getReinforcePool() << endl;

//    //(2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;
//    cout <<"---a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool---"<<endl;
//    // Normal case--- every deploy order only deploys 1 army in this case as of the definition of class "Deploy"
//    // During this section fo demo, just click no for advances and card playing
//    mainGE->issueOrdersPhase();
//    int deployCounter = 0;
//    int anyOtherOrders = 0;
//    for (int i = 0; i < (mainGE->getplayer_list()).size(); i++) {
//        Player *p = mainGE->getplayer_list().at(mainGE->getPlayerOrder()[i]);
//        cout<< "Number of armies in reinforcement pool for "<< p->getName() <<" : " << player1->getReinforcePool()<<endl;
//        for(Order* o : p->getOrder()->getOrderList()){
//            if(o->getDescription() == "deploy"){
//                deployCounter ++ ;
//            }else anyOtherOrders++;
//        }
//        cout << "number of deploy orders for player  (" << p->getName() << ") after issueOrderPhase : "
//             << deployCounter << endl;
//
//        deployCounter = 0;
//        anyOtherOrders = 0;
//
//    }
//
//    //(3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists;
//    cout <<"---a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend()---"<<endl;
//    //TODO
//    mainGE->issueOrdersPhase();
//
//    //(4) a player can play cards to issue orders;
//    cout <<"---a player can play cards to issue orders---"<<endl;
//    //TODO
//    mainGE->issueOrdersPhase();

    //(5) a player that does not control any territory is removed from the game;
    cout <<"---a player that does not control any territory is removed from the game---"<<endl;
    cout << "Number players : " << mainGE->getNumberOfPlayers() <<endl;
    cout << "Player order before removal: " <<endl;
    for (int j = 0; j < (mainGE->getplayer_list()).size(); j++) {
        cout << mainGE->getPlayerOrder()[j] << endl;
    }
    cout << "Player list before removal: " <<endl;
    for (Player *p : mainGE->getplayer_list()){
        cout<<p->getName()<<endl;
    }
    for (int i = 0; i < player2->getNumberOfTerritories(); i++) {
        Territory* t = player2->getTerritoryList().at(i);
        player2->removeTerritory(i);
        t->setOwner(player1);
        player1->assignTerritory(t);
    }
    mainGE->checkPlayers();
    cout << "Number players : " << mainGE->getNumberOfPlayers() <<endl;
    cout << "Number players : " << (mainGE->getplayer_list()).size() <<endl;
    cout << "Player order after removal: " <<endl;
    for (int j = 0; j < (mainGE->getplayer_list()).size(); j++) {
        cout << mainGE->getPlayerOrder()[j] << endl;
    }
    cout << "Player list after removal: " <<endl;
    for (Player *p : mainGE->getplayer_list()){
        cout<<p->getName()<<endl;
    }

    //(6) the game ends when a single player controls all the territories.
    cout <<"---the game ends when a single player controls all the territories---"<<endl;
    mainGE->checkForWinner();
    while (player3->getNumberOfTerritories() > 0) {
        Territory* t = player3->getTerritoryList().at(0);
        player3->removeTerritory(0);
        t->setOwner(player1);
        player1->assignTerritory(t);
    }
    mainGE->checkForWinner();

//All of this except the issueOrder() method must be implemented in a single .cpp/.h file duo named GameEngine.cpp/GameEngine.h.


    }

