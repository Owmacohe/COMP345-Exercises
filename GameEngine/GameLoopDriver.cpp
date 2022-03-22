#include "../Player/Player.h"
#include "../Map/Map.h"
#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"

#include <iostream>
using namespace std;

int main() {
    // Create Map Loader
    MapLoader* loader = new MapLoader();

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player(); player2->setReinforcementPool(10); player2->setName("MJ");
    Player* player3 = new Player(); player3->setReinforcementPool(10); player2->setName("Gabbi");
    player_list.push_back(player1); player_list.push_back(player2); player_list.push_back(player3);

    // Create && set up gameEngine
    GameEngine* mainGE = new GameEngine();
    mainGE->setplayer_list(player_list);
    mainGE->setDeck(*(new Deck(10)));
    Map* mainmap = new Map(loader->load("../Orders/canada.map"));

    int playerIndex = 0;
    cout << mainmap->territoriesLength<<endl;
    for (int i = 0; i < mainmap->territoriesLength; i++) {
        Player *tempPlayer = player_list.at(playerIndex);
        cout << tempPlayer->getName()<<endl;

        mainmap->getTerritories()[i].setOwner(tempPlayer);
        Territory *tempTerr = new Territory(mainmap->getTerritories()[i]);
        tempPlayer->assignTerritory(tempTerr);
        cout << tempTerr->getName()<<endl;
        playerIndex++;

        if (playerIndex >= player_list.size()) {
            playerIndex = 0;
        }
    }
}