#include "FlightLog.h"
#include <iomanip>

// Constructor
FlightLog::FlightLog() {
    root = nullptr;
}

// Destructor
FlightLog::~FlightLog() {
    destroyTree(root);
}

void FlightLog::destroyTree(LogNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// --- AVL HELPERS ---

int FlightLog::getHeight(LogNode* n) {
    if (n == nullptr) return 0;
    return n->height;
}

int FlightLog::getBalance(LogNode* n) {
    if (n == nullptr) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

// Right Rotation (LL Case)
LogNode* FlightLog::rightRotate(LogNode* y) {
    LogNode* x = y->left;
    LogNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // New root
}

// Left Rotation (RR Case)
LogNode* FlightLog::leftRotate(LogNode* x) {
    LogNode* y = x->right;
    LogNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // New root
}

// --- CORE INSERTION ---

LogNode* FlightLog::insertRec(LogNode* node, int time, string id, string status) {
    // 1. Normal BST Insertion
    if (node == nullptr)
        return new LogNode(time, id, status);

    if (time < node->timestamp)
        node->left = insertRec(node->left, time, id, status);
    else if (time > node->timestamp)
        node->right = insertRec(node->right, time, id, status);
    else {
        // Duplicate timestamps: Insert to right to maintain chronological order
        // (In real systems we might use a list, but here we just shift it slightly)
        node->right = insertRec(node->right, time, id, status);
    }

    // 2. Update Height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. Get Balance Factor
    int balance = getBalance(node);

    // 4. Balance the Tree (4 Cases)

    // Left Left Case
    if (balance > 1 && time < node->left->timestamp)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && time > node->right->timestamp)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && time > node->left->timestamp) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && time < node->right->timestamp) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Public Wrapper for Insertion
void FlightLog::addLog(int time, string flightID, string status) {
    root = insertRec(root, time, flightID, status);
}

// --- REPORTING ---

void FlightLog::inOrderRec(LogNode* root) {
    if (root != nullptr) {
        inOrderRec(root->left);

        // Print Node
        cout << "[Time: " << setw(4) << root->timestamp << "] Flight "
            << setw(8) << root->flightID << " -> " << root->status << endl;

        inOrderRec(root->right);
    }
}

void FlightLog::printReport() {
    system("cls");
    setColor(COLOR_CYAN);
    cout << "============= DAILY FLIGHT LOG (AVL TREE) =============\n";
    cout << "Ordered Chronologically by Arrival Time\n";
    cout << "-------------------------------------------------------\n";
    setColor(COLOR_WHITE);

    if (root == nullptr) {
        cout << "Log is empty.\n";
    }
    else {
        inOrderRec(root);
    }

    setColor(COLOR_CYAN);
    cout << "=======================================================\n";
    cout << "> End of Report.\n";
    setColor(COLOR_RESET);
}