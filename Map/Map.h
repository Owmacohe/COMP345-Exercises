#pragma once

class Territory {
    public:
        Territory(); // Default constructor
        Territory(string, string, string, int); // Parameterized constructor

        // Accessors
        string getName(), getContinent(), getOwner();
        int getArmies();

        // Mutators
        void setName(string), setContinent(string), setOwner(string), setArmies(int);
    private:
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
        Map(); // Default constructor
        Map(string); // Parameterized constructor

        // Accessors
        string getName();
        vector<string>& getContinents();
        vector<Territory>& getTerritories();
        vector<Edge>& getEdges();

        // Mutators
        void setName(string), setContinents(vector<string>), setTerritories(vector<Territory>), setEdges(vector<Edge>);

        void addTerritory(Territory); // Method to add a new Territory
        void addEdge(Edge); // Method to add a new Edge between Territories
        bool validate(); // Method to make sure the created Map is valid
    private:
        string name; // Name of the Map
        vector<string> continents; // List of strings all the continent names
        vector<Territory> territories; // List of Territories
        vector<Edge> edges; // List of edges between the Territories
};

class MapLoader {
    public:
        Map load(string);
};