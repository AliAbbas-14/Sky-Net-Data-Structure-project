#include <iostream>
#include "Helper.h"
#include "SkyNetGraph.h"
#include "LandingQueue.h"
#include "Registry.h"
#include "FlightLog.h"
#include "FileManager.h"
using namespace std;

void runModuleA(SkyNetGraph& atcSystem) {
    int choice;
    do {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "==========================================\n";
        cout << "      MODULE A: AIRSPACE CONTROL (GRAPH)  \n";
        cout << "==========================================\n";
        setColor(COLOR_WHITE);
        cout << "1. Add Airport/Waypoint\n";
        cout << "2. Add Flight Corridor (Edge)\n";
        cout << "3. View Radar Grid\n";
        cout << "4. Save Map Data\n";
        cout << "5. Load Map Data\n";
        cout << "0. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id; char type; int x, y;
            cout << "\n--- Add New Node ---\n";
            cout << "Enter ID (e.g., LHE): "; cin >> id;
            cout << "Enter Type (A for Airport, W for Waypoint): "; cin >> type;
            cout << "Enter X Coordinate (0-19): "; cin >> x;
            cout << "Enter Y Coordinate (0-19): "; cin >> y;
            atcSystem.addNode(id, type, x, y);
            system("pause");
            break;
        }
        case 2: {
            string src, dest; int w;
            cout << "\n--- Add Flight Corridor ---\n";
            cout << "Enter Source ID: "; cin >> src;
            cout << "Enter Destination ID: "; cin >> dest;
            cout << "Enter Distance (Weight): "; cin >> w;
            atcSystem.addEdge(src, dest, w);
            system("pause");
            break;
        }
        case 3:
            atcSystem.displayRadar();
            system("pause");
            break;
        case 4:
            atcSystem.saveToFile("network.txt");
            system("pause");
            break;
        case 5:
            atcSystem.loadFromFile("network.txt");
            system("pause");
            break;
        case 0:
            // Returns to Main Menu
            break;
        default:
            setColor(COLOR_RED);
            cout << "Invalid Option.\n";
            setColor(COLOR_RESET);
            system("pause");
        }
    } while (choice != 0);
}
void runModuleB(LandingQueue& q, FlightLog& history) {
    int choice;
    do {
        system("cls");
        setColor(COLOR_CYAN); cout << "=== MODULE B: PRIORITY LANDING ===\n"; setColor(COLOR_WHITE);
        cout << "1. Request Landing\n";
        cout << "2. Process Next Landing (Updates History)\n";
        cout << "3. Declare Emergency\n";
        cout << "4. View Queue\n";
        cout << "5. Save Queue\n";
        cout << "6. Load Queue\n";
        cout << "0. Back\nChoice: "; cin >> choice;

        if (choice == 1) {
            string i, s; int p; cout << "ID Prio(1-4): "; cin >> i >> p;
            s = (p == 1) ? "CRITICAL" : "Normal";
            q.requestLanding(i, p, s);
        }
        else if (choice == 2) {
            // INTEGRATION: Peek at who is landing, then process
            if (!q.isEmpty()) {
                FlightNode* plane = q.getArray(); // Peek at top (index 0)
                // Add to History (Timestamp is just a simulation counter for now)
                static int globalClock = 1000;
                history.addLog(globalClock++, plane[0].flightID, "Landed_Safely");
            }
            q.processLanding();
        }
        else if (choice == 3) { string i; cout << "ID: "; cin >> i; q.emergencyOverride(i, 1, "EMERGENCY"); }
        else if (choice == 4) q.displayQueue();
        else if (choice == 5) FileManager::saveQueue(q, "queue.txt");
        else if (choice == 6) FileManager::loadQueue(q, "queue.txt");

        if (choice != 0) system("pause");
    } while (choice != 0);
}
void runModuleC(Registry& reg) {
    int choice;
    do {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "==========================================\n";
        cout << "      MODULE C: AIRCRAFT REGISTRY (HASH)  \n";
        cout << "==========================================\n";
        setColor(COLOR_WHITE);
        cout << "1. Register New Aircraft\n";
        cout << "2. Search Aircraft (Flight ID)\n";
        cout << "3. Update Aircraft Status\n";
        cout << "4. Save Database\n";
        cout << "5. Load Database\n";
        cout << "0. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id, model, org, dst, stat;
            int fuel;
            cout << "\n--- New Registration ---\n";
            cout << "Enter Flight ID (e.g., PK-786): "; cin >> id;
            cout << "Enter Model (e.g., B-777): "; cin >> model;
            cout << "Enter Origin (e.g., LHE): "; cin >> org;
            cout << "Enter Destination (e.g., JFK): "; cin >> dst;
            cout << "Enter Fuel % (0-100): "; cin >> fuel;
            cout << "Enter Status (e.g., InAir): "; cin >> stat;

            Aircraft newPlane(model, org, dst, fuel, stat);
            reg.registerFlight(id, newPlane);
            system("pause");
            break;
        }
        case 2: {
            string id;
            cout << "\nEnter Flight ID to Search: "; cin >> id;
            reg.searchFlight(id);
            system("pause");
            break;
        }
        case 3: {
            string id, stat;
            int fuel;
            cout << "\n--- Update Status ---\n";
            cout << "Enter Flight ID: "; cin >> id;
            cout << "Enter New Status: "; cin >> stat;
            cout << "Enter New Fuel %: "; cin >> fuel;
            reg.updateStatus(id, stat, fuel);
            system("pause");
            break;
        }
        case 4:
            FileManager::saveRegistry(reg, "database.txt");
            system("pause");
            break;
        case 5:
            FileManager::loadRegistry(reg, "database.txt");
            system("pause");
            break;
        case 0:
            break;
        default:
            cout << "Invalid Option.\n";
            system("pause");
        }
    } while (choice != 0);
}
void runModuleD(FlightLog& log) {
    int choice;
    do {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "==========================================\n";
        cout << "      MODULE D: FLIGHT LOGS (AVL)         \n";
        cout << "==========================================\n";
        setColor(COLOR_WHITE);
        cout << "1. View Daily Report (In-Order Traversal)\n";
        cout << "2. Manually Add Log Entry\n";
        cout << "3. Save Logs\n";
        cout << "4. Load Logs\n";
        cout << "0. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            log.printReport();
            system("pause");
            break;
        case 2: {
            int t; string id, st;
            cout << "Enter Time (int): "; cin >> t;
            cout << "Enter Flight ID: "; cin >> id;
            cout << "Enter Result: "; cin >> st;
            log.addLog(t, id, st);
            cout << "Log Added.\n";
            system("pause");
            break;
        }
        case 3:
            FileManager::saveLogs(log, "logs.txt");
            system("pause");
            break;
        case 4:
            FileManager::loadLogs(log, "logs.txt");
            system("pause");
            break;
        case 0: break;
        default: cout << "Invalid.\n"; system("pause");
        }
    } while (choice != 0);
}
void runModuleE(SkyNetGraph& atc) {
    int choice;
    do {
        system("cls");
        setColor(COLOR_CYAN);
        cout << "==========================================\n";
        cout << "      MODULE E: COLLISION & NAV (DIJKSTRA)\n";
        cout << "==========================================\n";
        setColor(COLOR_WHITE);
        cout << "1. Calculate Safe Route (Dijkstra)\n";
        cout << "2. Toggle Sector Occupation (Simulate Traffic)\n";
        cout << "3. View Radar\n";
        cout << "0. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string startID;
            cout << "\nEnter Current Location (Node ID): "; cin >> startID;
            atc.findSafeRoute(startID);
            system("pause");
            break;
        }
        case 2: {
            string id; int status;
            cout << "\nEnter Node ID: "; cin >> id;
            cout << "Set Status (1 = Occupied, 0 = Empty): "; cin >> status;
            atc.setOccupation(id, (status == 1));
            system("pause");
            break;
        }
        case 3:
            atc.displayRadar();
            system("pause");
            break;
        case 0: break;
        default: cout << "Invalid.\n"; system("pause");
        }
    } while (choice != 0);
}
// ==========================================
//           MAIN HOME MENU
// ==========================================
int main()
{
    SkyNetGraph atcSystem;
    LandingQueue landingQueue(50);
    Registry registry(101);
    FlightLog historyLog;
    int mainChoice;
    do {
        system("cls");
        setColor(COLOR_YELLOW);
        cout << "==============================================\n";
        cout << "      SKYNET AIR TRAFFIC CONTROL SYSTEM       \n";
        cout << "==============================================\n";
        setColor(COLOR_WHITE);
        cout << "1. Airspace Control (Module A - Graph)\n";
        cout << "2. Landing Priority (Module B - Min-Heap)\n";
        cout << "3. Aircraft Registry (Module C - Hash Table)\n";
        cout << "4. Flight History (Module D - AVL Tree)\n";
        cout << "5. Navigation & Collision (Dijkstra)\n";
        cout << "0. Exit System\n";
        cout << "==============================================\n";
        cout << "Select Module: ";
        cin >> mainChoice;

        switch (mainChoice) {
        case 1:
            runModuleA(atcSystem);
            break;
        case 2:
            runModuleB(landingQueue, historyLog);
            break;
        case 3:
            runModuleC(registry);
            break;
        case 4:
            runModuleD(historyLog);
            break;
        case 5:
            runModuleE(atcSystem);
            break;
        case 0:
            cout << "Shutting down SkyNet...\n";
            break;
        default:
            cout << "Invalid selection.\n";
            system("pause");
        }

    } while (mainChoice != 0);

    return 0;
}