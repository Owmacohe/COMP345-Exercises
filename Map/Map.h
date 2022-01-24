#pragma once

class Territory {
    public:
        string name; // Name of the Territory
        string continent; // Name of the Territory's continent
        string owner; // Name of the owner of the Territory
        int armies; // Number of armies that the Territory has

        Territory(); // Default constructor
        Territory(string, string, string, int); // Parameterized constructor
};

struct Edge {
    Territory a, b;
};

class Map {
    public:
        string name;
        list<string> continents;
        list<Territory> territories;
        list<Edge> edges;

        void addTerritory(Territory);
        void addEdge(Edge);
        bool validate();

        Map(string);
};

class MapLoader {
    public:
        // METHOD read map
            // reject bad maps
            // create Map object
};