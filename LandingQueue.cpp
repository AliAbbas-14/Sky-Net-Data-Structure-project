#include "LandingQueue.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Constructor
LandingQueue::LandingQueue(int maxPlanes) {
    capacity = maxPlanes;
    currentSize = 0;
    timeCounter = 0;
    heapArray = new FlightNode[capacity];
}

// Destructor
LandingQueue::~LandingQueue() {
    delete[] heapArray;
}

// Swap Helper
void LandingQueue::swapNodes(int i, int j) {
    FlightNode temp = heapArray[i];
    heapArray[i] = heapArray[j];
    heapArray[j] = temp;
}

// Heapify Up (Bubble Up)
void LandingQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        // Priority Logic: Lower number = Higher Priority
        // Tie-Breaker: Lower ArrivalTime = Arrived Earlier (FIFO)
        bool needSwap = false;

        if (heapArray[index].priority < heapArray[parent].priority) {
            needSwap = true;
        }
        else if (heapArray[index].priority == heapArray[parent].priority) {
            if (heapArray[index].arrivalTime < heapArray[parent].arrivalTime) {
                needSwap = true;
            }
        }

        if (needSwap) {
            swapNodes(index, parent);
            index = parent;
        }
        else {
            break;
        }
    }
}

// Heapify Down (Bubble Down)
void LandingQueue::heapifyDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    // Check Left
    if (left < currentSize) {
        if (heapArray[left].priority < heapArray[smallest].priority) {
            smallest = left;
        }
        else if (heapArray[left].priority == heapArray[smallest].priority) {
            if (heapArray[left].arrivalTime < heapArray[smallest].arrivalTime) {
                smallest = left;
            }
        }
    }

    // Check Right
    if (right < currentSize) {
        if (heapArray[right].priority < heapArray[smallest].priority) {
            smallest = right;
        }
        else if (heapArray[right].priority == heapArray[smallest].priority) {
            if (heapArray[right].arrivalTime < heapArray[smallest].arrivalTime) {
                smallest = right;
            }
        }
    }

    if (smallest != index) {
        swapNodes(index, smallest);
        heapifyDown(smallest);
    }
}

// Requirement 1: Request Landing
void LandingQueue::requestLanding(string id, int priorityChoice, string statusDesc) {
    if (currentSize == capacity) {
        setColor(COLOR_RED);
        cout << "Error: Landing Queue is Full!\n";
        setColor(COLOR_RESET);
        return;
    }

    timeCounter++;

    // Insert at end
    heapArray[currentSize] = FlightNode(id, priorityChoice, statusDesc, timeCounter);
    heapifyUp(currentSize);
    currentSize++;

    setColor(COLOR_GREEN);
    cout << "Flight " << id << " added to landing queue (Priority " << priorityChoice << ").\n";
    setColor(COLOR_RESET);
}

// Helper for Loading from File
void LandingQueue::silentInsert(string id, int p, string s, int t) {
    if (currentSize == capacity) return;
    heapArray[currentSize] = FlightNode(id, p, s, t);
    heapifyUp(currentSize);
    currentSize++;
    // Sync clock to max time found
    if (t > timeCounter) timeCounter = t;
}

// Requirement 2: Process Landing (Extract Min)
void LandingQueue::processLanding() {
    if (currentSize == 0) {
        setColor(COLOR_RED);
        cout << "No flights waiting to land.\n";
        setColor(COLOR_RESET);
        return;
    }

    FlightNode topPlane = heapArray[0];

    // Move last to root and decrease size
    heapArray[0] = heapArray[currentSize - 1];
    currentSize--;

    heapifyDown(0);

    setColor(COLOR_YELLOW);
    cout << ">>> LANDING APPROVED <<<\n";
    cout << "Flight: " << topPlane.flightID << endl;
    cout << "Reason: " << topPlane.status << endl;
    cout << "Landed safely.\n";
    setColor(COLOR_RESET);
}

// Requirement 3: Emergency Override (Decrease Key)
void LandingQueue::emergencyOverride(string id, int newPriority, string newStatus) {
    int index = -1;
    for (int i = 0; i < currentSize; i++) {
        if (heapArray[i].flightID == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        setColor(COLOR_RED);
        cout << "Flight " << id << " not found in queue.\n";
        setColor(COLOR_RESET);
        return;
    }

    if (newPriority >= heapArray[index].priority) {
        cout << "New priority must be higher (lower number) to declare emergency.\n";
        return;
    }

    heapArray[index].priority = newPriority;
    heapArray[index].status = newStatus;

    setColor(COLOR_RED);
    cout << "EMERGENCY DECLARED: " << id << " updated to Priority " << newPriority << "!\n";
    setColor(COLOR_RESET);

    // Bubble up because priority number decreased (became more urgent)
    heapifyUp(index);
}

// Visual: Display List
void LandingQueue::displayQueue() {
    system("cls");
    setColor(COLOR_CYAN);
    cout << "============= LANDING QUEUE (MIN-HEAP) =============\n";
    if (currentSize == 0) {
        cout << " [Empty Sky - No Flights Waiting]\n";
    }
    else {
        cout << "* NEXT TO LAND: " << heapArray[0].flightID
            << " [Status: " << heapArray[0].status << "] *\n";
        cout << "----------------------------------------------------\n";
        cout << left << setw(10) << "Flight" << setw(20) << "Status" << "Priority\n";
        cout << "----------------------------------------------------\n";
        for (int i = 0; i < currentSize; i++) {
            cout << left << setw(10) << heapArray[i].flightID
                << setw(20) << heapArray[i].status
                << heapArray[i].priority << endl;
        }
    }
    cout << "====================================================\n";
    setColor(COLOR_RESET);
}