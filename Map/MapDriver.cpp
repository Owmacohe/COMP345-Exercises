#include "Map.h"
#include "../Player/Player.h"

#include "../Cards/Cards.cpp"
#include "Map.cpp"
#include "../Orders/Orders.cpp"
#include "../Player/Player.cpp"

int mapMain() {
    MapLoader loader;
    
    Map europe = loader.load("europe.map");
    //cout << europe << endl;
    //cout << europe.validate() << endl;

    //Map canada = loader.load("canada.map");
    //cout << canada << endl;
    //cout << canada.validate() << endl;

    return 0;
}