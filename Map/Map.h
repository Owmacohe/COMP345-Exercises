#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Player;

class Territory {
    public:
        Territory(); // Default constructor
        Territory(string, string, Player*, int); // Parameterized constructor
        Territory(const Territory &t); // Copy constructor
        ~Territory(); // Destructor
        friend ostream& operator<<(ostream &strm, const Territory &t); // Stream insertion operator

        // Accessors
        string getName(), getContinent();
        Player* getOwner();
        int getArmies();

        // Mutators
        void setName(string), setContinent(string), setOwner(Player*), setArmies(int);
    private:
        string name; // Name of the Territory
        string continent; // Name of the Territory's continent
        Player* owner; // Name of the owner of the Territory
        int armies; // Number of armies that the Territory has
};

struct Edge {
    Territory a, b;
};

class Map {
    public:
        Map(); // Default constructor
        Map(string); // Parameterized constructor
        Map(const Map &m); // Copy constructor
        ~Map(); // Destructor
        friend ostream& operator<<(ostream &strm, const Map &m); // Stream insertion operator

        // Accessors
        string getName();
        string* getContinents();
        Territory* getTerritories();
        Edge* getEdges();

        // Array lengths
        int continentsLength, territoriesLength, edgesLength;

        // Mutators
        void setName(string), setContinents(string*, int), setTerritories(Territory*, int), setEdges(Edge*, int);

        void addContinent(string); // Method to add a new Territory
        void addTerritory(Territory); // Method to add a new Territory
        void addEdge(Edge); // Method to add a new Edge between Territories
        bool validate(); // Method to make sure the created Map is valid
    private:
        string name; // Name of the Map
        string *continents; // Array of strings of all the continent names
        Territory *territories; // Array of Territories
        Edge *edges; // Array of edges between the Territories
};

class MapLoader {
    public:
        Map load(string);
};