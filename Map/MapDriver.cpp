#include <iostream>
#include <list>
using namespace std;

#include "Map.cpp"

int mapMain() {
    cout << endl;

    Territory qc = Territory("Quebec", "Eastern Canada", "Owen", 100);
    Territory on = Territory("Ontario", "Eastern Canada", "Owen", 200);
    Territory bc = Territory("British Columbia", "Western Canada", "Owen", 300);

    cout << qc << endl;
    cout << on << endl;
    cout << bc << endl;

    Map ca = Map("Canada");
    ca.addTerritory(qc);
    ca.addTerritory(on);
    ca.addTerritory(bc);
    ca.addEdge(Edge{qc, on});
    //ca.territories.front().continent = "Prairies";

    cout << ca << endl;
    cout << ca.validate() << endl;

    // TODO create a Map for each supplied .map file using Maploader
    // TODO use validate() for each Map

    return 0;
}