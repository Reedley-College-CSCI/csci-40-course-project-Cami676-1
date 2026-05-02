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
//function prototypes
void displayMenu();
int loadFromFile(Workout list[]);
void saveToFile(Workout list[], int count);
void addWorkout(Workout list[], int &count);
void displayAll(Workout list[], int count);

int main(){

    Workout workouts[MAX_WORKOUTS];
    int count = 0;
    int choice;

    count = loadFromFile(workouts);
    cout << "Welcome to the Gym Progress Tracker\n";
    cout << count << " workout(s) loaded from file.\n";
    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addWorkout(workouts, count);
                break;
            case 2:
                displayAll(workouts, count);
                break;
            case 3:
                saveToFile(workouts, count);
                cout << "Workouts saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

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

void addWorkout(Workout list[], int &count) {
    if (count >= MAX_WORKOUTS) {
        cout << "Workout list is full.\n";
        return;
    }
Workout w;
    cout << "Enter exercise name: ";
    getline(cin, w.exercise);

    cout << "Enter date (MM-DD-YYYY): ";
    getline(cin, w.date);

    cout << "Enter number of sets: ";
    cin >> w.sets;
    while (w.sets <= 0) {
        cout << "Sets must be positive. Try again: ";
        cin >> w.sets;
    }
    cout << "Enter number of reps: ";
    cin >> w.reps;
    while (w.reps <= 0) {
        cout << "Reps must be positive. Try again: ";
        cin >> w.reps;
    }

    cout << "Enter weight (lbs): ";
    cin >> w.weight;
    while (w.weight < 0) {
        cout << "Weight cannot be negative. Try again: ";
        cin >> w.weight;
    }
}
void displayAll(Workout list[], int count) {
    if (count == 0) {
        cout << "No workouts to display.\n";
        return;
    }

    cout << "\n";
    cout << left;
    cout << setw(20) << "Exercise";
    cout << setw(14) << "Date";
    cout << setw(6) << "Sets";
    cout << setw(6) << "Reps";
    cout << setw(10) << "Weight";
    cout << "Muscle Group\n";
    cout << "----------------------------------------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << setw(20) << list[i].exercise;
        cout << setw(14) << list[i].date;
        cout << setw(6) << list[i].sets;
        cout << setw(6) << list[i].reps;
        cout << setw(10) << list[i].weight;
        cout << list[i].muscleGroup << "\n";
    }
}
void displayMenu() {
    cout << "\n--- Menu ---\n";
    cout << "1. Add a new workout\n";
    cout << "2. Display all workouts\n";
    cout << "3. Save and Exit\n";
    cout << "Enter your choice: ";
}