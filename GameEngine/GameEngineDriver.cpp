#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

int gameEngineMain() {
    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine;

    string input;
    bool isPlaying = true;

    while (isPlaying) {
        gameEngine->startupPhase();
        isPlaying = gameEngine->mainGameLoop();
    }

    return 0;
}