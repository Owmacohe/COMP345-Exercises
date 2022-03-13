#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Player; // Forward declaration of Player

// Class representing a node on the graph
class Territory {
    public:
        Territory(); // Default constructor
        Territory(string, string, Player*, int); // Parameterized constructor
        Territory(const Territory &t); // Copy constructor
        ~Territory(); // Destructor
        friend ostream& operator<<(ostream &strm, const Territory &t); // Stream insertion operator
        Territory& operator = (const Territory& toAssign);  // Assignment operator

        // Accessors
        string getName(), getContinent();
        Player *getOwner();
        int getArmies();

        // Mutators
        void setName(string), setContinent(string), setOwner(Player*), setArmies(int);
    private:
        string name; // Name of the Territory
        string continent; // Name of the Territory's continent
        Player* owner; // Name of the owner of the Territory
        int armies; // Number of armies that the Territory has
};

// Small struct representing an edge between nodes on the graph
struct Edge {
    Territory a, b; // Connected territories
    bool visited; // Whether the edge has been visited (when validating)
};

// Class representing the graph data structure
class Map {
    public:
        Map(); // Default constructor
        Map(string); // Parameterized constructor
        Map(const Map &m); // Copy constructor
        ~Map(); // Destructor
        friend ostream& operator<<(ostream &strm, const Map &m); // Stream insertion operator
        Map& operator = (const Map& toAssign); // Assignment operator

        // Accessors
        string getName();
        string *getContinents();
        string *getContinentBonuses();
        Territory *getTerritories();
        Edge *getEdges();

        // Array lengths
        int continentsLength, territoriesLength, edgesLength;

        // Mutators
        void setName(string), setContinents(string*, int), setContinentBonuses(string*), setTerritories(Territory*, int), setEdges(Edge*, int);

        void addContinent(string); // Method to add a new Territory
        void addContinentBonus(string);
        void addTerritory(const Territory &t); // Method to add a new Territory
        void addEdge(const Edge &e); // Method to add a new Edge between Territories

        bool isGoodMap = true;
        bool validate(); // Method to make sure the created Map is valid

        vector<Territory*> getConnectedTerritories(string);
        vector<Territory*> getContinentTerritories(string);
        bool adjacentTerritories(Territory* t1, Territory* t2); // Method to check if two territories are adjacent

    private:
        string name; // Name of the Map
        string *continents; // Array of strings of all the continent names
        string *continentBonuses;
        Territory *territories; // Array of Territories
        Edge *edges; // Array of edges between the Territories
};

// Class to load in new graphs
class MapLoader {
    public:
        Map load(string); // Method to read a .map file with the given name, and output it as a Map
};