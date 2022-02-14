#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"

int gameEngineMain() {
    GameEngine gameEngine;
    string input;
    bool isPlaying = true;

    while (isPlaying) {
        gameEngine.startGame();

        while (gameEngine.getState() < 5) {
            cout << "Enter a command: " << endl;
            cin >> input;
            gameEngine.gameStartupTransitions(input);
        }

        while (gameEngine.getState() != 8) {
            for (int i = 0; i < gameEngine.getNumberOfPlayers(); i++) {
                while (true) {
                    cout << gameEngine.getplayer_list()[i]->getName() << "'s turn" <<endl;
                    cout << "What would you like to do now?\n" <<endl;
                    cin >> input;
                    gameEngine.gamePlayTransitions(input, gameEngine.getplayer_list()[i]);
                    
                    if ((gameEngine.getState() == 5 && input == "endexecorders") || (gameEngine.getState() == 8 && input == "win")) {
                        cout << "break" << endl;
                        break;
                    }
                }

                if (input == "win") {
                    break;
                }
            }
        }

        while (gameEngine.getState() == 8) {
            while (true) {
                cout << "What would you like to do next? To Play Again or end the game?" <<endl;
                cin >> input;
                gameEngine.gameEndTransitions(input);

                if (gameEngine.getState() == 0) {
                    if (input == "end") {
                        isPlaying = false;
                    }

                    break;
                }
            }
        }
    }
    
    return 0;
}
