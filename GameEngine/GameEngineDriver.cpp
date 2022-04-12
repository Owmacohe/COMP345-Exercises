#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategy/PlayerStrategies.h"

int gameEngineMain() {
    // tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>

    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine;
    PlayerStrategies::game = gameEngine;

    bool isPlaying = true;

    while (isPlaying) {
        gameEngine->startupPhase();

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

int main() {
    gameEngineMain();

    return 0;
}