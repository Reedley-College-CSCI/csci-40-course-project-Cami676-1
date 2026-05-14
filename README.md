[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ay551EX-)
# CS1 Final Project - [Gym Progress Tracker]

## 1. Overview
- What problem does your project solve?  
- Briefly describe the purpose and key features of your program.  
This project is a Gym Progress Tracker built in C++ that lets users log and manage their workouts through a menu-based console program. The problem it solves is keeping an organized record of training sessions without needing a spreadsheet or a third-party app.

Key features:
- Add new workout entries with exercise name, date, sets, reps, weight, and muscle group
- Display all logged workouts in a formatted table
- Remove an entry by selecting its number
- Search workouts by exercise name or muscle group
- Sort workouts by date or weight
- Save data to a text file so workouts persist between program runs

---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why? 
The program uses fundamental constructs for ex. arrays, structs, loops, conditionals, switch-case statements, file I/O with fstrim, and modular functions. Strings are used for text fields, integers for sets and reps, and a double for weight.

- Why did you choose to structure your data using structs? 
Each workout has six related pieces of data that describe one thing. Grouping them in a struct keeps the code organized and lets one Workout variable be passed around instead of six separate varables. The array of struts makes it easy to manage multiple workouts.

- How did you implement searching and sorting? What algorithms did you use and why? 
Linear search is used because the array is not guaranteed to be sorted, and linear search works on unordered data. The search uses `string::find` to support substring matching so partial keywords like "Bench" still match "Bench Press." Selection sort is used for sorting because it is simple to implement and efficient enough for a small array of up to 100 entries.


- How do you ensure data persistence between program runs? 
Workouts are stored in a text file (`workouts.txt`). On program startup, `loadFromFile` reads the file into the array. On exit, `saveToFile` writes the array back to the file. This way data is never lost between sessions.

- Did you consider alternative approaches? If so, why did you not use them? 
A vector could have replaced the fixed array, but the project requirements specify no STL containers. A binary search would be faster than linear search but requires sorted data, and since the user can sort by either date or weight, the array isn't always in the right order for the search field.


---

## 3. Testing Summary
- **Structured Testing Log:** Include a table with test cases, expected output, actual output, and pass/fail status.  

| Test Case | Input | Expected Output | Actual Output | Pass/Fail |
|-----------|-------|-----------------|---------------|-----------|
| Add valid workout | Bench Press, 04-28-2026, 3, 10, 135, Chest | Workout added confirmation | Workout added. | Pass |
| Add with negative sets | -1 for sets | Reprompt for valid input | "Sets must be positive. Try again:" | Pass |
| Add with non-numeric sets | "abc" for sets | Reprompt for number | "Invalid input. Please enter a number." | Pass |
| Add with negative weight | -50 for weight | Reprompt for valid input | "Weight cannot be negative. Try again:" | Pass |
| Add with invalid date | "asdf" for date | Reprompt with format hint | "Invalid date format. Please use MM-DD-YYYY." | Pass |
| Add with month 13 | "13-05-2026" | Reprompt with format hint | "Invalid date format. Please use MM-DD-YYYY." | Pass |
| Type letter at menu | "a" at menu choice | Error and reprompt | "Invalid input. Please enter a number." | Pass |
| Display when empty | No workouts logged | "No workouts to display." | No workouts to display. | Pass |
| Save and reload | Add 2 workouts, exit, restart | 2 workouts loaded from file | 2 workout(s) loaded from file. | Pass |
| Remove valid entry | Index 1 of 2 entries | Entry removed, 1 remaining | Workout removed. | Pass |
| Remove invalid index | Index 99 of 2 entries | "Invalid entry number." | Invalid entry number. | Pass |
| Search partial match | "Bench" when "Bench Press" exists | Match displayed | Match: Bench Press... | Pass |
| Search no match | "Yoga" with no matching entries | "No matches found." | No matches found. | Pass |
| Sort by weight | Multiple entries, varying weights | Entries sorted ascending | Workouts sorted and displayed | Pass |
| Sort by date | Multiple entries, varying dates | Entries sorted | Workouts sorted and displayed | Pass |
| Invalid menu choice | 99 | Error message | Invalid choice. Try again. | Pass |

- What testing methods did you use?  
Manual testing was used throughout development. After each feature was added, the program was compiled and run with both valid and invalid inputs to confirm the new function worked correctly and didn't break existing functionality. Several bugs were caught through this testing process and fixed in dedicated commits.
- Provide examples of test inputs (valid and invalid) and describe how your program responds.  
Valid inputs include realistic workout data with positive numbers, proper date strings in MM-DD-YYYY format, and menu choices within range. Invalid inputs cover negative numbers, zero, non-numeric characters at numeric prompts, malformed dates with bad lengths or out-of-range months and days, and out-of-range menu choices. The program responds to invalid input by reprompting or returning with a clear error message rather than crashing or entering an infinite loop.
---

## 4. Technical Walkthrough

The program starts in `main` by calling `loadFromFile` to populate the workout array from a saved text file. It then enters a do-while loop that displays the menu, reads the user's choice, and dispatches to the right function using a switch-case.

Each function handles one part of the program:

- `addWorkout` prompts for every field and validates the date format and numeric values before storing the entry in the array
- `displayAll` prints all entries in a formatted table using `setw` from iomanip for column alignment
- `removeWorkout` shows the list, prompts for an index, and shifts the array down to delete the chosen entry
- `searchWorkout` uses linear search with `string::find` so partial keywords still match — for example, "Bench" will find "Bench Press"
- `sortWorkout` uses selection sort to reorder entries by date or weight
- `saveToFile` writes the array back to `workouts.txt` when the user exits through the menu

The program also handles input failure across every numeric prompt. If a user types a letter where a number is expected, the program detects the cin failure, clears the error state, flushes the buffer, prints an error message, and continues without crashing or looping forever.

**Video Demonstration:** [-]

---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?  
One challenge came up right at the start when I pasted the file I/O functions inside main() by accident. C++ doesn't allow nested function definitions so the program wouldn't compile. Moving them out as standalone functions fixed it but taught me to pay closer attention to scope and structure early on.
A bigger issue was reading mixed string and numeric data from the file. After reading the numeric fields with the extraction operator, a leftover newline character would mess up the next getline and the muscle group field would load as empty. The fix was adding inFile.ignore() between the numeric read and the getline for muscle group.
The most frustrating bug was when typing a letter at a numeric prompt sent the program into an infinite loop. It turned out that cin enters a fail state when it can't parse the input, and the bad character stays stuck in the buffer. Every future read instantly fails. The fix was to add a cin.fail() check after every numeric input, then call cin.clear() and cin.ignore(10000, '\n') to recover.
A related bug happened with cin.ignore() alone, which only skips one character. Typing something like "1 2" at the menu left the "2" in the buffer and the next getline picked it up instead of waiting for input. Switching every cin.ignore() to cin.ignore(10000, '\n') flushed the buffer properly.
- What key lessons did you learn about programming and problem-solving?  
Building feature by feature with frequent commits made debugging much easier than writing everything at once. Each commit gave me a stable version to test, and when something broke I knew exactly where to look. Input validation needs to be designed into a function from the start rather than added later, especially around cin, which has tricky behavior with mixed string and numeric input. And file read/write formats have to match exactly or the program ends up breaking itself when loading its own saved data.

---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?  
If I had more time, I would add:

- **Editing existing entries** instead of having to remove and re-add a workout to fix a typo or update progress
- **Stats summaries** like total volume per muscle group, personal records per exercise, or weekly workout counts
- **Date format switch to YYYY-MM-DD** so sorting by date works chronologically. The current MM-DD-YYYY format sorts by month first when compared as a string, so January 2027 would come before December 2026
- **Case-insensitive search** so typing "bench" matches "Bench Press" without needing exact capitalization
- **Sorting by additional fields** like sets, reps, or exercise name in alphabetical order
- **Real date validation** including checking the correct number of days per month and leap years, instead of just allowing any day from 1 to 31
- **Ascending and descending sort options** so the user can pick the order
