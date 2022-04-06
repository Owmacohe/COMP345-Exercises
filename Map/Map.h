#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/// Forward declaration of Player
class Player;

/// Free method to determine whether a string vector contains a given string
bool doesContain(vector<string>, int, string);

/**
 Free method to split a given string into a string vector based on a given delimiter
 @param string to be split, char as the delimiter
 @return Vector with strings resulting from the split
 */
vector<string> stringSplit(string, char);

/**
 Class representing a node on the graph (a territory on the Map)
 */
class Territory {
    public:
        /// Default constructor
        Territory();

        /**
        Free method to split a given string into a string vector based on a given delimiter
        @param string to be split, char as the delimiter
        @return Vector with strings resulting from the split
        */
        Territory(string, string, Player*, int);

        /**
        Copy constructor that creates a deep copy
        @param constant Territory reference
        @return pointer to the Territory created
        */
        Territory(const Territory &t);

        /// Destructor
        ~Territory();

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the territory as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream &strm, const Territory &t);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Territory reference that will be copied and assigned
        @return Territory reference
        */
        Territory& operator = (const Territory& toAssign);

        /**
        Accessor for the name of the Territory
        @param None
        @return string that is the name of the Territory
        */
        string getName();

        /**
        Accessor for the Continent of the Territory
        @param None
        @return string that is the name of the Continent
        */
        string getContinent();

        /**
        Accessor for the player owner of the Territory
        @param None
        @return pointer to the Player who is the owner of the territory
        */
        Player *getOwner();

        /**
        Accessor for the owner's name
        @param None
        @return string name of the owner
        */
        string getOwnerName();

        /**
        Accessor for the number of armies in the Territory
        @param None
        @return int that is the number of Armies in the Territory
        */
        int getArmies();

        /**
        Mutator for the name of the Territory
        @param string that is the name of the Territory
        @return None
        */
        void setName(string);

        /**
        Mutator for the continent name
        @param string that is the continent name
        @return None
        */
        void setContinent(string);

        /**
        Mutator for the owner Player
        @param Player pointer that will be the owner
        @return None
        */
        void setOwner(Player*);

        /**
        Mutator for the number of armies in the Territory
        @param int that represent the number of armies
        @return None
        */
        void setArmies(int);

    private:
        /// Name of the Territory
        string name;
        /// Name of the Territory's continent
        string continent;
        /// Name of the owner of the Territory
        Player *owner;
        /// Number of armies that the Territory has
        int armies;
};

/// Small struct representing an edge between nodes on the graph
class Edge {
    public:
        /// Connected territories
        Territory *a, *b;
        /// Whether the edge has been visited (when validating)
        bool visited;
};

/**
 Free method to determine whether an Edge vector contains an Edge between the given Territories
 @param Vector of Edges, an int, and a Territory
 @return boolean
 */
bool doesContain(vector<Edge*>, Territory, Territory); // TODO : Removed in as parameter, now the implementation matches

/// Class representing the graph data structure
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
        vector<string> getContinents();
        vector<int> getContinentBonuses();
        vector<Territory*> getTerritories();
        vector<Edge*> getEdges();

        // Mutators
        void setName(string), setContinents(vector<string>), setContinentBonuses(vector<int>), setTerritories(vector<Territory*>), setEdges(vector<Edge*>);

        void addContinent(string); // Method to add a new continent
        void addContinentBonus(int); // Method to add a new continent bonus
        void addTerritory(Territory*); // Method to add a new Territory
        void addEdge(Edge*); // Method to add a new Edge between Territories

        bool isGoodMap = true; // Whether the Map that has been attempted to be loaded is from a proper file
        bool validateEdge(Map*, Territory*, Territory*); // Method to recursively determine if two given Territories are connected between edges on a Map
        bool validate(); // Method to make sure the created Map is valid

        vector<Territory*> getConnectedTerritories(string); // Method to get all Territories that are connected to a given Territory
        vector<Territory*> getContinentTerritories(string); // Method to get all Territories that are a part of a given Ccntinent
        bool adjacentTerritories(Territory*, Territory*); // Method to check if two territories are adjacent
    private:
        string name; // Name of the Map
        vector<string> continents; // Array of strings of all the continent names
        vector<int> continentBonuses; // Array of strings of all the continent names
        vector<Territory*> territories; // Array of Territories
        vector<Edge*> edges; // Array of edges between the Territories
};

// Class to load in new graphs
class MapLoader {
    public:
        Map *load(string); // Method to read a .map file with the given name, and output it as a Map
};