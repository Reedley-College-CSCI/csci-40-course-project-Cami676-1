[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Ay551EX-)
# CS1 Final Project - [Project Title]

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
- What testing methods did you use?  
- Provide examples of test inputs (valid and invalid) and describe how your program responds.  

---

## 4. Technical Walkthrough
- Explain the main functionality of your program.  
- **Include a link to your required video demonstration** showcasing how the project works (**3-7 minutes**). 
    Make sure it shareable without approval needed.

---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?  
- What key lessons did you learn about programming and problem-solving?  

---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?  
