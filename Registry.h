#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <iostream>
#include "Helper.h"

using namespace std;
struct Aircraft {
    string model;       // e.g., Boeing 777
    string origin;      // e.g., LHE
    string destination; // e.g., JFK
    int fuelLevel;      // e.g., 85 (%)
    string status;      // e.g., "In-Air", "Landed", "Maintenance"

    // Default Constructor
    Aircraft() : model(""), origin(""), destination(""), fuelLevel(0), status("") {}

    // Parameterized Constructor
    Aircraft(string m, string o, string d, int f, string s)
        : model(m), origin(o), destination(d), fuelLevel(f), status(s) {
    }
};
struct HashNode {
    string key;         // Flight ID (e.g., "PK-786")
    Aircraft value;     // The data object
    HashNode* next;     // Pointer for collision handling

    HashNode(string k, Aircraft v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class Registry {
private:
    HashNode** table;   // Array of pointers (The Hash Table)
    int tableSize;      // Size of the array

    // The Core Hash Function
    int hashFunction(string key);

public:
    Registry(int size = 101);
    ~Registry();

    // Requirements
    void registerFlight(string flightID, Aircraft info);
    void searchFlight(string flightID);
    void updateStatus(string flightID, string newStatus, int newFuel);

    int getSize() { return tableSize; }
    HashNode* getBucket(int index) { return table[index]; }
};

#endif