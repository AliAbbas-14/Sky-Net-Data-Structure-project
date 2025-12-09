#ifndef LANDINGQUEUE_H
#define LANDINGQUEUE_H

#include <string>
#include "Helper.h"

using namespace std;

// Structure to represent a single flight in the queue
struct FlightNode {
    string flightID;
    int priority;    // 1 (Critical) to 4 (Low)
    string status;   // Description
    int arrivalTime; // Integer timestamp for FIFO logic on same priority

    // Constructors
    FlightNode() : flightID(""), priority(100), status(""), arrivalTime(0) {}
    FlightNode(string id, int p, string s, int time) {
        flightID = id;
        priority = p;
        status = s;
        arrivalTime = time;
    }
};

class LandingQueue {
private:
    FlightNode* heapArray; // Dynamic Array
    int capacity;          // Max array size
    int currentSize;       // Current items
    int timeCounter;       // Simulated clock for arrival order

    // Heap Logic Helpers
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swapNodes(int i, int j);

public:
    LandingQueue(int maxPlanes);
    ~LandingQueue();

    // Core Requirements
    void requestLanding(string id, int priorityChoice, string statusDesc);
    void processLanding(); // Extract-Min
    void emergencyOverride(string flightID, int newPriority, string newStatus); // Decrease-Key

    // Visualization
    void displayQueue();

    // File I/O Helpers (Getters for FileManager)
    int getSize() { return currentSize; }
    FlightNode* getArray() { return heapArray; }

    // Load Helper (Manual insert without display messages)
    void silentInsert(string id, int p, string s, int t);

    bool isEmpty() {
        return currentSize == 0;
    }
};

#endif#pragma once
