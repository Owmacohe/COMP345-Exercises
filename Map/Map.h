#pragma once

class Territory {
    public:
        // TODO re-implement copy constructor

        Territory(); // Default constructor
        Territory(string, string, string, int); // Parameterized constructor
        //Territory(const Territory &t); // Copy constructor
        ~Territory(); // Destructor

        // Accessors
        string getName(), getContinent(), getOwner();
        int getArmies();

        // Mutators
        void setName(string), setContinent(string), setOwner(string), setArmies(int);
    private:
        // TODO change owner's type to Player
        
        string name; // Name of the Territory
        string continent; // Name of the Territory's continent
        string owner; // Name of the owner of the Territory
        int armies; // Number of armies that the Territory has
};

struct Edge {
    Territory a, b;
};

class Map {
    public:
        // TODO re-implement copy constructor
        
        Map(); // Default constructor
        Map(string); // Parameterized constructor
        //Map(const Map &m); // Copy constructor
        ~Map(); // Destructor

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