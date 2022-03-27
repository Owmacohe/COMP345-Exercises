#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../CommandProcessing/CommandProcessing.h"

//int main() {
//    GameEngine gameEngine;
//    gameEngine.startupPhase();
//
//    return 0;
//}

int GameEnginemain() {
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