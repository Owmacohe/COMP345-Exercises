#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"

#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/Map.cpp"
#include "../Player/Player.cpp"
#include "GameEngine.cpp"

int gameEngineMain() {
    GameEngine gameEngine;
    string input;
    bool isPlaying = true;

    while (isPlaying) {

        // ### TODO: the following block will be replaced with startupPhase()
        gameEngine.startGame();

        while (gameEngine.getState() < 5) {
            cout << "Enter a command: " << endl;
            cin >> input;
            gameEngine.gameStartupTransitions(input);
        }
        // ###

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

// DRIVER FOR MAINGAMELOOP
// You must deliver a driver that demonstrates that (1) a player receives the correct number of armies in the
// reinforcement phase (showing different cases); (2) a player will only issue deploy orders and no other kind of
// orders if they still have armies in their reinforcement pool; (3) a player can issue advance orders to either defend
// or attack, based on the toAttack() and toDefend() lists; (4) a player can play cards to issue orders; (5) a
// player that does not control any territory is removed from the game; (6) the game ends when a single player
// controls all the territories. All of this except the issueOrder() method must be implemented in a single .cpp/.h
// file duo named GameEngine.cpp/GameEngine.h.