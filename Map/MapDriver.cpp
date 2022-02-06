#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "Map.cpp"

int mapMain() {
    cout << endl;

    MapLoader loader;
    Map europe = loader.load("europe.map");
    cout << europe << endl;
    //cout << europe.validate() << endl;

    // TODO use validate() for each Map

    return 0;
}