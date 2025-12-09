✈️ SkyNet Air Traffic Control (ATC) Simulator
📌 Overview

SkyNet ATC Simulator is a console-based C++ application developed as a semester project for the Data Structures course.
The system simulates real-world air traffic control operations such as aircraft tracking, priority-based landings, emergency handling, and collision avoidance — using manually implemented data structures (no STL).

🎯 Objectives

Simulate a busy airspace with real-time aircraft movement

Apply core data structures to a critical real-world system

Handle emergencies and prioritize aircraft landings

Ensure efficient searching, routing, and historical logging

Visualize airspace using a live console-based radar

🛠️ Technologies Used

Language: C++ (C++11 or higher)

Environment: Console Application

Restrictions: No use of STL containers for core data structures

🧠 Data Structures & Algorithms
✅ Module A: Airspace Management

Data Structure: Weighted Directed Graph (Adjacency List)

Algorithm: Dijkstra’s Algorithm

Purpose:

Represent airports & waypoints

Compute shortest/safest path to nearest airport

Visualization: 20×20 Radar Grid

A → Airport

P → Plane

. → Empty Space

✅ Module B: Landing Priority System

Data Structure: Min-Heap (Array-Based)

Purpose: Priority-based aircraft landing

Landing Priorities:

Priority	Type
1	Emergency (Medical, Engine Failure)
2	Low Fuel
3	Commercial Flight
4	Cargo / Private

Operations:

Insert (Request Landing)

ExtractMin (Land Aircraft)

DecreaseKey (Emergency Override)

✅ Module C: Aircraft Registry

Data Structure: Hash Table with Chaining

Key: Flight ID (String)

Operations:

Instant search – O(1)

Update aircraft status

Hash Function:

Sum of ASCII values of Flight ID % Table Size

✅ Module D: Flight Log History

Data Structure: AVL Tree (Self-Balancing BST)

Key: Arrival Timestamp

Purpose:

Maintain permanent flight records

Ensure balanced tree using rotations (LL, RR, LR, RL)

Traversal: In-order (Chronological Report)

✅ Module E: Collision Avoidance

Prevents two planes from occupying the same graph node or radar cell

Holds aircraft or alerts the controller when conflict is detected

🎮 System Features

Real-time Radar Visualization

Emergency handling & rerouting

Priority-based aircraft landing

Fast flight search using Flight ID

Chronological flight history logs

Collision detection

Save & Load functionality using file handling

📋 Menu Options

Airspace Visualizer

Display Radar Grid

View next landing aircraft

Flight Control

Add Flight

Declare Emergency

Land Flight

Search & Reporting

Search Flight by ID

Print Flight Log

Find Safe Route (Dijkstra)

System

Save / Load Data

💾 File Handling

Uses file I/O to persist:

Aircraft Registry (Hash Table)

Flight Logs (AVL Tree)

Data remains available after system restart

⚙️ How to Run
g++ main.cpp -o SkyNet
./SkyNet


(Use system("cls") for Windows or system("clear") for Linux/macOS)

📈 Time Complexity Overview
Component	Complexity
Hash Search	O(1)
Heap Operations	O(log n)
AVL Insert/Search	O(log n)
Dijkstra’s Algorithm	O(V²)
Semester Project – Data Structures

📌 Key Learning Outcomes

Hands-on implementation of core data structures

Understanding real-time systems like ATC

Efficient algorithm design under constraints

System design without STL abstraction

📜 License

This project is created for educational purposes only.
