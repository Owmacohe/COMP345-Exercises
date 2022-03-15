#include "Map.h"
#include "../Player/Player.h"
#include <algorithm>

// Free method to determine whether a string pointer array contains a given string
bool doesContain(string* arr, int size, string s) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == s) {
            return true;
        }
    }

    return false;
}

// Free method to determine whether an Edge pointer array contains an Edge between the given Territories
bool doesContain(Edge* arr, int size, Territory t1, Territory t2) {
    for (int i = 0; i < size; i++) {
        string n1 = arr[i].a.getName();
        string n2 = arr[i].b.getName();
        string n3 = t1.getName();
        string n4 = t2.getName();

        if (n1 == n3 && n2 == n4) {
            return true;
        }
    }

    return false;
}

// Territory default constructor
Territory::Territory() {
    name = "";
    continent = "";
    owner = new Player;
    armies = 0;
    
    //cout << "[Territory default constructor]" << endl;
}

// Territory parameterized constructor
Territory::Territory(string n, string c, Player *o, int a) : name(n), continent(c), armies(a) {
    owner = o;

    //cout << "[" << n << " Territory param constructor]" << endl;
}

// Territory copy constructor
Territory::Territory(const Territory &t) {
    name = t.name;
    continent = t.continent;
    owner = t.owner;
    armies = t.armies;
    
    //cout << "[" << t.name << " Territory copy constructor]" << endl;
}

// Territory destructor
Territory::~Territory() {
    //cout << "[" << name << " Territory destructor]" << endl;
}

// Territory accessors
string Territory::getName() { return name; }
string Territory::getContinent() { return continent; }
Player *Territory::getOwner() { return owner; }
int Territory::getArmies() { return armies; }

// Territory mutators
void Territory::setName(string n) { name = n; }
void Territory::setContinent(string c) { continent = c; }
void Territory::setOwner(Player *o) { owner = o; }
void Territory::setArmies(int a) { armies = a; }

// Territory stream insertion operator
ostream& operator<<(ostream &strm, const Territory &t) {
    string temp;

    if (t.owner == NULL) {
        temp = "null";
    }
    else {
        temp = t.owner->getName();
    }

    return strm <<
        "[TERRITORY PRINT: " << t.name << "]" <<
        endl << "[--- Continent: " << t.continent << " ---]" <<
        endl << "[--- Owner: " << temp << " ---]" <<
        endl << "[--- Armies: " << t.armies << " ---]";
}

// Territory assignment operator
Territory& Territory::operator = (const Territory& toAssign){
    name = toAssign.name;
    continent = toAssign.continent;
    owner = toAssign.owner;
    armies = toAssign.armies;
    return *this;
}

// Map default constructor
Map::Map() {
    name = "";
    continentsLength = 0;
    continents = new string[continentsLength];
    continentBonuses = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];

    //cout << "[Map default constructor]" << endl;
}

// Map parameterized constructor
Map::Map(string n) : name(n) {
    continentsLength = 0;
    continents = new string[continentsLength];
    continentBonuses = new string[continentsLength];
    territoriesLength = 0;
    territories = new Territory[territoriesLength];
    edgesLength = 0;
    edges = new Edge[edgesLength];
    
    //cout << "[" << n << " Map param constructor]" << endl;
}

// Map copy constructor
Map::Map(const Map &m) {
    name = m.name;
    setContinents(m.continents, m.continentsLength);
    setContinentBonuses(m.continentBonuses);
    setTerritories(m.territories, m.territoriesLength);
    setEdges(m.edges, m.edgesLength);

    //cout << "[" << m.name << " Map copy constructor]" << endl;
}

// Map destructor
Map::~Map() {
    delete[] continents;
    continents = NULL;

    delete[] continentBonuses;
    continentBonuses = NULL;

    continentsLength = 0;

    delete[] territories;
    territories = NULL;
    territoriesLength = 0;

    delete[] edges;
    edges = NULL;
    edgesLength = 0;

    //cout << "[" << name << " Map destructor]" << endl;
}

// Map stream insertion operator
ostream& operator<<(ostream &strm, const Map &m) {
    string c = "";
    string t = "";
    string e = "";

    // Creating a long deliminated string of all the continents
    string *continents = m.continents;
    for (int i = 0; i < m.continentsLength; i++) {
        c += continents[i] + " | ";
    }

    // Creating a long deliminated string of all the territories
    Territory *territories = m.territories;
    for (int j = 0; j < m.territoriesLength; j++) {
        t += territories[j].getName() + " | ";
    }

    // Creating a long deliminated string of all the Edges
    Edge *edges = m.edges;
    for (int k = 0; k < m.edgesLength; k++) {
        e += edges[k].a.getName() + " and " + edges[k].b.getName() + " | ";
    }

    return strm <<
        "[MAP PRINT: " << m.name << "]" << endl <<
        endl << "[-------------------------Continents--------------------------]" <<
        endl << c.substr(0, c.length() - 3) << endl <<
        endl << "[-------------------------Territories--------------------------]" <<
        endl << t.substr(0, t.length() - 3) << endl <<
        endl << "[-------------------------Edges--------------------------]" <<
        endl << e.substr(0, e.length() - 3);
}

// Map assignment operator
Map& Map::operator = (const Map& toAssign){
    name = toAssign.name;
    continents = toAssign.continents;
    continentBonuses = toAssign.continentBonuses;
    territories = toAssign.territories;
    edges = toAssign.edges;
    return *this;
}

// Map accessors
string Map::getName() { return name; }
string *Map::getContinents() { return continents; }
string *Map::getContinentBonuses() { return continentBonuses; }
Territory *Map::getTerritories() { return territories; }
Edge *Map::getEdges() { return edges; }

// Map mutators
void Map::setName(string n) { name = n; }
void Map::setContinents(string *c, int l) {
    delete[] continents;
    continents = new string[l];

    for (int i = 0; i < l; i++) {
        continents[i] = c[i];
    }

    continentsLength = l;
}
void Map::setContinentBonuses(string *b) {
    delete[] continentBonuses;
    continentBonuses = new string[continentsLength];

    for (int i = 0; i < continentsLength; i++) {
        //continentBonuses[i] = c[i]; SORRY UNCOMMENTED THIS, WHAT IS C?
    }
}
void Map::setTerritories(Territory *t, int l) {
    delete[] territories;
    territories = new Territory[l];

    for (int i = 0; i < l; i++) {
        territories[i] = t[i];
    }

    territoriesLength = l;
}
void Map::setEdges(Edge *e, int l) {
    delete[] edges;
    edges = new Edge[l];

    for (int i = 0; i < l; i++) {
        edges[i] = e[i];
    }

    edgesLength = l;
}

// Method to add a string continent to a Map
void Map::addContinent(string c) {
    string *temp = new string[continentsLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < continentsLength; i++) {
        temp[i] = continents[i];
    }

    // Freeing the old memory and setting the new address
    delete[] continents;
    continents = temp;

    // Setting the new element and incrementing the size variable
    continents[continentsLength] = c;
    continentsLength++;
}

void Map::addContinentBonus(string b) {
    string *temp = new string[continentsLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < continentsLength; i++) {
        temp[i] = continentBonuses[i];
    }

    // Freeing the old memory and setting the new address
    delete[] continentBonuses;
    continentBonuses = temp;

    // Setting the new element and incrementing the size variable
    continentBonuses[continentsLength] = b;
}

// Method to add a Territory to a Map
void Map::addTerritory(const Territory &t) {
    Territory *temp = new Territory[territoriesLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < territoriesLength; i++) {
        temp[i] = territories[i];
    }

    // Freeing the old memory and setting the new address
    delete[] territories;
    territories = temp;

    // Setting the new element and incrementing the size variable
    territories[territoriesLength] = t;
    territoriesLength++;
}

// Method to add an Edge to a Map
void Map::addEdge(const Edge &e) {
    Edge *temp = new Edge[edgesLength + 1]; // Creating a new array (1 size larger)

    // Copying the old elements into the new array
    for (int i = 0; i < edgesLength; i++) {
        temp[i] = edges[i];
    }

    // Freeing the old memory and setting the new address
    delete[] edges;
    edges = temp;

    // Setting the new element and incrementing the size variable
    edges[edgesLength] = e;
    edgesLength++;
}

// Free method to recursively determine if two given Territories are connected between edges on a Map
bool validateEdge(Map &m, Territory &start, Territory &end) {
    Edge *temp = m.getEdges();

    // Checking all the edges for matches
    for (int i = 0; i < m.edgesLength; i++) {
        if (!temp[i].visited) { // Making sure not to check previously used edges
            bool valid;

            // True if the desired destination edge has been reached
            if (temp[i].a.getName() == end.getName() || temp[i].b.getName() == end.getName()) {
                valid = true;
            }
            // Visiting the edge and checking the other Territory if not yet found
            else if (temp[i].a.getName() == start.getName()) {
                temp[i].visited = true;
                valid = validateEdge(m, temp[i].b, end);
            }
            else if (temp[i].b.getName() == start.getName()) {
                temp[i].visited = true;
                valid = validateEdge(m, temp[i].a, end);
            }
            // False if no other option
            else {
                valid = false;
            }

            // Immediately returning true if the destination has been found
            if (valid) {
                return true;
            }
        }
    }

    return false; // False if no matches
}

// Method to determine if a Map is valid
bool Map::validate() {
    Territory *temp = getTerritories();

    // Checking paths from every Territory to every other
    for (int i = 0; i < territoriesLength; i++) {
        for (int j = i+1; j < territoriesLength; j++) {
            if (j < territoriesLength) {
                // Making sure to set the edges to un-visited each new check
                for (int k = 0; k < edgesLength; k++) {
                    edges[k].visited = false;
                }

                // Verifying that the map is a connected graph
                if (!validateEdge(*this, temp[i], temp[j])) {
                    cout << "Validation of " << name << " failed!" << endl;
                    return false;
                }

                // Verifying that continents are connected subgraphs
                if (temp[i].getContinent() == temp[j].getContinent() && !validateEdge(*this, temp[i], temp[j])) {
                    cout << "Validation of " << name << " failed!" << endl;
                    return false;
                }
            }
        }

        // Verifying that each country belongs to one and only one continent
        if (!doesContain(continents, continentsLength, territories[i].getContinent())) {
            cout << "Validation of " << name << " failed!" << endl;
            return false;
        }
    }

    cout << "Validation of " << name << " succeeded!" << endl;
    return true;
}

vector<Territory*> Map::getConnectedTerritories(string n) {
    bool hasFound = true;

    vector<Territory*> connected = vector<Territory*>();

    for (int i = 0; i < edgesLength; i++) {
        Territory other;
        other.setName("null");

        if (edges[i].a.getName() == n) {
            other = Territory(edges[i].b);
        }
        else if (edges[i].b.getName() == n) {
            other = Territory(edges[i].a);
        }

        if (other.getName() != "null") {
            Territory *temp = new Territory(other);
            connected.push_back(temp);
        }
        else {
            hasFound = false;
        }
    }

    if (!hasFound) {
        cout << "No connected Territories!" << endl;
    }

    return connected;
}

vector<Territory*> Map::getContinentTerritories(string c) {
    vector<Territory*> terrs = vector<Territory*>();

    if (doesContain(continents, continentsLength, c)) {
        bool hasFound = false;

        for (int i = 0; i < territoriesLength; i++) {
            if (territories[i].getContinent() == c) {
                Territory *temp = new Territory(territories[i]);
                terrs.push_back(temp);

                hasFound = false;
            }
        }

        if (!hasFound) {
            cout << "Continent has no Territories!" << endl;
        }
    }
    else {
        cout << "Continent does not exist in Map!" << endl;
    }

    return terrs;
}

// Method to check if two territories are adjacent
bool Map::adjacentTerritories(Territory* t1, Territory* t2) {
    vector<Territory*> ct = getConnectedTerritories(t1->getName());
    if(count(ct.begin(), ct.end(), t2)){
    return true;}

    else
    return false;
}

// Free method to split a given string into a pointer array based on a given delimiter
string *stringSplit(string s, char delim) {
    int indexChecker = 0;
    int splitLength = 1;
    string *result = new string[splitLength];
    string temp;

    // Looping through all the characters in the string
    for (char i : s) {
        // Adding to the current word if a delimiter has not been reached
        if (i != delim) {
            temp += i;
        }

        // Adding the neew word to the pointer array if a delimiter or the end has been reached
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

    result[0] = to_string(splitLength - 1); // Making the first element of the array the length

    return result;
}

// Method to read the information at a given file, and output a fully-crafted Map object
Map MapLoader::load(string f) {
    ifstream input(f);
    string line;
    Map m;

    // Checking to see if the file can even be read from
    if (!getline(input, line)) {
        cout << "Unable to read file: " << f << endl;
    }
    else {
        // Catching any issues that might arise from a bad map file
        try {
            int section = 0;

            cout << "Loading name..." << endl;

            string *nameSplit = stringSplit(line, ' ');

            // Making sure the first line (which contains the name) is valid
            if (nameSplit[1] != ";") {
                delete[] nameSplit;
                throw "INVALID MAP: no name!";
            }

            string mapName = nameSplit[3];
            delete[] nameSplit;

            m.setName(mapName.substr(0, mapName.length() - 4)); // Setting the new Map's name

            // Reading every subsequent line in the file
            while (getline(input, line)) {
                string *lineSplit = stringSplit(line, ' '); // Splitting the line

                // Checking to see if a new section of the file has been reached
                if (line == "[continents]" || line == "[countries]" || line == "[borders]") {
                    section++;

                    if (line == "[continents]") {
                        cout << "Loading continents..." << endl;
                    }
                    else if (line == "[countries]") {
                        cout << "Loading territories..." << endl;

                        // Making sure no sections have been left out
                        if (section != 2) {
                            throw "INVALID MAP: no continents!";
                        }
                    }
                    else if (line == "[borders]") {
                        cout << "Loading edges..." << endl;

                        // Making sure no sections have been left out
                        if (section != 3) {
                            throw "INVALID MAP: no continents OR no territories!";
                        }
                    }
                }
                else {
                    // Skipping over blank lines
                    if (line != "") {
                        // Adding each continent
                        if (section == 1) {
                            if (stoi(lineSplit[0]) == 3) {
                                m.addContinent(lineSplit[1]);
                                m.addContinentBonus(lineSplit[2]);
                            }
                            else {
                                throw "INVALID MAP: improper continent!";
                            }
                        }
                        // Adding each Territory
                        else if (section == 2) {
                            if (stoi(lineSplit[0]) == 5) {
                                Territory t = Territory(lineSplit[2], m.getContinents()[stoi(lineSplit[3]) - 1], NULL, 0);
                                m.addTerritory(t);
                            }
                            else {
                                throw "INVALID MAP: improper territory!";
                            }
                        }
                        // Adding each Edge
                        else if (section == 3) {
                            if (stoi(lineSplit[0]) > 1) {
                                int len = stoi(lineSplit[0]);

                                // TODO: this can be optimized greatly
                                // Comparing each Territory with the others on the line, and adding the new Edge if it doesn't yet exist
                                for (int i = 1; i <= len; i++) {
                                    for (int j = i+1; j <= len; j++) {
                                        Territory t1 = m.getTerritories()[stoi(lineSplit[i]) - 1];
                                        Territory t2 = m.getTerritories()[stoi(lineSplit[j]) - 1];
                                        Edge *tempEdges = m.getEdges();

                                        if (!doesContain(tempEdges, m.edgesLength, t1, t2) && !doesContain(tempEdges, m.edgesLength, t2, t1)) {
                                            m.addEdge(Edge{t1, t2});
                                        }
                                    }
                                }
                            }
                            else {
                                throw "INVALID MAP: improper edge!";
                            }
                        }
                    }
                }

                delete[] lineSplit;
            }

            input.close();
            cout << m.getName() << " loaded!" << endl;
        }
        // Setting the Map to bad, and printing the error message
        catch (const char* message) {
            m.isGoodMap = false;
            cout << message << endl;
        }
    }

    return m;
}