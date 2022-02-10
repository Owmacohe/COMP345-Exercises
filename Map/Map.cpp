#include "Map.h"
#include "../Player/Player.h"

bool doesContain(string* arr, int size, string s) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        if (arr[i] == s) {
            found = true;
        }
    }

    return found;
}

bool doesContain(Edge* arr, int size, Territory t1, Territory t2) {
    bool found = false;

    for (int i = 0; i < size; i++) {
        string n1 = arr[i].a.getName();
        string n2 = arr[i].b.getName();
        string n3 = t1.getName();
        string n4 = t2.getName();

        if (n1 == n3 && n2 == n4) {
            found = true;
        }
    }

    return found;
}

string *stringSplit(string s, char delim) {
    int indexChecker = 0;
    int splitLength = 1;
    string *result = new string[splitLength];
    string temp;

    for (char i : s) {
        if (i != delim) {
            temp += i;
        }

        if (i == delim || indexChecker == s.length() - 1) {
            string *tempResult = new string[splitLength + 1];
            copy(result, result + splitLength, tempResult);

            delete[] result;
            result = new string[splitLength + 1];

            for (int j = 0; j < splitLength; j++) {
                result[j] = tempResult[j];
            }

            result[splitLength] = temp;

            delete[] tempResult;

            splitLength++;
            temp = "";
        }

        indexChecker++;
    }

    result[0] = to_string(splitLength - 1);

    return result;
}

Territory::Territory() {
    cout << "[Territory default constructor]" << endl;

    name = "";
    continent = "";
    owner = new Player;
    armies = 0;
}

Territory::Territory(string n, string c, Player *o, int a) : name(n), continent(c), armies(a) {
    cout << "[" << n << " Territory param constructor]" << endl;

    owner = new Player(*o);
}

Territory::Territory(const Territory &t) {
    cout << "[" << t.name << " Territory copy constructor]" << endl;

    name = t.name;
    continent = t.continent;
    owner = new Player(*(t.owner));
    armies = t.armies;
}

Territory::~Territory() {
    cout << "[" << name << " Territory destructor]" << endl;

    delete owner;
    owner = NULL;
}

string Territory::getName() { return name; }
string Territory::getContinent() { return continent; }
Player *Territory::getOwner() { return owner; }
int Territory::getArmies() { return armies; }

void Territory::setName(string n) { name = n; }
void Territory::setContinent(string c) { continent = c; }
void Territory::setOwner(Player *o) {
    delete owner;
    owner = new Player(*o);
}
void Territory::setArmies(int a) { armies = a; }

std::ostream& operator<<(std::ostream &strm, const Territory &t) {
    Territory temp = Territory(t);

    return strm <<
        "TERRITORY: " << temp.getName() <<
        "\n    Continent: " << temp.getContinent() <<
        "\n    Owner: " << temp.getOwner()->getName() <<
        "\n    Armies: " << temp.getArmies();
}

Map::Map() {
    cout << "[Map default constructor]" << endl;

    name = "";
    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
}

Map::Map(string n) : name(n) {
    cout << "[" << n << " Map param constructor]" << endl;

    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
}

Map::Map(const Map &m) {
    cout << "[" << m.name << " Map copy constructor]" << endl;

    name = m.name;
    setContinents(m.continents, m.continentsLength);
    setTerritories(m.territories, m.territoriesLength);
    setEdges(m.edges, m.edgesLength);
}

Map::~Map() {
    cout << "[" << name << " Map destructor]" << endl;

    delete[] continents;
    continents = NULL;

    delete[] territories;
    territories = NULL;

    delete[] edges;
    edges = NULL;
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

bool validateEdge(Map m, Territory start, Territory end, Territory last) {
    for (int i = 0; i < m.edgesLength; i++) {
        Edge temp = m.getEdges()[i];

        if (temp.a.getName() == end.getName() || temp.b.getName() == end.getName()) {
            return true;
        }
        else if (temp.a.getName() == start.getName() && temp.b.getName() != last.getName()) {
            return validateEdge(m, temp.b, end, start);
        }
        else if (temp.b.getName() == start.getName() && temp.a.getName() != last.getName()) {
            return validateEdge(m, temp.a, end, start);
        }
    }

    return false;
}

bool Map::validate() {
    bool valid = true;
    Territory *temp = getTerritories();

    for (int i = 0; i < territoriesLength; i++) {
        for (int j = 0; j < territoriesLength; j++) {
            valid = validateEdge(*this, temp[i], temp[j], Territory());

            if (temp[i].getContinent() == temp[j].getContinent()) {
                valid = validateEdge(*this, temp[i], temp[j], Territory());
            }
        }

        if (!doesContain(continents, continentsLength, territories[i].getContinent())) {
            valid = false;
        }
    }


    if (valid) {
        cout << "Vefification succeeded!" << endl;
    }
    else {
        cout << "Vefification failed!" << endl;
    }

    return valid;
}

std::ostream& operator<<(std::ostream &strm, const Map &m) {
    Map temp = Map(m);

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
        "\n    Continents: " << c.substr(0, c.length() - 2) <<
        "\n    Territories: " << t.substr(0, t.length() - 2) <<
        "\n    Edges: " << e.substr(0, e.length() - 2);
}

Map MapLoader::load(string f) {
    // TODO reject bad maps

    ifstream input(f);
    string line;
    int section = 0;

    getline(input, line);
    string *nameSplit = stringSplit(line, ' ');
    string mapName = nameSplit[3];
    delete[] nameSplit;
    Map m = Map(mapName.substr(0, mapName.length() - 4));

    while (!input.eof()) {
        getline(input, line);
        string *lineSplit = stringSplit(line, ' ');

        if (line == "[continents]" || line == "[countries]" || line == "[borders]") {
            section++;

            if (line == "[continents]") {
                cout << "Loading continents..." << endl;
            }
            else if (line == "[countries]") {
                cout << "Loading territories..." << endl;
            }
            else if (line == "[borders]") {
                cout << "Loading edges..." << endl;
            }
        }
        else {
            if (line != "") {
                if (section == 1) {
                    m.addContinent(lineSplit[1]);
                }
                else if (section == 2) {
                    m.addTerritory(Territory(
                        lineSplit[2],
                        m.getContinents()[stoi(lineSplit[3]) - 1],
                        new Player,
                        0));
                }
                else if (section == 3) {
                    int len = stoi(lineSplit[0]);

                    for (int i = 1; i <= len; i++) {
                        for (int j = 1; j <= len; j++) {
                            Territory t1 = m.getTerritories()[stoi(lineSplit[i]) - 1];
                            Territory t2 = m.getTerritories()[stoi(lineSplit[j]) - 1];
                            Edge *tempEdges = m.getEdges();

                            if (i != j && !doesContain(tempEdges, m.edgesLength, t1, t2) && !doesContain(tempEdges, m.edgesLength, t2, t1)) {
                                m.addEdge(Edge{t1, t2});
                            }
                        }
                    }
                }
            }
        }

        delete[] lineSplit;
    }

    input.close();

    cout << "Map loaded!" << endl;

    return m;
}