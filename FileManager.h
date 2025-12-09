#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include "GraphStructures.h"
#include "LandingQueue.h"
#include "Registry.h"
#include "FlightLog.h"
#include "Helper.h"
class FileManager {
private:
    static void saveAVLRec(LogNode* root, ofstream& out) {
        if (root != nullptr) {
            out << root->timestamp << " " << root->flightID << " " << root->status << endl;
            saveAVLRec(root->left, out);
            saveAVLRec(root->right, out);
        }
    }
public:
    // Save the entire graph to a file
    static void saveNetwork(GraphNode* head, string filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            setColor(COLOR_RED);
            cout << "Error: Could not open file for saving.\n";
            setColor(COLOR_RESET);
            return;
        }

        // 1. Count Nodes
        int count = 0;
        GraphNode* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        outFile << count << endl;

        // 2. Save Nodes
        temp = head;
        while (temp != nullptr) {
            outFile << temp->id << " " << temp->type << " " << temp->x << " " << temp->y << endl;
            temp = temp->next;
        }

        // 3. Save Edges
        outFile << "EDGES" << endl;
        temp = head;
        while (temp != nullptr) {
            Edge* e = temp->headEdge;
            while (e != nullptr) {
                outFile << temp->id << " " << e->destination->id << " " << e->weight << endl;
                e = e->next;
            }
            temp = temp->next;
        }

        outFile.close();
        setColor(COLOR_GREEN);
        cout << "Network data saved to " << filename << " successfully.\n";
        setColor(COLOR_RESET);
    }
    static void saveQueue(LandingQueue& queue, string filename) {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cout << "Error: Could not open file.\n"; return;
        }

        int count = queue.getSize();
        outFile << count << endl;

        FlightNode* arr = queue.getArray();
        for (int i = 0; i < count; i++) {
            outFile << arr[i].flightID << " " << arr[i].priority << " " << arr[i].arrivalTime << " " << arr[i].status << endl;
        }

        outFile.close();
        setColor(COLOR_GREEN); cout << "Landing Queue Saved.\n"; setColor(COLOR_RESET);
    }

    static void loadQueue(LandingQueue& queue, string filename) {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "No saved queue data found.\n"; return;
        }

        int count;
        inFile >> count;

        string id, status;
        int p, t;

        for (int i = 0; i < count; i++) {
            inFile >> id >> p >> t >> status;
            queue.silentInsert(id, p, status, t);
        }

        inFile.close();
        setColor(COLOR_GREEN); cout << "Landing Queue Loaded.\n"; setColor(COLOR_RESET);
    }
    static void saveRegistry(Registry& reg, string filename) {
        ofstream out(filename);
        if (!out.is_open()) { cout << "Save Error.\n"; return; }

        // We iterate through every bucket in the table
        for (int i = 0; i < reg.getSize(); i++) {
            HashNode* node = reg.getBucket(i);
            while (node != nullptr) {
                out << node->key << " " << node->value.model << " " << node->value.origin
                    << " " << node->value.destination << " " << node->value.fuelLevel
                    << " " << node->value.status << endl;
                node = node->next;
            }
        }
        out.close();
        setColor(COLOR_GREEN); cout << "Registry Database Saved.\n"; setColor(COLOR_RESET);
    }

    static void loadRegistry(Registry& reg, string filename) {
        ifstream in(filename);
        if (!in.is_open()) { cout << "No database file found.\n"; return; }

        string k, m, o, d, s;
        int f;
        while (in >> k >> m >> o >> d >> f >> s) {
            reg.registerFlight(k, Aircraft(m, o, d, f, s));
        }
        in.close();
        setColor(COLOR_GREEN); cout << "Registry Database Loaded.\n"; setColor(COLOR_RESET);
    }
    static void saveLogs(FlightLog& log, string filename) {
        ofstream out(filename);
        if (!out.is_open()) { cout << "Error saving logs.\n"; return; }

        saveAVLRec(log.root, out);

        out.close();
        setColor(COLOR_GREEN); cout << "Flight Logs Saved.\n"; setColor(COLOR_RESET);
    }

    static void loadLogs(FlightLog& log, string filename) {
        ifstream in(filename);
        if (!in.is_open()) { cout << "No log file found.\n"; return; }

        int t; string id, s;
        // Simple reading loop
        while (in >> t >> id >> s) {
            log.addLog(t, id, s);
        }

        in.close();
        setColor(COLOR_GREEN); cout << "Flight Logs Loaded.\n"; setColor(COLOR_RESET);
    }
};

#endif#pragma once
