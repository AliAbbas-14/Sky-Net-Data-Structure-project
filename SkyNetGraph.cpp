#include "SkyNetGraph.h"
#include "FileManager.h"
#include "Helper.h"
#include <iostream>
#include <climits>

using namespace std;

SkyNetGraph::SkyNetGraph() { headNode = nullptr; }

GraphNode* SkyNetGraph::findNode(string id) {
    GraphNode* temp = headNode;
    while (temp != nullptr) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

void SkyNetGraph::addNode(string id, char type, int x, int y) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
        setColor(COLOR_RED); cout << "Error: Coordinates out of bounds.\n"; setColor(COLOR_RESET); return;
    }
    if (findNode(id) != nullptr) {
        cout << "Node " << id << " already exists.\n"; return;
    }
    GraphNode* newNode = new GraphNode(id, type, x, y);
    newNode->next = headNode;
    headNode = newNode;
    cout << "Node " << id << " added.\n";
}

void SkyNetGraph::addEdge(string srcId, string destId, int weight) {
    GraphNode* src = findNode(srcId);
    GraphNode* dest = findNode(destId);
    if (!src || !dest) { cout << "Invalid Node IDs.\n"; return; }

    Edge* newEdge = new Edge(dest, weight);
    newEdge->next = src->headEdge;
    src->headEdge = newEdge;
    cout << "Path: " << srcId << " -> " << destId << " (" << weight << "km)\n";
}

// --- MODULE E START ---

// Helper: toggle occupation status (Simulates a plane moving into a sector)
void SkyNetGraph::setOccupation(string id, bool status) {
    GraphNode* node = findNode(id);
    if (node) {
        node->isOccupied = status;
        if (status) {
            setColor(COLOR_RED); cout << "ALERT: Sector " << id << " is now OCCUPIED.\n"; setColor(COLOR_RESET);
        }
        else {
            setColor(COLOR_GREEN); cout << "Sector " << id << " is now CLEARED.\n"; setColor(COLOR_RESET);
        }
    }
    else {
        cout << "Node not found.\n";
    }
}

// Helper: Reset Dijkstra variables before running algo
void SkyNetGraph::resetDijkstraVars() {
    GraphNode* temp = headNode;
    while (temp != nullptr) {
        temp->dDist = INT_MAX;
        temp->dParent = nullptr;
        temp->visited = false;
        temp = temp->next;
    }
}

// Helper: Find unvisited node with smallest dDist (Manual Priority Queue replacement)
GraphNode* SkyNetGraph::getMinDistanceNode() {
    GraphNode* minNode = nullptr;
    int minVal = INT_MAX;

    GraphNode* temp = headNode;
    while (temp != nullptr) {
        if (!temp->visited && temp->dDist < minVal) {
            minVal = temp->dDist;
            minNode = temp;
        }
        temp = temp->next;
    }
    return minNode;
}

// CORE ALGORITHM: Dijkstra to find nearest Airport
void SkyNetGraph::findSafeRoute(string startNodeID) {
    GraphNode* startNode = findNode(startNodeID);
    if (!startNode) {
        setColor(COLOR_RED); cout << "Start node not found.\n"; setColor(COLOR_RESET); return;
    }

    // 1. Initialization
    resetDijkstraVars();
    startNode->dDist = 0;

    cout << "\nCALCULATING PATH TO NEAREST AIRPORT...\n";
    cout << "------------------------------------------\n";

    // 2. Dijkstra Loop
    while (true) {
        // Find unvisited node with smallest distance
        GraphNode* u = getMinDistanceNode();

        // If no reachable nodes left, break
        if (u == nullptr || u->dDist == INT_MAX) break;

        u->visited = true;

        // Relax neighbors
        Edge* e = u->headEdge;
        while (e != nullptr) {
            GraphNode* v = e->destination;
            if (!v->visited) {
                int newDist = u->dDist + e->weight;
                if (newDist < v->dDist) {
                    v->dDist = newDist;
                    v->dParent = u;
                }
            }
            e = e->next;
        }
    }

    // 3. Find the closest Airport (Type 'A')
    GraphNode* nearestAirport = nullptr;
    int shortestDist = INT_MAX;

    GraphNode* temp = headNode;
    while (temp != nullptr) {
        if (temp->type == 'A' && temp->dDist < shortestDist) {
            shortestDist = temp->dDist;
            nearestAirport = temp;
        }
        temp = temp->next;
    }

    if (nearestAirport == nullptr) {
        setColor(COLOR_RED); cout << "No reachable airport found!\n"; setColor(COLOR_RESET);
        return;
    }

    // 4. Reconstruct Path (Backtracking from Dest to Start)
    // We use a temporary simple stack (array) to reverse the order
    string pathStack[100]; // Assume max path length 100 for safety
    int top = 0;

    GraphNode* curr = nearestAirport;
    while (curr != nullptr) {
        pathStack[top++] = curr->id;
        curr = curr->dParent;
    }

    // 5. Print Path
    setColor(COLOR_CYAN);
    cout << "Start: " << startNodeID << endl;

    // Iterate stack backwards to print Forward path
    for (int i = top - 2; i >= 0; i--) { // Start from second to last (since last is startNode)
        cout << "  |\n  V\n";

        // Check Collision logic here!
        GraphNode* step = findNode(pathStack[i]);
        if (step->isOccupied) {
            setColor(COLOR_RED); cout << "[WARNING: " << step->id << " IS OCCUPIED!]"; setColor(COLOR_CYAN);
        }
        else {
            cout << step->id;
        }

        // Calculate distance segment if needed, but for now just structure
        cout << endl;
    }

    cout << "  |\n  V\n";
    cout << "Destination: Airport " << nearestAirport->id << " (Total Dist: " << shortestDist << "km)\n";
    cout << "------------------------------------------\n";
    setColor(COLOR_RESET);
}

// --- END MODULE E LOGIC ---

void SkyNetGraph::displayRadar() {
    // 1. Initialize Grid with Empty Sky
    char grid[GRID_SIZE][GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = '.';
        }
    }

    // 2. Populate Grid with Nodes
    GraphNode* temp = headNode;
    while (temp != nullptr) {
        // PRIORITY CHECK: If occupied, show 'P', otherwise show type ('A' or 'W')
        if (temp->isOccupied) {
            grid[temp->x][temp->y] = 'P'; // Plane
        }
        else {
            grid[temp->x][temp->y] = temp->type; // Airport/Waypoint
        }
        temp = temp->next;
    }

    // 3. Render to Console
    system("cls");
    setColor(COLOR_CYAN);
    cout << "================ SKYNET RADAR ================\n";
    cout << "   ";
    for (int j = 0; j < GRID_SIZE; j++) cout << j % 10 << " ";
    cout << endl;

    for (int i = 0; i < GRID_SIZE; i++) {
        setColor(COLOR_CYAN);
        cout << i % 10 << "  ";

        for (int j = 0; j < GRID_SIZE; j++) {
            char symbol = grid[i][j];

            // Set Colors based on symbol
            if (symbol == 'A') setColor(COLOR_YELLOW);       // Airport
            else if (symbol == 'W') setColor(COLOR_WHITE);   // Waypoint
            else if (symbol == 'P') setColor(COLOR_RED);     // PLANE (Occupied)
            else setColor(8); // Grey for empty sky

            cout << symbol << " ";
        }
        cout << endl;
    }
    setColor(COLOR_RESET);
    cout << "==============================================\n";
    cout << "Legend: [A] Airport  [W] Waypoint  [P] Plane\n";
}

void SkyNetGraph::saveToFile(string filename) {
    FileManager::saveNetwork(headNode, filename);
}

void SkyNetGraph::loadFromFile(string filename) {
    FileManager::saveNetwork(headNode, filename);
}