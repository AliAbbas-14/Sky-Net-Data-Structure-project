#include "Registry.h"

// Constructor: Allocates the table
Registry::Registry(int size) {
    tableSize = size;
    table = new HashNode * [tableSize];

    // Initialize all buckets to nullptr
    for (int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

// Destructor: Cleans up all nodes
Registry::~Registry() {
    for (int i = 0; i < tableSize; i++) {
        HashNode* current = table[i];
        while (current != nullptr) {
            HashNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

// Hash Function: Sum of ASCII % TableSize
int Registry::hashFunction(string key) {
    int sum = 0;
    for (char c : key) {
        sum += int(c);
    }
    return sum % tableSize;
}

// Register (Insert)
void Registry::registerFlight(string flightID, Aircraft info) {
    int index = hashFunction(flightID);

    HashNode* newNode = new HashNode(flightID, info);

    // Collision Handling: Chaining (Insert at Head of Linked List)
    if (table[index] == nullptr) {
        table[index] = newNode;
    }
    else {
        // Collision occurred! Add to front.
        newNode->next = table[index];
        table[index] = newNode;
    }

    setColor(COLOR_GREEN);
    cout << "Flight " << flightID << " registered successfully.\n";
    setColor(COLOR_RESET);
}

// Search (O(1) on average)
void Registry::searchFlight(string flightID) {
    int index = hashFunction(flightID);
    HashNode* temp = table[index];

    cout << "\nSEARCHING DATABASE... ";

    // Traverse the linked list at this bucket
    while (temp != nullptr) {
        if (temp->key == flightID) {
            cout << "FOUND.\n";
            setColor(COLOR_CYAN);
            cout << "-----------------------------------\n";
            cout << "| Flight ID : " << temp->key << endl;
            cout << "| Model     : " << temp->value.model << endl;
            cout << "| Origin    : " << temp->value.origin << endl;
            cout << "| Dest      : " << temp->value.destination << endl;
            cout << "| Fuel      : " << temp->value.fuelLevel << "%" << endl;
            cout << "| Status    : " << temp->value.status << endl;
            cout << "-----------------------------------\n";
            setColor(COLOR_RESET);
            return;
        }
        temp = temp->next;
    }

    setColor(COLOR_RED);
    cout << "NOT FOUND.\n";
    setColor(COLOR_RESET);
}
void Registry::updateStatus(string flightID, string newStatus, int newFuel) {
    int index = hashFunction(flightID);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == flightID) {
            temp->value.status = newStatus;
            temp->value.fuelLevel = newFuel;
            setColor(COLOR_YELLOW);
            cout << "Update Success: " << flightID << " is now " << newStatus << ".\n";
            setColor(COLOR_RESET);
            return;
        }
        temp = temp->next;
    }

    setColor(COLOR_RED);
    cout << "Error: Flight " << flightID << " not found.\n";
    setColor(COLOR_RESET);
}