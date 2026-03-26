// thanks anas

#include "starter.h"
#include <fstream>
#include <iostream>
using namespace std;

// Saves player stats to file
void saveStats(const Player& p) {
    ofstream outFile("stats.txt");

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    // Simple text format: name wins losses
    outFile << p.name << endl;
    outFile << p.wins << endl;
    outFile << p.losses << endl;

    outFile.close();
}

// Loads player stats from file
void loadStats(Player& p) {
    ifstream inFile("stats.txt");

    if (!inFile) {
        cout << "No stats file found. Starting fresh.\n";
        return;
    }

    // Read in same order as saved
    getline(inFile, p.name);
    inFile >> p.wins;
    inFile >> p.losses;

    inFile.close();
}
