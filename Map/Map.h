#pragma once

#include <iostream>
using namespace std;

class Territory {
    public:
        string name; // Name of the Territory
        int edgeSize; // Number of edges
        string *edges; // Array of names of edge Territories
        string owner; // Name of the owner of the Territory
        int armies; // Number of armies that the Territory has

        Territory(); // Default constructor
        Territory(string, int, string*, string, int); // Parameterized constructor
        ~Territory(); // Destructor
};

class Continent {
    public:
        string name; // Name of the Continent
        int nodeSize; // Number of Territories
        Territory *nodes; // Array of Territories

        Continent(); // Default constructor
        Continent(string, int, Territory*); // Parameterized constructor
        ~Continent(); // Destructor

        void addNode(Territory); // Method to add new Territories to the continent
};

class Map {
    public:
        // METHOD add territory
            // Territory param
            // Continent string name param
        
        // METHOD validate
            // verify that it is a connected graph
            // verify that continents are connected subgraphs
            // each country belongs to only one continent
    private:
        // VALUE graph of nodes
            // array of Continents, each with nodes
            // each node is a Territory
};

class MapLoader {
    public:
        // METHOD read map
            // reject bad maps
            // create Map object
};