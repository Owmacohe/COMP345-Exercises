
#include "../Cards/Cards.cpp"
#include "../Orders/Orders.cpp"
#include "../Map/Map.cpp"
#include "../Player/Player.cpp"
#include "GameEngine.cpp"



#include "../Cards/CardsDriver.cpp"
#include "../Orders/OrdersDriver.cpp"
#include "../Map/MapDriver.cpp"
#include "../Player/PlayerDriver.cpp"


/*
int main() {
    State * s = 0;
    GameEngine* game = new GameEngine();
    game->startGame();
    *s = game->getState();
    cout << *s << endl;

    return 0;
}
*/


int main() {
    GameEngine gameEngine;
    int numPlayer;
    //TODO :  the plauer enters the commands and if they are the same as the edges,
    // then we can go to the next state, there needs to be cint in between every state and if it matches, cool,
    // else we need error message and try again or stay in the same state

    //START STATE -- player must enter loadmap to go to the next state
    cout << "Welcome to Warzone" << endl;

    // MAP LOADED --- HAS LOOP UNTO ITSELF -- player must enter loadmap to stay or validatemap to continue
    MapLoader loader;
    Map europe = loader.load("europe.map");
    cout << europe << endl; //TODO Owen how should your stream inseration be used here

    // MAP VALIDATED -- player must enter add player to continue
    cout << europe.validate() << endl; // TODO is this already included in MapLoader?

    // PLAYERS ADDED --- HAS LOOP UNTO ITSELF -- player must enter addplayer to stay or assigncountries to continue
    cout << "Enter The number of Player: ";
    cin >> numPlayer;
    gameEngine.setNumberOfPlayers(numPlayer);
    gameEngine.addPlayer(); // There was a for loop here but the method already has a for loop.

    // WHATEVER IS BELOW HAS TO LOOP FOR EACH PLAYER UNTIL SOMEONE WINS
    // ASSIGN REINFORCEMENT -- player must enter issueorder to issue order
    //TODO in cpp, not sure if implementaiton is needed or just going through the states is enough

    // ISSUE ORDERS -- HAS LOOP UNTO ITSELF -- player must enter issueorder to stay or endissueorders to continue
    //TODO  in cpp, not sure if implementaiton is needed or just going through the states  is enough

    // EXECUTE ORDERS -- HAS LOOP UNTO ITSELF -- player must enter execorder to stay or endexecorder to continue to the next player's turn
    // TODO in cpp, not sure if implementaiton is needed or just going through the states  is enough

    // WIN -- PLayer enters win

    return 0;

}
