#include "PlayerStrategies.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../GameEngine/GameEngine.h"
#include <iostream>
#include <vector>

using namespace std;

int PlayerStrategymain() {
    // Create Map Loader
    MapLoader* loader;
    Map *mainmap = loader->load("../Orders/canada.map");

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player();player1->setStrategy(new HumanPlayerStrategy()); player1->setReinforcementPool(12); player1->setName("Audrey");
    Player* player2 = new Player(new AggressivePlayerStrategy()); player2->setReinforcementPool(10); player2->setName("MJ");
    Player* player3 = new Player(new BenevolentPlayerStrategy()); player3->setReinforcementPool(8); player3->setName("Gabbi");
    Player* player4 = new Player(new NeutralPlayerStrategy()); player4->setReinforcementPool(6); player4->setName("Owen");
    Player* player5 = new Player(new CheaterPlayerStrategy()); player5->setReinforcementPool(4); player5->setName("Joe");
    player_list.push_back(player1); player_list.push_back(player2); player_list.push_back(player3); player_list.push_back(player4); player_list.push_back(player5);

    // Create & Set up Game Engine
    GameEngine* mainGE = new GameEngine();
    mainGE->setMap(mainmap);
    mainGE->setplayer_list(player_list);
    PlayerStrategies::game = mainGE;

    // Assign Territories to Players
    int playerIndex = 0;
    for (Territory *i : mainmap->getTerritories()) {
        Player *tempPlayer = mainGE->getplayer_list().at(playerIndex);
        i->setOwner(tempPlayer);
        tempPlayer->assignTerritory(i);

        playerIndex++;
        if (playerIndex >= mainGE->getplayer_list().size()) {
            playerIndex = 0;
        }
    }

    // Display Player list of Territories
    cout << endl;
    for (int i=0; i<mainGE->getplayer_list().size();i++){
        cout << mainGE->getplayer_list().at(i)->getName() << "'s territories: ";
        for(auto teri : mainGE->getplayer_list().at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }
    cout << endl;

    for (Player* p : mainGE->getplayer_list()) {
        cout << p->getPlayerStrategy()->getType() << endl;
        cout << *(p->getPlayerStrategy()) << endl;
    }

    return 0;
}