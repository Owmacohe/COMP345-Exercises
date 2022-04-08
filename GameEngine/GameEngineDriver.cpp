#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

int gameEnginemain() {
    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine; // TODO: what is this line for? ANSWER : basically order has a game engine attribute so this just initializes it, it is necessary line of code very important

    bool isPlaying = true;

    while (isPlaying) {
        gameEngine->startupPhase();
        isPlaying = gameEngine->mainGameLoop();
    }

    return 0;
}

int tournamentMain() {
    // tournament -M europe.map -P Aggressive Benevolent -G 1 -D 10

//    CommandProcessor cp;
//    cp.getCommand();
//    cout << *cp.getCommands()[cp.getCommands().size() - 1] << endl;

    GameEngine* gameEngine = new GameEngine;
    gameEngine->startupPhase();

    return 0;
}