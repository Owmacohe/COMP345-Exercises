#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

int commandProcessingMain() {
    // TODO: initialize a couple Commands and a CommandProcessor

    // TODO: try using readCommand(), saveCommand(), and getCommand()

    GameEngine *e = new GameEngine;
    e->setState(start);
    CommandProcessor cp = CommandProcessor(e);
    cp.getCommand();
    cout << cp << endl;

    // TODO: validate() CommandProcessor

    // TODO: do the above ^, but with a FileCommandProcessorAdapter

    return 0;
}

int main() {
    commandProcessingMain();

    return 0;
}