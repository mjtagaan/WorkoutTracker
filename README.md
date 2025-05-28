# 🏋️ Workout Buddy: Your Personal Fitness Tracker! 🏋️‍♀️

Welcome to **Workout Buddy**, a powerful and intuitive command-line application built in C++ to help you meticulously track and manage your fitness journey! Say goodbye to scattered notes and hello to organized workout logs. This program is designed to be your digital workout companion, allowing you to easily add, edit, delete, and display your exercises and sessions.

## 🌟 Features

Workout Buddy comes packed with essential functionalities to streamline your workout logging:

* **Comprehensive Exercise Logging**: Record detailed information for each exercise, including its name, the number of sets, and the repetitions and weight for each set.
* **Flexible Workout Management**:
    * **Add Exercises**: Seamlessly add new exercises to your current workout session.
    * **Edit Workouts**: Easily modify existing exercise entries to correct mistakes or adjust your plan.
    * **Delete Exercises**: Remove any unwanted exercises from your log with a simple command.
* **Clear Workout Overview**: Display a well-formatted summary of your current workout, including all logged exercises, sets, reps, and weights.
* **Persistent Data Storage**:
    * **Save Workouts**: Save your entire workout session, including all exercises and their details, to a text file for future reference.
    * **Load Workouts**: (While the UI mentions "Load Workout", the provided `WorkoutTracker.cpp` focuses on saving. Future versions could expand this functionality.)
* **Robust Input Validation**: The program includes extensive validation for all user inputs, ensuring data integrity. It handles:
    * Empty inputs
    * Invalid numeric formats
    * Out-of-range values for sets, reps, and weights
    * Correct date format (YYYY-MM-DD)
    * Prevention of empty workout titles
* **Error Handling**: Gracefully manages various errors, providing informative messages to the user.
* **User-Friendly Interface**: A simple, menu-driven command-line interface makes navigation straightforward and efficient.
* **File Overwrite Protection**: Warns the user if a workout file already exists and asks for confirmation before overwriting.

## 🛠️ Technologies Used

This application is developed using standard C++ and leverages several key libraries:

* `iostream`: For fundamental input and output operations.
* `fstream`: Enables robust file handling for saving and potentially loading workouts.
* `vector`: Utilized for dynamic arrays to store exercise repetitions and weights.
* `limits`: Used for numeric limits, aiding in input validation.
* `cctype`: For character handling, such as converting characters to lowercase for 'yes/no' prompts.
* `cmath`: Included for potential future mathematical calculations.
* `iomanip`: Essential for formatting the output, ensuring a clean and readable display of workout data.
* `cstdlib`: Provides general utilities, including the `exit()` function for program termination.
* `algorithm`: For various algorithms, such as `std::replace` used in filename sanitization.
* `sstream`: For string stream operations, crucial for parsing and validating user inputs.

## 🚀 Getting Started

Follow these simple steps to get Workout Buddy up and running on your system.

### Prerequisites

You'll need a C++ compiler installed on your machine. Popular choices include:
* **g++** (GNU C++ Compiler)
* **MinGW** (Minimalist GNU for Windows)
* **Visual C++** (part of Visual Studio)

### Compilation

Navigate to the directory where you saved `WorkoutTracker.cpp` in your terminal or command prompt and compile the source code.

**Example using g++:**

```bash
g++ WorkoutTracker.cpp -o WorkoutTracker
```

This command compiles the `WorkoutTracker.cpp` file and creates an executable named `WorkoutTracker` (or `WorkoutTracker.exe` on Windows).

### How to Run

Once compiled, you can run the program from your terminal:

```bash
./WorkoutTracker
```
*(On Windows, you might type `WorkoutTracker.exe`)*

## 🖥️ Usage

Upon launching the program, you will be greeted by the main menu:

```
======================================
    WORKOUT TRACKER/LOGGER
======================================

[1] Add Exercises for Workout
[2] Edit Workout
[3] Delete Exercise
[4] Display Current Workout
[5] Save Workout
[6] Exit Program

Enter your choice (1-6):
```

Follow the on-screen prompts to interact with the application.

* **Adding Exercises**: Select option `1`. You'll be asked for the workout title and date (only once per session), then the exercise name, number of sets, and then reps and weight for each set.
* **Editing Workouts**: Select option `2`. The program will list your current exercises, and you can choose which one to modify.
* **Deleting Exercises**: Select option `3`. A list of exercises will appear, allowing you to choose which one to remove.
* **Displaying Workouts**: Option `4` will show all exercises currently logged in your session.
* **Saving Workouts**: Option `5` saves your workout to a `.txt` file, named after your workout title and date (e.g., `MyWorkout_2024-05-28.txt`).
* **Exiting**: Option `6` gracefully exits the program.

The program will guide you through each step and handle various invalid inputs by prompting you to try again.

## 🤝 Contributing

While this is a personal project, I'm always open to feedback and suggestions! If you have ideas for improvements, new features, or find any bugs, feel free to reach out to me.

## 📜 License

This project is open-source and available under the **MIT License**. You are free to use, modify, and distribute the code, adhering to the terms of the license.

## ✍️ Owner/Author

This Workout Tracker/Logger program was crafted with dedication by:

**Michael Joseph Tagaan**

---

Thank you for checking out Workout Buddy! Happy tracking! 💪