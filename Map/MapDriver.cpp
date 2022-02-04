#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Map.cpp"

int mapMain() {
    cout << endl;

    MapLoader loader;
    Map europe = loader.load("europe.map");
    //Map canada = loader.load("canada.map");
    cout << europe << endl;
    //cout << europe.validate() << endl;
    //cout << canada << endl;

    // TODO use validate() for each Map

    return 0;
}