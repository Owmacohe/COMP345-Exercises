#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

#include "Map.cpp"

int mapMain() {
    cout << endl;

    MapLoader loader = MapLoader();
    Map europe = loader.load("europe.map");
    Map canada = loader.load("canada.map");
    cout << europe << endl;
    //cout << canada << endl;

    // TODO create a Map for each supplied .map file using Maploader
    // TODO use validate() for each Map

    return 0;
}