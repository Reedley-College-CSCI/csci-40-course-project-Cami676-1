// CSCI-40 Final Project
// Author: Abhineet Singh

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
void removeWorkout(Workout list[], int &count);
void searchWorkout(Workout list[], int count);
void sortWorkout(Workout list[], int count);

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
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(10000, '\n');
    switch (choice) {
            case 1:
                addWorkout(workouts, count);
                break;
            case 2:
                displayAll(workouts, count);
                break;
            case 3:
                removeWorkout(workouts, count);
                break;
            case 4:
                searchWorkout(workouts, count);
                break;
            case 5:
                sortWorkout(workouts, count);
                break;
            case 6:
                saveToFile(workouts, count);
                cout << "Workouts saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

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
    while (true) {
        bool valid = true;

        if (w.date.length() != 10) {
            valid = false;
        }

        if (valid && (w.date[2] != '-' || w.date[5] != '-')) {
            valid = false;
        }

        if (valid) {
            for (int i = 0; i < 10; i++) {
                if (i == 2 || i == 5) {
                    continue;
                }
                if (!isdigit(w.date[i])) {
                    valid = false;
                }
            }
        }

        if (valid) {
            int month = stoi(w.date.substr(0, 2));
            int day = stoi(w.date.substr(3, 2));
            int year = stoi(w.date.substr(6, 4));

            if (month < 1 || month > 12) {
                valid = false;
            }
            if (day < 1 || day > 31) {
                valid = false;
            }
            if (year < 1900 || year > 2100) {
                valid = false;
            }
        }

        if (valid) {
            break;
        }

        cout << "Invalid date format. Please use MM-DD-YYYY.\n";
        cout << "Enter date (MM-DD-YYYY): ";
        getline(cin, w.date);
    }
    cout << "Enter number of sets: ";
    cin >> w.sets;
    while (cin.fail() || w.sets <= 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cout << "Sets must be positive. Try again: ";
        }
        cin >> w.sets;
    }
    cout << "Enter number of reps: ";
    cin >> w.reps;
    while (cin.fail() || w.reps <= 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cout << "Reps must be positive. Try again: ";
        }
        cin >> w.reps;
    }

    cout << "Enter weight (lbs): ";
    cin >> w.weight;
    while (cin.fail() || w.weight < 0) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else {
            cout << "Weight cannot be negative. Try again: ";
        }
        cin >> w.weight;
    }
    cin.ignore(10000, '\n');

    cout << "Enter muscle group: ";
    getline(cin, w.muscleGroup);

    list[count] = w;
    count++;
    cout << "Workout added.\n";
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
cout << string(70, '-') << "\n";    
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
    cout << "3. Remove a workout\n";
    cout << "4. Search workouts\n";
    cout << "5. Sort workouts\n";
    cout << "6. Save and Exit\n";
    cout << "Enter your choice: ";
}
void removeWorkout(Workout list[], int &count) {
    if (count == 0) {
        cout << "No workouts to remove.\n";
        return;
    }
displayAll(list, count);
    int index;
    cout << "Enter the entry number to remove (1 to " << count << "): ";
    cin >> index;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore(10000, '\n');
    if (index < 1 || index > count) {
        cout << "Invalid entry number.\n";
        return;
    }
    for (int i = index - 1; i < count - 1; i++) {
        list[i] = list[i + 1];
    }
    count--;
cout << "Workout removed.\n";
}
void searchWorkout(Workout list[], int count) {
    if (count == 0) {
        cout << "No workouts to search.\n";
        return;
    }

    int searchChoice;
    cout << "Search by:\n";
    cout << "1. Exercise name\n";
    cout << "2. Muscle group\n";
    cout << "Enter your choice: ";
    cin >> searchChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore(10000, '\n');

    string keyword;
    cout << "Enter search keyword: ";
    getline(cin, keyword);

    int found = 0;
    for (int i = 0; i < count; i++) {
        bool match = false;
        if (searchChoice == 1 && list[i].exercise.find(keyword) != string::npos) {
            match = true;
        }
        else if (searchChoice == 2 && list[i].muscleGroup.find(keyword) != string::npos) {
            match = true;
        }

        if (match) {
            cout << "Match: " << list[i].exercise << " | " << list[i].date
                 << " | " << list[i].sets << " sets x " << list[i].reps
                 << " reps @ " << list[i].weight << " lbs | "
                 << list[i].muscleGroup << "\n";
            found++;
        }
    }
    if (found == 0) {
        cout << "No matches found.\n";
    } else {
        cout << found << " match(es) found.\n";
    }
}
void sortWorkout(Workout list[], int count) {
    if (count == 0) {
        cout << "No workouts to sort.\n";
        return;
    }

    int sortChoice;
    cout << "Sort by:\n";
    cout << "1. Date\n";
    cout << "2. Weight\n";
    cout << "Enter your choice: ";
    cin >> sortChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number.\n";
        return;
    }
    cin.ignore(10000, '\n');

    if (sortChoice != 1 && sortChoice != 2) {
        cout << "Invalid choice.\n";
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        int smallest = i;
        for (int j = i + 1; j < count; j++) {
            if (sortChoice == 1 && list[j].date < list[smallest].date) {
                smallest = j;
            }
            else if (sortChoice == 2 && list[j].weight < list[smallest].weight) {
                smallest = j;
            }
        }

        if (smallest != i) {
            Workout temp = list[i];
            list[i] = list[smallest];
            list[smallest] = temp;
        }
    }

    cout << "Workouts sorted.\n";
    displayAll(list, count);
}