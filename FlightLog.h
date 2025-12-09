#ifndef FLIGHTLOG_H
#define FLIGHTLOG_H

#include <string>
#include <iostream>
#include "Helper.h"

using namespace std;

// AVL Tree Node
struct LogNode {
    int timestamp;      // Key (Arrival Time)
    string flightID;    // Value
    string status;      // Value (Landed/Crashed)

    int height;         // For balancing
    LogNode* left;
    LogNode* right;

    LogNode(int t, string id, string s) {
        timestamp = t;
        flightID = id;
        status = s;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class FlightLog {
private:
    LogNode* root;

    // AVL Helper Functions
    int getHeight(LogNode* n);
    int getBalance(LogNode* n);
    LogNode* rightRotate(LogNode* y);
    LogNode* leftRotate(LogNode* x);
    LogNode* insertRec(LogNode* node, int time, string id, string status);
    void inOrderRec(LogNode* root); // For printing report
    void destroyTree(LogNode* node);

    // Friend class for File I/O access
    friend class FileManager;

public:
    FlightLog();
    ~FlightLog();

    // Insert new log
    void addLog(int time, string flightID, string status);

    // Reporting (In-Order Traversal)
    void printReport();

    // Check if empty
    bool isEmpty() { return root == nullptr; }

    // Getter for File Manager
    LogNode* getRoot() { return root; }
};

#endif#pragma once
