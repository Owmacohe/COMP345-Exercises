#include <iostream>
using namespace std;

#include "Map.cpp"

int mapMain() {
    cout << endl;

    string quebecEdges[] = { "ON", "NV", "NL&L", "NB" };
    Territory quebec = Territory("QC", 4, quebecEdges, "Owen", 200);
    string ontarioEdges[] = { "MT", "NV", "QC"};
    Territory ontario = Territory("ON", 3, ontarioEdges, "Owen", 100);

    cout << quebec << endl;
    cout << ontario << endl;

    Territory terrs[] = { quebec, ontario };
    Continent canada = Continent("CA", 2, terrs);

    cout << canada << endl;

    // TODO create a Map for each supplied .map file using Maploader

    // TODO use validate() for each Map

    return 0;
}