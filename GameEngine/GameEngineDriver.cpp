
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"

#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/Map.cpp"
#include "../Player/Player.cpp"

int main() {
    GameEngine gameEngine;

    //START STATE -- player must enter loadmap to go to the next state
    gameEngine.startGame();

    string input;
    while (gameEngine.getState() < 5) {
        cout << "Enter a command: " << endl;
        cin >> input;
        gameEngine.gameStartupTransitions(input);
    }


    while (gameEngine.getState() != 8) {
    for (int i = 0; i < gameEngine.getNumberOfPlayers(); i++) {
        cout << gameEngine.getplayer_list()[i]->getName() << "'s turn" <<endl;
        string input;
        cout << "What would you like to do now?\n" <<endl;
        cin >> input;
        gameEngine.gamePlayTransitions( input ,gameEngine.getplayer_list()[i]);
    }
    }

    while(gameEngine.getState() == 8) {
        cout << "What would you like to do next? To Play Again or end the game?" <<endl;
        gameEngine.gameEndTransitions(input);
    }
    return 0;

}
