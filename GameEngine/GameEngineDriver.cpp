#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategy/PlayerStrategies.h"

int gameEngineMain() {
    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine; // TODO: this causes an infinite loop if trying to do a tournament command

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

    GameEngine* gameEngine = new GameEngine;
    PlayerStrategies::game = gameEngine;

    gameEngine->startupPhase();

    Order::logObs->outputFile.close();

    return 0;
}