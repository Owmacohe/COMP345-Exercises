
#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/Map.cpp"
#include "../Player/Player.cpp"
#include "GameEngine.cpp"



#include "../Cards/CardsDriver.cpp"
#include "../Orders/OrdersDriver.cpp"
#include "../Map/MapDriver.cpp"
#include "../Player/PlayerDriver.cpp"


int main() {
    GameEngine gameEngine;
    int numPlayer;
    //TODO :  the plauer enters the commands and if they are the same as the edges,
    // then we can go to the next state, there needs to be cint in between every state and if it matches, cool,
    // else we need error message and try again or stay in the same state

    //START STATE -- player must enter loadmap to go to the next state
    gameEngine.startGame();

    string input;
    while (gameEngine.getState() < 5) {
        cout << "Enter a command: " << endl;
        cin >> input;
        gameEngine.gameStartupTransitions(input);
    }

    // WHATEVER IS BELOW HAS TO LOOP FOR EACH PLAYER UNTIL SOMEONE WINS
    while (gameEngine.getState() != 8) {
    for (int i = 0; i < gameEngine.getNumberOfPlayers(); i++) {
        cout << gameEngine.getplayer_list()[i]->getName() << "'s turn" <<endl;
        string input;
        cout << "What would you like to do now?\n" <<endl;
        cin >> input;
        gameEngine.gamePlayTransitions( input ,gameEngine.getplayer_list()[i]);
        //TODO IF A PLAYER WINS AND OTEHR PLAYERS HAVE NOT HAD THEIR TURN,DO WE FINISH THE FOR LOOP OR END IT
    }
    }

    while(gameEngine.getState() == 8) {
        cout << "What would you like to do next? To Play Again or end the game?" <<endl;
        gameEngine.gameEndTransitions(input);
    }
    return 0;

}
