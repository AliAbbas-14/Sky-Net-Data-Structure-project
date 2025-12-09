#ifndef SKYNETGRAPH_H
#define SKYNETGRAPH_H

#include "GraphStructures.h"

// Radar Grid Size
const int GRID_SIZE = 20;

class SkyNetGraph {
private:
    GraphNode* headNode;

    // Helper
    GraphNode* findNode(string id);

    // Dijkstra Helpers
    GraphNode* getMinDistanceNode();
    void resetDijkstraVars();

    // Friend for saving
    friend class FileManager;

public:
    SkyNetGraph();

    // Basic Graph Ops
    void addNode(string id, char type, int x, int y);
    void addEdge(string srcId, string destId, int weight);
    void displayRadar();

    // --- MODULE E: COLLISION & PATHFINDING ---
    void setOccupation(string id, bool status); // Mark node as occupied/empty
    void findSafeRoute(string startNodeID);     // Run Dijkstra
    // -----------------------------------------

    void saveToFile(string filename);
    void loadFromFile(string filename);

    // Getter for Module A to expose head
    GraphNode* getHead() { return headNode; }
};

#endif