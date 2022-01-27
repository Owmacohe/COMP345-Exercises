#include "Map.h"

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
    territories = vector<Territory>();
    edges = vector<Edge>();
}

Map::Map(string n) {
    name = n;
    territories = vector<Territory>();
    edges = vector<Edge>();
}

string Map::getName() { return name; }
vector<string>& Map::getContinents() { return continents; }
vector<Territory>& Map::getTerritories() { return territories; }
vector<Edge>& Map::getEdges() { return edges; }

void Map::setName(string n) { name = n; }
void Map::setContinents(vector<string> c) {
    continents = vector<string>();

    for (string i : c) {
        continents.push_back(i);
    }
}
void Map::setTerritories(vector<Territory> t) {
    territories = vector<Territory>();

    for (Territory i : t) {
        territories.push_back(i);
    }
}
void Map::setEdges(vector<Edge> e) {
    edges = vector<Edge>();

    for (Edge i : e) {
        edges.push_back(i);
    }
}

void Map::addTerritory(Territory t) {
    territories.push_back(t);

    if (!doesContain(continents, t.getContinent())) {
        continents.push_back(t.getContinent());
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
        if (!doesContain(continents, k.getContinent())) {
            valid = false;
        }
    }

    return valid;
}

std::ostream& operator<<(std::ostream &strm, const Map &m) {
    Map temp = m;

    string c = "";
    string t = "";
    string e = "";

    for (string i : temp.getContinents()) {
        c += i + ", ";
    }

    for (Territory j : temp.getTerritories()) {
        t += j.getName() + ", ";
    }

    for (Edge k : temp.getEdges()) {
        e += k.a.getName() + " and " + k.b.getName() + ", ";
    }

    return strm <<
        "MAP: " << temp.getName() <<
        "\n    Continents: " << c <<
        "\n    Territories: " << t <<
        "\n    Edges: " << e;
}

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

Map MapLoader::load(string f) {
    // reject bad maps
    // create Map object

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