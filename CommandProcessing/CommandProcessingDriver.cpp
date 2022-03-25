#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

int commandProcessingMain() {
    // Driver demonstrates that commands can be read from the console using the CommandProcessor class.
    // Driver demonstrates that commands can be read from a saved text file using the FileCommandProcessorAdapter class.
    // Driver demonstrates that commands that commands that are invalid in the current game state are rejected and valid commands result in the correct effect and state change.

    CommandProcessor *cp;
    FileCommandProcessorAdapter *fcpa;

    cout << "Read commands from console or file?" << endl;

    string word1, word2;
    cin >> word1;

    while (word1 != "console" && word1 != "file") {
        cout << "Please try again!" << endl;
        cin >> word1;
    }

    if (word1 == "file") {
        cout << "Please provide the file name to read from:" << endl;
        cin >> word2;

        fcpa = new FileCommandProcessorAdapter(word2);
        cp = fcpa;
    }
    else {
        CommandProcessor *temp = new CommandProcessor;
        cp = temp;

        cout << "Please give a command: " << endl;
    }

    GameEngine *e = new GameEngine;
    cp->setEngine(e);
    e->setProcessor(cp);
    e->setState(start);

    cp->getCommand();

    Command *c = cp->getCommands()[cp->getCommands().size() - 1];

    cout << endl << *cp << endl << endl;
    cout << *c << endl << endl;

    cout << "Is valid command: " << cp->validate(c) << endl;

    // TODO: figure out how to delete e properly

    return 0;
}