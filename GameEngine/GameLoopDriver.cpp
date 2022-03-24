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
    Map* mainmap = new Map(loader.load("../Orders/canada.map"));

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setName("Normal_Player");
    Player* player2 = new Player(); player2->setName("Player_with_1_Territory");
    Player* player3 = new Player(); player3->setName("Player_with_Continent");
    player_list.push_back(player1); player_list.push_back(player2); player_list.push_back(player3);

    // Create && set up gameEngine
    GameEngine* mainGE = new GameEngine();
    mainGE->setplayer_list(player_list);
    Deck* deck = new Deck(10);
    mainGE->setDeck(*deck);

    // Assign Territories to Players
    // The following will assign equal territories for each player, but i will not be doing this for demonstrative purposes
    // One player with territories normal, one without many territories, and one with a whole continent
//    int playerIndex = 0;
//    for (int i = 0; i < mainmap->territoriesLength; i++) {
//
//        player_list.at(playerIndex)->assignTerritory(new Territory(mainmap->getTerritories()[i]));
//        mainmap->getTerritories()[i].setOwner(player_list.at(playerIndex));
//
//        playerIndex++;
//
//        if (playerIndex >= player_list.size()) {
//            playerIndex = 0;
//        }
//
//    }

    // Determine randomly the order of play of the players in the game
    int *tempOrder = new int[player_list.size()];
    for (int j = 0; j < player_list.size(); j++) {
        tempOrder[j] = rand() % (player_list.size() - j) + j;
    }
    mainGE->setPlayerOrder(tempOrder);

    // Initial state of player
    for (Player* k : player_list) {
        // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
        k->addToReinforcePool(10);

        // Let each player draw 2 initial cards from the deck using the deck’s draw() method
        k->getHand()->drawCard(*deck);
        k->getHand()->drawCard(*deck);
    }

    //(1) a player receives the correct number of armies in the reinforcement phase (showing different cases);
    cout << "number of reinforcement for player 1 (" << player1->getName() << ") before reinforcement phase : " << player1->getReinforcePool() << endl;
    cout << "number of reinforcement for player 2 (" << player2->getName() << ") before reinforcement phase : " << player2->getReinforcePool() << endl;
    cout << "number of reinforcement for player 3 (" << player3->getName() << ") before reinforcement phase : " << player3->getReinforcePool() << endl;
    mainGE->assignReinforcementPhase();
    cout << "number of reinforcement for player 1 (" << player1->getName() << ") after reinforcement phase : " << player1->getReinforcePool() << endl;
    cout << "number of reinforcement for player 2 (" << player2->getName() << ") after reinforcement phase : " << player2->getReinforcePool() << endl;
    cout << "number of reinforcement for player 3 (" << player3->getName() << ") after reinforcement phase : " << player3->getReinforcePool() << endl;
    //(2) a player will only issue deploy orders and no other kind of orders if they still have armies in their reinforcement pool;

    
//(3) a player can issue advance orders to either defend or attack, based on the toAttack() and toDefend() lists;
//(4) a player can play cards to issue orders;
//(5) a player that does not control any territory is removed from the game;
//(6) the game ends when a single player controls all the territories.
//All of this except the issueOrder() method must be implemented in a single .cpp/.h file duo named GameEngine.cpp/GameEngine.h.


}