// CSCI-40 Final Project
// Author: Abhineet SIngh

/*
 * Description:
 *A C++ program that lets users log and manage their gym workouts.
 * Each workout entry stores the exercise name, date, sets, reps,
 * weight lifted, and muscle group, grouped together using a struct.
 * Entries are held in arrays and saved to a file so data persists
 * between program runs.
 *
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_WORKOUTS = 100;
const string FILE_NAME = "workouts.txt";

struct Workout {
    string exercise;
    string date;
    int sets;
    int reps;
    double weight;
    string muscleGroup;
};

void displayMenu();
int loadFromFile(Workout list[]);
void saveToFile(Workout list[], int count);

int main(){

    Workout workouts[MAX_WORKOUTS];
    int count = 0;
    int choice;

    count = loadFromFile(workouts);
    cout << "Welcome to the Gym Progress Tracker\n";
    cout << count << " workout(s) loaded from file.\n";

    return 0;
}

int loadFromFile(Workout list[]) {
    ifstream inFile(FILE_NAME);
    int count = 0;

    if (!inFile) {
        return 0;
    }

    while (count < MAX_WORKOUTS &&
           getline(inFile, list[count].exercise) &&
           getline(inFile, list[count].date) &&
           inFile >> list[count].sets >> list[count].reps >> list[count].weight) {
        inFile.ignore();
        getline(inFile, list[count].muscleGroup);
        count++;
    }

    inFile.close();
    return count;
}

void saveToFile(Workout list[], int count) {
    ofstream outFile(FILE_NAME);

    for (int i = 0; i < count; i++) {
        outFile << list[i].exercise << "\n";
        outFile << list[i].date << "\n";
        outFile << list[i].sets << " " << list[i].reps << " " << list[i].weight << "\n";
        outFile << list[i].muscleGroup << "\n";
    }

    outFile.close();
}
