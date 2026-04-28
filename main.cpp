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

const int MAX_WORKOUTS = 100;

struct Workout {
    string exercise;
    string date;
    int sets;
    int reps;
    double weight;
    string muscleGroup;
};

// Function prototypes
void displayMenu();

int main() {

    return 0;
}
