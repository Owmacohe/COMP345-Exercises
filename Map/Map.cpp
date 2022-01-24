#include "Map.h"

Territory::Territory() {
    name = "";
    continent = "";
    owner = "";
    armies = 0;
}

Territory::Territory(string n, string c, string o, int a) {
    name = n;
    continent = c;
    owner = o;
    armies = a;
}

std::ostream& operator<<(std::ostream &strm, const Territory &t) {
    return strm <<
        "TERRITORY: " << t.name <<
        "\n    Continent: " << t.continent <<
        "\n    Owner: " << t.owner <<
        "\n    Armies: " << t.armies;
}

bool doesContain(list<string> l, string s) {
    bool found = false;

    for (string i : l) {
        if (i == s) {
            found = true;
        }
    }

    return found;
}

Map::Map(string n) {
    name = n;
    territories = {};
    edges = {};
}

void Map::addTerritory(Territory t) {
    territories.push_back(t);

    if (!doesContain(continents, t.continent)) {
        continents.push_back(t.continent);
    }
}

void Map::addEdge(Edge e) {
    edges.push_back(e);
}

bool Map::validate() {
    bool valid = true;

    // TODO verify that it is a connected graph
    // TODO verify that continents are connected subgraphs

    // Verifying that each Territory belongs to only one continent
    for (Territory k : territories) {
        if (!doesContain(continents, k.continent)) {
            valid = false;
        }
    }

    return valid;
}

std::ostream& operator<<(std::ostream &strm, const Map &m) {
    string c = "";
    string t = "";
    string e = "";

    for (string i : m.continents) {
        c += i + ", ";
    }

    for (Territory j : m.territories) {
        t += j.name + ", ";
    }

    for (Edge k : m.edges) {
        e += k.a.name + " and " + k.b.name + ", ";
    }

    return strm <<
        "MAP: " << m.name <<
        "\n    Continents: " << c <<
        "\n    Territories: " << t <<
        "\n    Edges: " << e;
}