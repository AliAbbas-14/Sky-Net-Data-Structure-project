#ifndef GRAPHSTRUCTURES_H
#define GRAPHSTRUCTURES_H

#include <string>
#include <climits> // For INT_MAX
using namespace std;

// Forward declaration
struct GraphNode;

struct Edge {
    GraphNode* destination;
    int weight;
    Edge* next;

    Edge(GraphNode* dest, int w) {
        destination = dest;
        weight = w;
        next = nullptr;
    }
};

struct GraphNode {
    string id;
    char type;      // 'A' (Airport) or 'W' (Waypoint)
    int x, y;

    // ---  Collision & Pathfinding Variables ---
    bool isOccupied;        // TRUE if a plane is currently here
    int dDist;              // Dijkstra: Shortest distance from start
    GraphNode* dParent;     // Dijkstra: To reconstruct the path
    bool visited;           // Dijkstra: To mark processing
    // ----------------------------------------------

    Edge* headEdge;
    GraphNode* next;

    GraphNode(string _id, char _type, int _x, int _y) {
        id = _id;
        type = _type;
        x = _x;
        y = _y;
        isOccupied = false; // Default: Sky is empty
        dDist = INT_MAX;
        dParent = nullptr;
        visited = false;
        headEdge = nullptr;
        next = nullptr;
    }
};

#endif#pragma once
