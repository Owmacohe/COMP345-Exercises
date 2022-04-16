#include "PlayerStrategies.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../GameEngine/GameEngine.h"
#include "../Cards/Cards.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Create Map Loader
    MapLoader* loader;
    Map *mainmap = loader->load("../Orders/canada.map");

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player();
    HumanPlayerStrategy* humanstrat = new HumanPlayerStrategy(player1);
    player1->setStrategy(humanstrat); player1->setReinforcementPool(12); player1->setName("Audrey");

    Player* player2 = new Player();
    NeutralPlayerStrategy* neutralstrat = new NeutralPlayerStrategy(player2);
    player2->setStrategy(neutralstrat); player2->setReinforcementPool(10); player2->setName("MJ");

    Player* player3 = new Player();
    BenevolentPlayerStrategy* benevolentstrat = new BenevolentPlayerStrategy(player3);
    player3->setStrategy(benevolentstrat); player3->setReinforcementPool(8); player3->setName("Gabbi");

    Player* player4 = new Player();
    AggressivePlayerStrategy* aggressivestrat = new AggressivePlayerStrategy(player4);
    player4->setStrategy(aggressivestrat); player4->setReinforcementPool(6); player4->setName("Owen");

    Player* player5 = new Player();
    CheaterPlayerStrategy* cheaterstrat = new CheaterPlayerStrategy(player5);
    player5->setStrategy(cheaterstrat); player5->setReinforcementPool(4); player5->setName("Joe");

    player_list.push_back(player1); player_list.push_back(player2); player_list.push_back(player3); player_list.push_back(player4); player_list.push_back(player5);

    // Create & Set up Game Engine
    GameEngine* mainGE = new GameEngine();
    mainGE->setMap(mainmap);
    mainGE->setplayer_list(player_list);
    mainGE->setNumberOfPlayers(3);
    PlayerStrategies::game = mainGE;
    Order::game = mainGE;

    // Set up player order
    vector<int> tempOrder;
    for (int j = 0; j < mainGE->getplayer_list().size(); j++) {
        int randOrder = rand() % mainGE->getplayer_list().size();

        while (doesContain(tempOrder, randOrder)) {
            randOrder = rand() % mainGE->getplayer_list().size();
        }
        tempOrder.push_back(randOrder);
    }
    mainGE->setPlayerOrder(tempOrder);

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
    for (int i = 0; i < mainGE->getplayer_list().size(); i++){
        cout << mainGE->getplayer_list().at(i)->getName() << "'s territories: ";
        for(auto teri : mainGE->getplayer_list().at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }
    cout << endl;

    // Give Player Cards
    for (Player* p : mainGE->getplayer_list()) {
        p->getHand()->drawCard(*(mainGE->getDeck()));
        p->getHand()->drawCard(*(mainGE->getDeck()));
        p->getHand()->drawCard(*(mainGE->getDeck()));
    }

    /****************************** Human *******************************/
//    player1->issueOrder("advance"); // attack - New_Brunswick -> Prince_Edward_Island
                                                // to test neutral to aggressive switch
//                                              // neutral attack : Ontario-North, Ontario-South
//                                              // neutral attack : Nunavut-Continental, NU-Victoria_Island-East
//    cout << *player1->toAttack().at(0) << endl; // attack - Quebec-North -> Quebec-Central
//    player1->issueOrder("deploy"); // move - Quebec-North -> New_Brunswick
//    cout << *player1->toDefend().at(0) << endl; //Nunavut-Continental

    /****************************** Aggressive *******************************/
    player4->issueOrder("deploy");
//    player4->issueOrder("deploy");
//    player4->issueOrder("advance");
//    player4->getHand()->drawCard(*PlayerStrategies::game->getDeck());
    /****************************** Benevolent *******************************/
    /****************************** Neutral *******************************/
    // show that neutral can turn into aggressive, test using the human
    // Testing Neutral -> Aggressive
    //    cout << player2->getPlayerStrategy()->getType() << endl;
    //
    //    mainGE->issueOrdersPhase(); // testing without benevolent or cheater use Quebec-Central and Quebec-North
    //
    //    cout << player2->getPlayerStrategy()->getType() << endl;
    /****************************** Cheater *******************************/
    return 0;
}