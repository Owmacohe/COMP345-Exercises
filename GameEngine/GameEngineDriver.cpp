#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategy/PlayerStrategies.h"

int gameEngineMain() {
    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine;

    bool isPlaying = true;

    while (isPlaying) {
        gameEngine->startupPhase();

        // TODO: this might cause errors when running a tournament, so feel free to comment it out
        if (!gameEngine->getIsTournament()) {
            isPlaying = gameEngine->mainGameLoop();
        }
        else {
            isPlaying = false;
        }
    }

    Order::logObs->outputFile.close();

    return 0;
}

int tournamentMain() {
    // tournament -M europe.map -P Aggressive Aggressive -G 1 -D 10

    // TODO: currently breaks when using more than 1 map (players' territories become null)
    // TODO: currently loops infinitely when playing more than 1 game (not sure why)

    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine;
    PlayerStrategies::game = gameEngine;

    gameEngine->startupPhase();

    Order::logObs->outputFile.close();

    return 0;
}