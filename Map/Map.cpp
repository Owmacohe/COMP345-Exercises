#include "Map.h"

Territory::Territory() {
    name = "";
    edgeSize = 0;
    edges = NULL;
    armies = 0;
    owner = "";
}

Territory::Territory(string pName, int pEdgeSize, string *pEdges, string pOwner, int pArmies) {
    name = pName;

    edgeSize = pEdgeSize;
    edges = new string[edgeSize];

    for (int i = 0; i < edgeSize; i++) {
        edges[i] = pEdges[i];
    }

    owner = pOwner;
    armies = pArmies;
}

Territory::~Territory() {
    delete edges;
    edges = NULL;
}

std::ostream& operator<<(std::ostream &strm, const Territory &territory) {
    string tempEdges = "";

    for (int i = 0; i < territory.edgeSize; i++) {
        tempEdges += " " + territory.edges[i];
    }

    return strm <<
        "Territory( Name: " << territory.name <<
        ", Edges:" << tempEdges <<
        ", Owner: " << territory.owner <<
        ", Armies: " << territory.armies << " )";
}

Continent::Continent() {
    name = "";
    nodeSize = 0;
    nodes = NULL;
}

Continent::Continent(string pName, int pNodeSize, Territory *pNodes) {
    name = pName;

    nodeSize = pNodeSize;
    nodes = new Territory[nodeSize];

    for (int i = 0; i < nodeSize; i++) {
        nodes[i] = pNodes[i];
    }
}

Continent::~Continent() {
    delete nodes;
    nodes = NULL;
}

/*
void Continent::addNode(Territory node) {
    nodeSize++;
    Territory *tempNodes = new Territory[nodeSize];

    for (int i = 0; i < nodeSize; i++) {
        if (i < nodeSize - 1) {
            tempNodes[i] = nodes[i];
        }
        else {
            tempNodes[i] = node;
        }
    }

    nodes = tempNodes;
    delete tempNodes;
}
*/

std::ostream& operator<<(std::ostream &strm, const Continent &continent) {
    string tempNodes = "";

    for (int i = 0; i < continent.nodeSize; i++) {
        tempNodes += " " + continent.nodes[i].name;
    }

    return strm <<
        "Continent( Name: " << continent.name <<
        ", Territories:" << tempNodes << " )";
}