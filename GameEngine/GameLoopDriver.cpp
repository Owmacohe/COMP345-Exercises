#include "../Player/Player.h"
#include "../Map/Map.h"
#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"

#include <iostream>
using namespace std;

int GameLoopmain() {
    // Create Map Loader
    MapLoader loader;
    Map *mainmap = new Map(loader.load("../Orders/canada.map"));

    // Create Players List
    vector<Player *> player_list;
    Player *player1 = new Player();
    player1->setName("Normal_Player");
    Player *player2 = new Player();
    player2->setName("Player_with_1_Territory");
    Player *player3 = new Player();
    player3->setName("Player_with_Continent");
    player_list.push_back(player1);
    player_list.push_back(player2);
    player_list.push_back(player3);

    // Create && set up gameEngine
    GameEngine *mainGE = new GameEngine();
    mainGE->setplayer_list(player_list);
    Deck *deck = new Deck(10);
    mainGE->setDeck(*deck);

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
    for (Territory *t : mainmap->getTerritories()) {
        if (t->getContinent() != continent && t->getName() != player2_territory->getName()) {
            player1->assignTerritory(t);
            t->setOwner(player1);
        }
    }
    vector<Territory*> t = player3->toAttack(mainmap);
    for (Territory* territory : t) {
        cout<<territory->getName()<<" owned by "<<territory->getOwner()->getName()<<endl;
    }

    //TODO:: not functioning
    // Determine randomly the order of play of the players in the game
    int *tempOrder = new int[player_list.size()];
    for (int j = 0; j < player_list.size(); j++) {
        tempOrder[j] = rand() % (player_list.size() - j) + j;
        //std::random_shuffle( myvector.begin(), myvector.end() );
    }

    mainGE->setPlayerOrder(tempOrder);
    for (int k = 0; k < player_list.size(); k++) {
        cout<<mainGE->getPlayerOrder()[k] <<endl;
    }

    // Initial state of player
    for (Player* k : player_list) {
        // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
        k->addToReinforcePool(10);

        // Let each player draw 2 initial cards from the deck using the deck’s draw() method
        k->getHand()->drawCard(*deck);
        k->getHand()->drawCard(*deck);
    }
    cout<<endl;
    mainGE->setNumberOfPlayers(player_list.size());
    cout << "Number of territories : " << mainmap->getTerritories().size()<<endl;
    cout << "Player 1 number territories : " << player1->getNumberOfTerritories()<<endl;
    cout << "Player 2 number territories : " << player2->getNumberOfTerritories()<<endl;
    cout << "Player 3 number territories : " << player3->getNumberOfTerritories()<<endl;
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