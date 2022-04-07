#include "PlayerStrategies.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){

    // Create Map Loader
    MapLoader* loader;
    Map *mainMap = loader->load("../Map/canada.map");

    Player* player1 = new Player(new HumanPlayerStrategy());
    Player* player2 = new Player(new AggressivePlayerStrategy());
    Player* player3 = new Player(new BenevolentPlayerStrategy());
    Player* player4 = new Player(new NeutralPlayerStrategy());
    Player* player5 = new Player(new CheaterPlayerStrategy());
    Player* player6 = new Player("Audrey");
    player6->setStrategy(new HumanPlayerStrategy());

    // TODO :: this is currently giving SIGSEGV error, the method can be called but sth inside it is not functioning properly
    player6->toDefend(mainMap);

    return 0;
}
