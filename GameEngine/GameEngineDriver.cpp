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

int main() {
    //cardsMain();
    //gameEngineMain();
    //mapMain();
    //ordersMain();
    //playerMain();

    /*
    State * s = 0;
    GameEngine* game = new GameEngine();
    game->startGame();
    *s = game->getState();
    cout << *s << endl;
    */

    return 0;
}

/*
int main(){
    GameEngine gameEngine;
    int numPlayer;
    
    Greeting message
    cout << "Welcome to Warzone" << endl;
    cout << "Enter The number of Player: ";
    cin >> numPlayer;
    
    Create player
    gameEngine.setNumberOfPlayers(numPlayer);
    for (size_t i=0; i<numPlayer;i++){
        gameEngine.addPlayer();
    }
    
    Create Map
    MapLoader loader;

    Map europe = loader.load("europe.map");
    cout << europe << endl;
    cout << europe.validate() << endl;

    Create Deck
    Deck mainDeck;

    Create order
    Order player1List;

    return 0;

}
*/