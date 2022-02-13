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

Territory::Territory() {
    name = "";
    continent = "";
    owner = new Player;
    armies = 0;
    
    //cout << "[Territory default constructor]" << endl;
}

Territory::Territory(string n, string c, Player *o, int a) : name(n), continent(c), armies(a) {
    owner = o;

    //cout << "[" << n << " Territory param constructor]" << endl;
}

Territory::Territory(const Territory &t) {
    name = t.name;
    continent = t.continent;
    owner = t.owner;
    armies = t.armies;
    
    //cout << "[" << t.name << " Territory copy constructor]" << endl;
}

Territory::~Territory() {
    //cout << "[" << name << " Territory destructor]" << endl;
}

string Territory::getName() { return name; }
string Territory::getContinent() { return continent; }
Player *Territory::getOwner() { return owner; }
int Territory::getArmies() { return armies; }

void Territory::setName(string n) { name = n; }
void Territory::setContinent(string c) { continent = c; }
void Territory::setOwner(Player *o) { owner = o; }
void Territory::setArmies(int a) { armies = a; }

ostream& operator<<(ostream &strm, const Territory &t) {
    return strm <<
        "TERRITORY: " << t.name <<
        "\n    Continent: " << t.continent <<
        "\n    Owner: " << t.owner->getName() <<
        "\n    Armies: " << t.armies;
}

Map::Map() {
    name = "";
    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];

    cout << "[Map default constructor]" << endl;
}

Map::Map(string n) : name(n) {
    continentsLength = 0;
    continents = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
    
    cout << "[" << n << " Map param constructor]" << endl;
}

Map::Map(const Map &m) {
    name = m.name;
    setContinents(m.continents, m.continentsLength);
    setTerritories(m.territories, m.territoriesLength);
    setEdges(m.edges, m.edgesLength);

    cout << "[" << m.name << " Map copy constructor]" << endl;
}

Map::~Map() {
    delete[] continents;
    continents = NULL;

    delete[] territories;
    territories = NULL;

    delete[] edges;
    edges = NULL;

    cout << "[" << name << " Map destructor]" << endl;
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
    string *temp = new string[continentsLength + 1];

    for (int i = 0; i < continentsLength; i++) {
        temp[i] = continents[i];
    }

    continentsLength++;

    delete[] continents;
    continents = temp;

    continents[continentsLength - 1] = c;
}

void Map::addTerritory(const Territory &t) {
    Territory *temp = new Territory[territoriesLength + 1];

    for (int i = 0; i < territoriesLength; i++) {
        temp[i] = territories[i];
    }

    territoriesLength++;

    delete[] territories;
    territories = temp;

    territories[territoriesLength - 1] = t;
}

void Map::addEdge(const Edge &e) {
    Edge *temp = new Edge[edgesLength + 1];

    for (int i = 0; i < edgesLength; i++) {
        temp[i] = edges[i];
    }

    edgesLength++;

    delete[] edges;
    edges = temp;

    edges[edgesLength - 1] = e;
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

ostream& operator<<(ostream &strm, const Map &m) {
    string c = "";
    string t = "";
    string e = "";

    string *continents = m.continents;
    for (int i = 0; i < m.continentsLength; i++) {
        c += continents[i] + ", ";
    }

    Territory *territories = m.territories;
    for (int j = 0; j < m.territoriesLength; j++) {
        t += territories[j].getName() + ", ";
    }

    Edge *edges = m.edges;
    for (int k = 0; k < m.edgesLength; k++) {
        e += edges[k].a.getName() + " and " + edges[k].b.getName() + ", ";
    }

    return strm <<
        "MAP: " << m.name <<
        "\n    Continents: " << c.substr(0, c.length() - 2) <<
        "\n    Territories: " << t.substr(0, t.length() - 2) <<
        "\n    Edges: " << e.substr(0, e.length() - 2);
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

Map MapLoader::load(string f) {
    ifstream input(f);
    string line;
    Map m;

    if (!getline(input, line)) {
        cout << "Unable to read file: " << f << endl;
    }
    else {
        try {
            int section = 0;

            string *nameSplit = stringSplit(line, ' ');
            string mapName = nameSplit[3];
            delete[] nameSplit;

            m.setName(mapName.substr(0, mapName.length() - 4));

            while (getline(input, line)) {
                string *lineSplit = stringSplit(line, ' ');

                if (line == "[continents]" || line == "[countries]" || line == "[borders]") {
                    section++;

                    if (line == "[continents]") {
                        cout << "Loading continents..." << endl;
                    }
                    else if (line == "[countries]") {
                        cout << "Loading territories..." << endl;

                        if (section != 2) {
                            throw "Invalid Map!";
                        }
                    }
                    else if (line == "[borders]") {
                        cout << "Loading edges..." << endl;

                        if (section != 3) {
                            throw "Invalid Map!";
                        }
                    }
                }
                else {
                    if (line != "") {
                        if (section == 1) {
                            if (stoi(lineSplit[0]) == 3) {
                                m.addContinent(lineSplit[1]);
                            }
                            else {
                                throw "Invalid Map!";
                            }
                        }
                        else if (section == 2) {
                            if (stoi(lineSplit[0]) == 5) {
                                Territory t = Territory(lineSplit[2], m.getContinents()[stoi(lineSplit[3]) - 1], NULL, 0);
                                m.addTerritory(t);
                            }
                            else {
                                throw "Invalid Map!";
                            }
                        }
                        else if (section == 3) {
                            if (stoi(lineSplit[0]) > 1) {
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
                            else {
                                throw "Invalid Map!";
                            }
                        }
                    }
                }

                delete[] lineSplit;
            }

            input.close();

            cout << "Map loaded!" << endl;
        }
        catch (const char* message) {
            cout << message << endl;
        }
    }

    return m;
}