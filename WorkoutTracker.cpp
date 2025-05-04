#include <iostream> // For the basic input and output functions.
#include <fstream> // For file handling.
#include <vector> // For handling dynamic inputs.	
#include <limits> // Limits library to add min/max value.
#include <cctype> // Include cctype library for character handling.
#include <cmath> // For future calculations.
#include <iomanip> // Include iomanip library for formatting output.
#include <cstdlib> // For the exit() function.
#include <algorithm> // For std::replace
#include <sstream> // For string stream operations

 /* Struct to represent the main menu and its associated functions. */

struct mainmenu { 

    /* Everything that happens within the main menu/display
       Function to serve as the back door to get back to the main menu. */

    /* Function to serve as the layout/default main menu when the program is launched. */

    void ui() {
        while (true) {
            try {
                int choice;
                std::cout << "======================================" << "\n";
                std::cout << "\t" << "WORKOUT TRACKER/LOGGER" << "\n";
                std::cout << "======================================" << "\n\n";
                std::cout << "[1] Add Exercises for Workout" << "\n";
                std::cout << "[2] Edit Workout" << "\n";
                std::cout << "[3] Delete Exercise" << "\n";
                std::cout << "[4] Display Current Workout" << "\n";
                std::cout << "[5] Save Workout" << "\n";
                std::cout << "[6] Exit Program" << "\n\n";
                std::cout << "Enter your choice (1-6): ";

                std::string input;
                std::getline(std::cin, input);

                // Check for empty input
                if (input.empty()) {
                    throw std::invalid_argument("Empty input. Please enter a number (1-6).");
                }

                // Try to convert input to integer
                std::istringstream iss(input);
                if (!(iss >> choice) || !iss.eof()) {
                    throw std::invalid_argument("Invalid input. Please enter a number (1-6).");
                }

                // Check if number is in valid range
                if (choice < 1 || choice > 6) {
                    throw std::out_of_range("Invalid choice. Please enter a number between 1 and 6.");
                }

                system("cls");
            
                switch(choice) {
                    case 1:
                        workout();
                        addExercise();
                        break;
                    case 2:
                        workout();
                        editExercise();
                        repUi();
                        break;
                    case 3:
                        workout();
                        deleteExercise();
                        repUi();
                        break;
                    case 4:
                        displayCurrentWorkout(workoutTitle, workoutDate);
                        repUi();
                        break;
                    case 5:   
                        saveWorkoutToFile();
                        std::cout << "\nThank you for using the program!";
                        exit(0);
                        break;
                    case 6: 
                        system("cls");
                        std::cout << "=================================================\n";
                        std::cout << "              WORKOUT TRACKER/LOGGER              \n";
                        std::cout << "=================================================\n\n";
                        std::cout << "                Thank you for using               \n";
                        std::cout << "                the Workout Tracker!               \n\n";
                        std::cout << "                   See you soon!                  \n";
                        std::cout << "=================================================\n";
                        exit(0);
                        break;
                }
            } catch (const std::exception& e) {
                system("cls");
                std::cout << "Error: " << e.what() << "\n\n";
            }
        }
    };

    /* Struct to represent an exercise with its attributes.
       Includes title, date, name, sets, repetitions, and weights for each set. */

    private:
    struct Exercise {
        std::string title; // Title of the workout
        std::string date; // Date of the workout
        std::string name; // Name of the exercise
        int sets; // Number of sets for the exercise
        std::vector<int> reps; // Vector to hold repetitions for each set
        std::vector<float> weights; // Vector to hold weight for each set
    };

    // Vector to store all exercises
    
    std::vector<Exercise> exercises;
    std::string workoutTitle;
    std::string workoutDate;

    // Utility function for safe numeric input
    template<typename T>
    T getNumericInput(const std::string& prompt, T min_val, T max_val) {
        while (true) {
            try {
                std::cout << prompt;
                std::string input;
                std::getline(std::cin, input);
                
                if (input.empty()) {
                    throw std::invalid_argument("Empty input");
                }
                
                T value;
                std::istringstream iss(input);
                if (!(iss >> value) || !iss.eof()) {
                    throw std::invalid_argument("Invalid number format");
                }
                
                if (value < min_val || value > max_val) {
                    throw std::out_of_range("Value out of allowed range");
                }
                
                return value;
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << ". Please try again.\n";
            }
        }
    }

    // Validate date format
    bool isValidDate(const std::string& date) {
        try {
            if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
                return false;
            }
            
            int year = std::stoi(date.substr(0, 4));
            int month = std::stoi(date.substr(5, 2));
            int day = std::stoi(date.substr(8, 2));
            
            // Check year range
            if (year < 1900 || year > 2100) return false;
            
            // Check month
            if (month < 1 || month > 12) return false;
            
            // Check days per month
            const int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
            int maxDays = daysInMonth[month-1];
            
            // Handle leap years
            if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) {
                maxDays = 29;
            }
            
            return day >= 1 && day <= maxDays;
        } catch (...) {
            return false;
        }
    }

    // Function to handle yes/no input from the user
    bool yesorno() {
        char choice;
        std::cout << "\nDo you want to continue? (y/n): ";
        std::cin >> choice;
        std::cout << "\n";
        std::cin.ignore(); // Clear newline character from input buffer
        return (tolower(choice) == 'y'); // Return true if 'y' or 'Y', false otherwise
    }

    // This function serves as the back door to get back to the main menu.
    void repUi () { 

        std::cout << "\nEnter [1] to return to the main menu. \n";
        std::cout << "Enter [2] to exit. \n\n";
            
        int mmex;
        std::cout << "Enter your choice: ";
        std::cin >> mmex;

        if (mmex == 1) {
            system("cls");
            ui();
        } else if (mmex == 2) {
            std::cout << "\nThank you for using the program!";
            exit(0);
        } else if (mmex != 1 && mmex != 2) {
            std::cout << "\nInvalid Input!";
            repUi(); // Call the function again to get a valid input
        }   
    };

    /* Function to add a new exercise to the exercises vector.
       Prompts the user for title, date, name, sets, repetitions, and weights. */
       
    void workout() {
        try {
            if (workoutTitle.empty() && workoutDate.empty()) {
                // Get workout title with validation
                while (true) {
                    std::cout << "Enter workout title: ";
                    std::getline(std::cin, workoutTitle);
                    
                    if (workoutTitle.empty()) {
                        system("cls");
                        std::cout << "Error: Workout title cannot be empty.\n\n";
                        continue;
                    }
                    break;
                }

                // Get workout date with validation
                while (true) {
                    std::cout << "Enter workout date (YYYY-MM-DD): ";
                    std::getline(std::cin, workoutDate);
                    if (!isValidDate(workoutDate)) {
                        system("cls");
                        std::cout << "Invalid date format. Use YYYY-MM-DD\n\n";
                        workoutDate.clear();
                        continue;
                    }
                    std::cout << "\n";
                    break;
                }
            } else {
                std::cout << "\nWorkout Name: " << workoutTitle << std::endl;
                std::cout << "Workout Date: " << workoutDate << std::endl;
                std::cout << "\n";
            }
        } catch (const std::exception& e) {
            system("cls");
            std::cout << "Error in workout setup: " << e.what() << std::endl << std::endl;
            workoutTitle.clear();
            workoutDate.clear();
            workout(); // Retry on error
        }
    }

    void addExercise() {
        try {
            if (exercises.size() >= SIZE_MAX) {
                throw std::runtime_error("Maximum number of exercises reached");
            }
            
            Exercise newExercise;
                
            // Get exercise name with validation
            do {
                std::cout << "Enter exercise name: ";
                std::getline(std::cin, newExercise.name);
                if (newExercise.name.empty()) {
                    std::cout << "Exercise name cannot be empty. Please try again.\n";
                }
            } while (newExercise.name.empty());

            // Show current exercises if any exist
            if (!exercises.empty()) {
                std::cout << "\nCurrent exercises in your workout:\n";
                for (size_t i = 0; i < exercises.size(); ++i) {
                    std::cout << i + 1 << ". " << exercises[i].name << std::endl;
                }
                std::cout << "\n";
            }

            // Get number of sets with validation for positive integers
            while (true) {
                try {
                    std::cout << "Enter number of sets: ";
                    std::string input;
                    std::getline(std::cin, input);
                    
                    if (input.empty()) {
                        throw std::invalid_argument("Empty input");
                    }
                    
                    int sets;
                    std::istringstream iss(input);
                    if (!(iss >> sets) || !iss.eof()) {
                        throw std::invalid_argument("Invalid number format");
                    }
                    
                    if (sets <= 0) {
                        throw std::out_of_range("Sets must be greater than 0");
                    }
                    
                    newExercise.sets = sets;
                    break;
                } catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << ". Please try again.\n";
                }
            }

            // Validate vector resizing
            try {
                newExercise.reps.resize(newExercise.sets);
                newExercise.weights.resize(newExercise.sets);
            } catch (const std::bad_alloc& e) {
                throw std::runtime_error("Not enough memory to add exercise");
            }

            // Get reps and weights for each set
            for (int i = 0; i < newExercise.sets; ++i) {
                std::cout << "\nSet " << (i + 1) << ":\n";
                
                // Get reps with validation for positive integers
                while (true) {
                    try {
                        std::cout << "Enter reps: ";
                        std::string input;
                        std::getline(std::cin, input);
                        
                        if (input.empty()) {
                            throw std::invalid_argument("Empty input");
                        }
                        
                        int reps;
                        std::istringstream iss(input);
                        if (!(iss >> reps) || !iss.eof()) {
                            throw std::invalid_argument("Invalid number format");
                        }
                        
                        if (reps <= 0) {
                            throw std::out_of_range("Reps must be greater than 0");
                        }
                        
                        newExercise.reps[i] = reps;
                        break;
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << ". Please try again.\n";
                    }
                }
                
                // Get weights with validation for non-negative numbers
                while (true) {
                    try {
                        std::cout << "Enter weight (in kg): ";
                        std::string input;
                        std::getline(std::cin, input);
                        
                        if (input.empty()) {
                            throw std::invalid_argument("Empty input");
                        }
                        
                        float weight;
                        std::istringstream iss(input);
                        if (!(iss >> weight) || !iss.eof()) {
                            throw std::invalid_argument("Invalid number format");
                        }
                        
                        if (weight < 0) {
                            throw std::out_of_range("Weight cannot be negative");
                        }
                        
                        newExercise.weights[i] = weight;
                        break;
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << ". Please try again.\n";
                    }
                }
            }

            exercises.push_back(newExercise);
            std::cout << "\nExercise added successfully!\n";

            // Show exercise summary
            std::cout << "\nExercise Summary:\n\n";
            std::cout << "Name: " << newExercise.name << "\n";
            for (int i = 0; i < newExercise.sets; ++i) {
                std::cout << "Set " << (i + 1) << ": "
                         << newExercise.reps[i] << " reps @ "
                         << newExercise.weights[i] << " kg\n";
            }

            if (yesorno()) {
                system("cls");
                // Display workout info again after clearing screen
                std::cout << "Workout Name: " << workoutTitle << "\n";
                std::cout << "Workout Date: " << workoutDate << "\n\n";
                addExercise();
            } else {
                system("cls");
                ui();
            }
        } catch (const std::exception& e) {
            std::cout << "Error adding exercise: " << e.what() << "\n";
            if (yesorno()) {
                system("cls");
                // Display workout info again after error
                std::cout << "Workout Name: " << workoutTitle << "\n";
                std::cout << "Workout Date: " << workoutDate << "\n\n";
                addExercise();
            } else {
                system("cls");
                ui();
            }
        }
    }

    void displayCurrentWorkout(const std::string& workoutTitle, const std::string& workoutDate) {
    	
        std::cout << "\nWorkout Name: " << workoutTitle << std::endl;
        std::cout << "Workout Date: " << workoutDate << std::endl;
        std::cout << "\n";
        std::cout << "=======================================================\n";
        std::cout << std::left << std::setw(25) << "Exercise Name";
        std::cout << std::setw(12) << "Set";
        std::cout << std::setw(14) << "Weight";
        std::cout << std::setw(12) << "Reps"; 
        std::cout << std::endl;
        std::cout << "=======================================================\n";

        for (const auto& exercise : exercises) {
            for (int i = 0; i < exercise.sets; ++i) {
                // Print exercise name only for the first set
                if (i == 0) {
                    std::cout << std::left << std::setw(25) << exercise.name;
                } else {
                    std::cout << std::left << std::setw(25) << " "; // Blank space for subsequent sets
                }
                std::cout << std::setw(12) << (i + 1); // Displaying the set number
                std::cout << std::setw(14) << exercise.weights[i];
                std::cout << std::setw(12) << exercise.reps[i];
                std::cout << std::endl;
            }
        }
        std::cout << "=======================================================\n";
    }

    // Function to delete an exercise from the exercises vector.
    
    void deleteExercise() {

        if (exercises.empty()) {
            std::cout << "No exercises to delete." << std::endl;
            return;
        }

        std::cout << "Current Exercises:\n\n";
        for (size_t i = 0; i < exercises.size(); ++i) {
            std::cout << i + 1 << ". " << exercises[i].name << std::endl;
        }

        int index;
        std::cout << "\nEnter the number of the exercise you want to delete: ";
        std::cin >> index;
        std::cin.ignore(); 

        if (index < 1 || index > exercises.size()) {
            std::cout << "Invalid choice. Please try again." << std::endl;
            return;
        }

        // Remove the selected exercise
        exercises.erase(exercises.begin() + (index - 1));
        std::cout << "\nExercise deleted successfully!" << std::endl;

        // Use the yes or no function to ask if the user wants to delete another exercise
        if (yesorno()) {
            deleteExercise();
        } else {
            system("cls");
            ui(); // Return to main menu
        }

         /* Things to add:
		   show the lists of exercises briefly 
           also remove the set of the specific exercise */
    }
    
    void editExercise() {
    // Check if there are any exercises to edit
    if (exercises.empty()) {
        std::cout << "No exercises to edit." << std::endl;
        return;
    }

    // Display list of all current exercises with their index numbers
    std::cout << "Current Exercises:\n\n";
    for (size_t i = 0; i < exercises.size(); ++i) {
        std::cout << i + 1 << ". " << exercises[i].name << std::endl;
    }

    // Variable to store the user's choice of exercise to edit
    int index;
    // Prompt user to select an exercise by number
    std::cout << "\nEnter the number of the exercise you want to edit: ";
    std::cin >> index;
    std::cin.ignore(); // Clear the input buffer after reading the number

    // Validate the user's input
    if (index < 1 || index > exercises.size()) {
        std::cout << "Invalid choice. Please try again." << std::endl;
        return;
    }

    // Get a reference to the exercise that will be edited (index-1 because array is 0-based)
    Exercise& exerciseToEdit = exercises[index - 1];

    // Show which exercise is being edited
    std::cout << "\nEditing exercise: " << exerciseToEdit.name << "\n";

    // Prompt for new exercise name, showing current name. Enter to keep current name
    std::cout << "\nEnter new exercise name (or press Enter to keep current: " << exerciseToEdit.name << "): ";
    std::string newName;
    std::getline(std::cin, newName);
    // Update name only if user entered something
    if (!newName.empty()) {
        exerciseToEdit.name = newName;
    }

    // Prompt for new number of sets, showing current number. Enter to keep current number
    std::cout << "Enter new number of sets (or press Enter to keep current: " << exerciseToEdit.sets << "): ";
    std::string newSetStr;
    std::getline(std::cin, newSetStr);
    // Update sets only if user entered something
    if (!newSetStr.empty()) {
        int newSets = std::stoi(newSetStr); // Convert string to integer
        exerciseToEdit.sets = newSets;
        exerciseToEdit.reps.resize(newSets); // Resize reps vector to match new number of sets
        exerciseToEdit.weights.resize(newSets); // Resize weights vector to match new number of sets
    }

    // Loop through each set to edit reps and weights
    for (int i = 0; i < exerciseToEdit.sets; ++i) {
        // Prompt for new reps for current set, showing current reps. Enter to keep current reps
        std::cout << "Enter new reps for set " << (i + 1) << " (or press Enter to keep current: " << exerciseToEdit.reps[i] << "): ";
        std::string newRepStr;
        std::getline(std::cin, newRepStr);
        // Update reps only if user entered something
        if (!newRepStr.empty()) {
            exerciseToEdit.reps[i] = std::stoi(newRepStr); // Convert string to integer
        }

        // Prompt for new weight for current set, showing current weight. Enter to keep current weight
        std::cout << "Enter new weight for set " << (i + 1) << " (or press Enter to keep current: " << exerciseToEdit.weights[i] << "): ";
        std::string newWeightStr;
        std::getline(std::cin, newWeightStr);
        // Update weight only if user entered something
        if (!newWeightStr.empty()) {
            exerciseToEdit.weights[i] = std::stof(newWeightStr); // Convert string to float
        }
    }

    // Confirm successful edit to user
    std::cout << "\nExercise edited successfully!\n";

    // Ask if user wants to edit another exercise
    if (yesorno()) {
        editExercise(); // Recursively call editExercise if user wants to edit another
    } else {
        system("cls"); // Clear the screen
        ui(); // Return to main menu
    }
}

    void saveWorkoutToFile() {
        try {
            if (exercises.empty()) {
                std::cout << "No exercises to save." << std::endl;
                repUi();
                return;
            }

            // Create filename using workout title and date
            std::string filename = workoutTitle + "_" + workoutDate + ".txt";
            // Sanitize filename
            const std::string invalid_chars = "\\/:*?\"<>|";
            for (char c : invalid_chars) {
                std::replace(filename.begin(), filename.end(), c, '_');
            }
            
            // Check if file already exists
            std::ifstream checkFile(filename);
            if (checkFile.good()) {
                std::cout << "File already exists. Overwrite? (y/n): ";
                if (!yesorno()) {
                    return;
                }
            }
            checkFile.close();
            
            std::ofstream outFile(filename);
            if (!outFile.is_open()) {
                throw std::runtime_error("Unable to create file: Permission denied");
            }

            // Write workout header
            outFile << "======================================\n";
            outFile << "Workout Name: " << workoutTitle << "\n";
            outFile << "Workout Date: " << workoutDate << "\n";
            outFile << "======================================\n\n";

            // Write exercise table header
            outFile << std::left << std::setw(25) << "Exercise Name";
            outFile << std::setw(12) << "Set";
            outFile << std::setw(14) << "Weight";
            outFile << std::setw(12) << "Reps";
            outFile << "\n=======================================================\n";

            // Write each exercise and its details
            for (const auto& exercise : exercises) {
                for (int i = 0; i < exercise.sets; ++i) {
                    if (i == 0) {
                        outFile << std::left << std::setw(25) << exercise.name;
                    } else {
                        outFile << std::left << std::setw(25) << " ";
                    }
                    outFile << std::setw(12) << (i + 1);
                    outFile << std::setw(14) << exercise.weights[i];
                    outFile << std::setw(12) << exercise.reps[i] << "\n";
                }
            }
            outFile << "=======================================================\n";
            
            outFile.close();
            std::cout << "\nWorkout saved successfully to: " << filename << std::endl;
            
        } catch (const std::exception& e) {
            std::cout << "Error saving workout: " << e.what() << "\n";
        }
    }
};

std::string getValidInput(const std::string& prompt, size_t maxLength = 100) {
    while (true) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            std::cout << "Input cannot be empty\n";
            continue;
        }
        
        if (input.length() > maxLength) {
            std::cout << "Input too long (max " << maxLength << " characters)\n";
            continue;
        }
        
        // Remove leading/trailing whitespace
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);
        
        return input;
    }
}

int main(){
    mainmenu mm1;  // This is the main menu struct object.
    mm1.ui(); // Object accessing the ui.
    return 0;
}