#include "Map.h"
#include <iostream>
#include <iostream>
#include <string>
using namespace std;

/*
bool doesContain(vector<string> v, string s) {
    bool found = false;

    for (string i : v) {
        if (i == s) {
            found = true;
        }
    }

    return found;
}

bool doesContain(vector<Edge> v, Territory t1, Territory t2) {
    bool found = false;

    for (Edge i : v) {
        string n1 = i.a.getName();
        string n2 = i.b.getName();
        string n3 = t1.getName();
        string n4 = t2.getName();

        if (n1 == n3 && n2 == n4) {
            found = true;
        }
    }

    return found;
}
*/

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

/*
Territory::Territory(const Territory &t) {
    Territory temp = t;

    name = temp.getName();
    continent = temp.getContinent();
    owner = temp.getOwner();
    armies = temp.getArmies();
}
*/

Territory::~Territory() {
    cout << name << " destroyed" << endl;
}

string Territory::getName() { return name; }
string Territory::getContinent() { return continent; }
string Territory::getOwner() { return owner; }
int Territory::getArmies() { return armies; }

void Territory::setName(string n) { name = n; }
void Territory::setContinent(string c) { continent = c; }
void Territory::setOwner(string o) { owner = o; }
void Territory::setArmies(int a) { armies = a; }

std::ostream& operator<<(std::ostream &strm, const Territory &t) {
    Territory temp = t;

    return strm <<
        "TERRITORY: " << temp.getName() <<
        "\n    Continent: " << temp.getContinent() <<
        "\n    Owner: " << temp.getOwner() <<
        "\n    Armies: " << temp.getArmies();
}

Map::Map() {
    name = "";
    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
}

Map::Map(string n) {
    name = n;
    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
}

/*
Map::Map(const Map &m) {
    Map temp = m;

    name = temp.getName();
    setContinents(temp.getContinents(), temp.continentsLength);
    setTerritories(temp.getTerritories(), temp.territoriesLength);
    setEdges(temp.getEdges(), temp.edgesLength);
}
*/

Map::~Map() {
    delete[] continents;
    continents = NULL;

    delete[] territories;
    territories = NULL;

    delete[] edges;
    edges = NULL;

    cout << endl << name << " destroyed" << endl;
}

string Map::getName() { return name; }
string *Map::getContinents() { return continents; }
Territory *Map::getTerritories() { return territories; }
Edge *Map::getEdges() { return edges; }

void Map::setName(string n) { name = n; }
void Map::setContinents(string *c, int l) {
    delete[] continents;
    continents = new string[l];

    copy(c, c + l, continents);

    continentsLength = l;
}
void Map::setTerritories(Territory *t, int l) {
    delete[] territories;
    territories = new Territory[l];

    copy(t, t + l, territories);

    territoriesLength = l;
}
void Map::setEdges(Edge *e, int l) {
    delete[] edges;
    edges = new Edge[l];

    copy(e, e + l, edges);

    edgesLength = l;
}

void Map::addContinent(string c) {
    string *temp = new string[continentsLength];
    copy(continents, continents + continentsLength, temp);

    delete[] continents;
    continents = new string[continentsLength + 1];

    for (int i = 0; i < continentsLength; i++) {
        continents[i] = temp[i];
    }

    continents[continentsLength] = c;

    delete[] temp;

    continentsLength++;
}

void Map::addTerritory(Territory t) {
    Territory *temp = new Territory[territoriesLength];
    copy(territories, territories + territoriesLength, temp);

    delete[] territories;
    territories = new Territory[territoriesLength + 1];

    for (int i = 0; i < territoriesLength; i++) {
        territories[i] = temp[i];
    }

    territories[territoriesLength] = t;

    delete[] temp;

    territoriesLength++;
}

void Map::addEdge(Edge e) {
    Edge *temp = new Edge[edgesLength];
    copy(edges, edges + edgesLength, temp);

    delete[] edges;
    edges = new Edge[edgesLength + 1];

    for (int i = 0; i < edgesLength; i++) {
        edges[i] = temp[i];
    }

    edges[edgesLength] = e;

    delete[] temp;

    edgesLength++;
}

bool Map::validate() {
    bool valid = true;

    // TODO verify that it is a connected graph
    // TODO verify that continents are connected subgraphs
    // TODO verify that each Territory belongs to only one continent

    return valid;
}

std::ostream& operator<<(std::ostream &strm, const Map &m) {
    Map temp = m;

    string c = "";
    string t = "";
    string e = "";

    string *continents = temp.getContinents();
    for (int i = 0; i < m.continentsLength; i++) {
        c += continents[i] + ", ";
    }

    Territory *territories = temp.getTerritories();
    for (int j = 0; j < m.territoriesLength; j++) {
        t += territories[j].getName() + ", ";
    }

    Edge *edges = temp.getEdges();
    for (int k = 0; k < m.edgesLength; k++) {
        e += edges[k].a.getName() + " and " + edges[k].b.getName() + ", ";
    }

    return strm <<
        "MAP: " << temp.getName() <<
        "\n    Continents: " << c <<
        "\n    Territories: " << t <<
        "\n    Edges: " << e;
}

/*
vector<string> stringSplit(string s, char delim) {
    vector<string> temp = vector<string>();

    string phrase = "";

    for (char i : s) {
        if (i != delim) {
            phrase += i;
        }
        else {
            temp.push_back(phrase);
            phrase = "";
        }
    }

    temp.push_back(phrase);

    return temp;
}
*/

/*
Map MapLoader::load(string f) {
    // TODO reject bad maps
    // TODO check and see if it's a directionless graph or not

    Map m = Map();

    ifstream input(f);
    string line;
    int section = 0;

    getline(input, line);
    string mapName = stringSplit(line, ' ')[2];
    m.setName(mapName.substr(0, mapName.length() - 4));

    while (!input.eof()) {
        getline(input, line);

        if (line == "[continents]" || line == "[countries]" || line == "[borders]") {
            section++;
        }
        else {
            if (line != "") {
                if (section == 1) {
                    m.getContinents().push_back(stringSplit(line, ' ')[0]);
                }
                else if (section == 2) {
                    vector<string> temp = stringSplit(line, ' ');

                    m.addTerritory(Territory(
                        temp[1],
                        m.getContinents()[stoi(temp[2]) - 1],
                        "",
                        stoi(temp[3])));
                }
                else if (section == 3) {
                    vector<string> temp = stringSplit(line, ' ');

                    for (string i : temp) {
                        for (string j : temp) {
                            Territory t1 = m.getTerritories()[stoi(i) - 1];
                            Territory t2 = m.getTerritories()[stoi(j) - 1];
                            vector<Edge> tempEdges = m.getEdges();

                            if (i != j && !doesContain(tempEdges, t1, t2) && !doesContain(tempEdges, t2, t1)) {
                                m.addEdge(Edge{t1, t2});
                            }
                        }
                    }
                }
            }
        }
    }

    input.close();

    return m;
}
*/