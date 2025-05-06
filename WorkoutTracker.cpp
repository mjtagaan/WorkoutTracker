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
    void repUi() {
        while (true) {
            std::cout << "\nEnter [1] to return to the main menu. \n";
            std::cout << "Enter [2] to exit. \n\n";
                
            std::string input;
            std::cout << "Enter your choice: ";
            std::getline(std::cin, input);

            try {
                if (input.empty()) {
                    throw std::invalid_argument("Empty input");
                }

                int mmex;
                std::istringstream iss(input);
                if (!(iss >> mmex) || !iss.eof()) {
                    throw std::invalid_argument("Invalid input");
                }

                if (mmex == 1) {
                    system("cls");
                    ui();
                    break;
                } else if (mmex == 2) {
                    std::cout << "\nThank you for using the program!";
                    exit(0);
                } else {
                    throw std::out_of_range("Invalid choice");
                }
            } catch (const std::exception& e) {
                system("cls");
                std::cout << "Error: " << e.what() << ". Please enter 1 or 2.\n";
            }
        }
    }

    /* Function to add a new exercise to the exercises vector.
       Prompts the user for title, date, name, sets, repetitions, and weights. */
       
    /* Workout Function Documentation
       Purpose: Manages the workout title and date input/display functionality
       - Handles initial workout setup
       - Validates and stores workout information
       - Prevents empty or whitespace-only titles
       - Ensures proper date format
       - Provides error recovery */

    void workout() {
        while (true) {  // Main loop for error recovery and input validation
            try {
                // Check if workout information already exists
                if (workoutTitle.empty() && workoutDate.empty()) {
                    
                    // Title Input Loop
                    while (true) {
                        std::cout << "Enter workout title: ";
                        std::getline(std::cin, workoutTitle);
                        
                        // Remove leading/trailing whitespace from title
                        workoutTitle.erase(0, workoutTitle.find_first_not_of(" \t\n\r"));
                        workoutTitle.erase(workoutTitle.find_last_not_of(" \t\n\r") + 1);
                        
                        // Validate title is not empty after trimming
                        if (workoutTitle.empty()) {
                            system("cls");  // Clear screen for better user experience
                            std::cout << "Error: Workout title cannot be empty or contain only whitespace.\n\n";
                            continue;  // Restart title input loop
                        }
                        break;  // Valid title obtained
                    }

                    // Date Input Loop
                    while (true) {
                        std::cout << "Enter workout date (YYYY-MM-DD): ";
                        std::getline(std::cin, workoutDate);
                        
                        // Validate date format using isValidDate helper function
                        if (!isValidDate(workoutDate)) {
                            system("cls");
                            std::cout << "Invalid date format. Use YYYY-MM-DD\n\n";
                            workoutDate.clear();  // Reset invalid date
                            continue;  // Restart date input loop
                        }
                        std::cout << "\n";
                        break;  // Valid date obtained
                    }
                    break;  // Exit main loop after successful input
                    
                } else {
                    // Display existing workout information
                    std::cout << "\nWorkout Name: " << workoutTitle << std::endl;
                    std::cout << "Workout Date: " << workoutDate << std::endl;
                    std::cout << "\n";
                    break;  // Exit main loop
                }
                
            } catch (const std::exception& e) {
                // Handle any unexpected errors
                system("cls");
                std::cout << "Error in workout setup: " << e.what() << std::endl << std::endl;
                
                // Reset workout information
                workoutTitle.clear();
                workoutDate.clear();
                
                continue;  // Restart main loop for error recovery
            }
        }
    }

    /* Function: addExercise()
       Purpose: Adds a new exercise to the workout with full validation and error handling
       - Manages exercise creation and data input
       - Validates all numeric inputs
       - Provides memory safety checks
       - Shows exercise summary after addition
       - Allows multiple exercise additions */

    void addExercise() {
        try {
            // Check if maximum exercise limit reached
            if (exercises.size() >= SIZE_MAX) {
                throw std::runtime_error("Maximum number of exercises reached");
            }
            
            Exercise newExercise;  // Create new exercise object
                
            // Exercise name input with empty check
            do {
                std::cout << "Enter exercise name: ";
                std::getline(std::cin, newExercise.name);
                if (newExercise.name.empty()) {
                    std::cout << "Exercise name cannot be empty. Please try again.\n";
                }
            } while (newExercise.name.empty());

            // Display existing exercises for reference
            if (!exercises.empty()) {
                std::cout << "\nCurrent exercises in your workout:\n";
                for (size_t i = 0; i < exercises.size(); ++i) {
                    std::cout << i + 1 << ". " << exercises[i].name << std::endl;
                }
                std::cout << "\n";
            }

            // Get number of sets with validation
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

            // Allocate memory for reps and weights vectors
            try {
                newExercise.reps.resize(newExercise.sets);
                newExercise.weights.resize(newExercise.sets);
            } catch (const std::bad_alloc& e) {
                throw std::runtime_error("Not enough memory to add exercise");
            }

            // Input loop for each set's data
            for (int i = 0; i < newExercise.sets; ++i) {
                std::cout << "\nSet " << (i + 1) << ":\n";
                
                // Get reps with validation
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
                
                // Get weights with validation
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

            // Add exercise to vector
            exercises.push_back(newExercise);
            std::cout << "\nExercise added successfully!\n";

            // Display exercise summary
            std::cout << "\nExercise Summary:\n\n";
            std::cout << "Name: " << newExercise.name << "\n";
            for (int i = 0; i < newExercise.sets; ++i) {
                std::cout << "Set " << (i + 1) << ": "
                         << newExercise.reps[i] << " reps @ "
                         << newExercise.weights[i] << " kg\n";
            }

            // Ask to add another exercise
            if (yesorno()) {
                system("cls");
                // Redisplay workout info
                std::cout << "Workout Name: " << workoutTitle << "\n";
                std::cout << "Workout Date: " << workoutDate << "\n\n";
                addExercise();  // Recursive call for another exercise
            } else {
                system("cls");
                ui();  // Return to main menu
            }
        } catch (const std::exception& e) {
            // Error handling for the entire function
            std::cout << "Error adding exercise: " << e.what() << "\n";
            if (yesorno()) {
                system("cls");
                // Redisplay workout info after error
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

    /* Function: deleteExercise()
       Purpose: Removes exercises from the workout with confirmation
       Features:
       - Lists all current exercises
       - Validates exercise selection
       - Confirms deletion
       - Handles empty exercise list
       - Provides cancellation option
       - Allows multiple deletions */

    void deleteExercise() {
        try {
            // Check if there are exercises to delete
            if (exercises.empty()) {
                std::cout << "No exercises to delete." << std::endl;
                repUi();
                return;
            }

            while (true) {  // Main deletion loop
                // Display current exercises with numbers
                std::cout << "Current Exercises:\n\n";
                for (size_t i = 0; i < exercises.size(); ++i) {
                    std::cout << i + 1 << ". " << exercises[i].name << std::endl;
                }

                // Get exercise number with cancel option
                std::string input;
                std::cout << "\nEnter the number of the exercise to delete (or press Enter to cancel): ";
                std::getline(std::cin, input);

                // Handle cancellation via Enter key
                if (input.empty()) {
                    std::cout << "\nDeletion cancelled.\n";
                    repUi();
                    return;
                }

                try {
                    // Validate input number
                    int index;
                    std::istringstream iss(input);
                    if (!(iss >> index) || !iss.eof()) {
                        throw std::invalid_argument("Invalid input. Please enter a number.");
                    }

                    // Check if number is in valid range
                    if (index < 1 || index > exercises.size()) {
                        throw std::out_of_range("Invalid exercise number.");
                    }

                    // Confirm deletion
                    std::cout << "\nAre you sure you want to delete '" << exercises[index-1].name << "'? (y/n): ";
                    char choice;
                    std::cin >> choice;
                    std::cin.ignore();

                    if (tolower(choice) == 'y') {
                        // Perform deletion
                        exercises.erase(exercises.begin() + (index - 1));
                        std::cout << "\nExercise deleted successfully!\n";
                        
                        // Option to delete another if exercises remain
                        if (!exercises.empty()) {
                            if (yesorno()) {  // Using global yes/no function
                                system("cls");
                                workout();
                                continue;  // Continue deletion loop
                            }
                        }
                    } else {
                        std::cout << "\nDeletion cancelled.\n";
                    }
                    repUi();
                    return;

                } catch (const std::exception& e) {
                    // Handle invalid input errors
                    std::cout << "Error: " << e.what() << "\nPlease try again.\n\n";
                    continue;
                }
            }
        } catch (const std::exception& e) {
            // Handle unexpected errors
            std::cout << "Error in delete operation: " << e.what() << std::endl;
            repUi();
        }
    }
    
    /* Function: editExercise()
       Purpose: Allows modification of existing exercises in the workout
       Features:
       - Displays list of current exercises
       - Allows editing of exercise name, sets, reps, and weights
       - Provides cancellation option
       - Input validation for all numeric values
       - Memory safety for vector resizing
       - Maintains data integrity during edits */

    void editExercise() {
        while (true) {  // Main edit loop for error recovery
            // Check for exercises to edit
            if (exercises.empty()) {
                std::cout << "No exercises to edit." << std::endl;
                repUi();
                return;
            }

            // Display exercise list
            std::cout << "Current Exercises:\n\n";
            for (size_t i = 0; i < exercises.size(); ++i) {
                std::cout << i + 1 << ". " << exercises[i].name << std::endl;
            }
            
            // Get exercise selection with cancel option
            std::string input;
            std::cout << "\nEnter the number of the exercise to edit (or press Enter to cancel): ";
            std::getline(std::cin, input);

            // Handle cancellation
            if (input.empty()) {
                std::cout << "\nEdit cancelled.\n";
                repUi();
                return;
            }

            try {
                // Validate exercise number input
                int index;
                std::istringstream iss(input);
                if (!(iss >> index) || !iss.eof()) {
                    throw std::invalid_argument("Invalid input. Please enter a number.");
                }

                if (index < 1 || index > exercises.size()) {
                    throw std::out_of_range("Invalid exercise number.");
                }

                // Get reference to selected exercise
                Exercise& exerciseToEdit = exercises[index - 1];

                // Edit exercise name with empty input check
                std::cout << "\nCurrent name: " << exerciseToEdit.name;
                std::cout << "\nEnter new name (or press Enter to keep current): ";
                std::string newName;
                std::getline(std::cin, newName);
                if (!newName.empty()) {
                    exerciseToEdit.name = newName;
                }

                // Edit number of sets with validation
                std::cout << "\nCurrent number of sets: " << exerciseToEdit.sets;
                std::cout << "\nEnter new number of sets (or press Enter to keep current): ";
                std::string newSetStr;
                std::getline(std::cin, newSetStr);

                // Process new sets if provided
                if (!newSetStr.empty()) {
                    try {
                        std::istringstream iss(newSetStr);
                        int newSets;
                        if (!(iss >> newSets) || !iss.eof()) {
                            throw std::invalid_argument("Invalid number format");
                        }
                        if (newSets <= 0) {
                            throw std::out_of_range("Sets must be greater than 0");
                        }
                        exerciseToEdit.sets = newSets;
                        exerciseToEdit.reps.resize(newSets);
                        exerciseToEdit.weights.resize(newSets);
                    } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << ". Keeping current sets.\n";
                    }
                }

                // Edit reps and weights for each set
                for (int i = 0; i < exerciseToEdit.sets; ++i) {
                    std::cout << "\nSet " << (i + 1) << ":\n";
                    
                    // Edit reps with validation
                    std::cout << "Current reps: " << exerciseToEdit.reps[i];
                    std::cout << "\nEnter new reps (or press Enter to keep current): ";
                    std::string newRepStr;
                    std::getline(std::cin, newRepStr);

                    if (!newRepStr.empty()) {
                        try {
                            std::istringstream iss(newRepStr);
                            int newReps;
                            if (!(iss >> newReps) || !iss.eof()) {
                                throw std::invalid_argument("Invalid number format");
                            }
                            if (newReps <= 0) {
                                throw std::out_of_range("Reps must be greater than 0");
                            }
                            exerciseToEdit.reps[i] = newReps;
                        } catch (const std::exception& e) {
                            std::cout << "Error: " << e.what() << ". Keeping current reps.\n";
                        }
                    }

                    // Edit weights with validation
                    std::cout << "Current weight: " << exerciseToEdit.weights[i];
                    std::cout << "\nEnter new weight (or press Enter to keep current): ";
                    std::string newWeightStr;
                    std::getline(std::cin, newWeightStr);

                    if (!newWeightStr.empty()) {
                        try {
                            std::istringstream iss(newWeightStr);
                            float newWeight;
                            if (!(iss >> newWeight) || !iss.eof()) {
                                throw std::invalid_argument("Invalid number format");
                            }
                            if (newWeight < 0) {
                                throw std::out_of_range("Weight cannot be negative");
                            }
                            exerciseToEdit.weights[i] = newWeight;
                        } catch (const std::exception& e) {
                            std::cout << "Error: " << e.what() << ". Keeping current weight.\n";
                        }
                    }
                }

                // Confirm successful edit
                std::cout << "\nExercise edited successfully!\n";

                // Option to edit another exercise
                if (yesorno()) {
                    system("cls");
                    workout();
                    continue;  // Continue loop for another edit
                } else {
                    system("cls");
                    ui();
                    return;
                }
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << "\nPlease try again.\n\n";
                continue;  // Continue loop on error
            }
        }
    }

    /* Function: saveWorkoutToFile()
       Purpose: Saves the current workout session to a text file
       Features:
       - Creates a formatted text file with workout details
       - Sanitizes filename for system compatibility
       - Handles file overwrite protection
       - Provides proper error handling
       - Formats output for readability
       - Validates file operations */

    void saveWorkoutToFile() {
        try {
            // Check if there are exercises to save
            if (exercises.empty()) {
                std::cout << "No exercises to save." << std::endl;
                repUi();
                return;
            }

            // Create filename from workout details and sanitize it
            std::string filename = workoutTitle + "_" + workoutDate + ".txt";
            const std::string invalid_chars = "\\/:*?\"<>|";  // Windows invalid filename chars
            for (char c : invalid_chars) {
                std::replace(filename.begin(), filename.end(), c, '_');
            }
            
            // File overwrite protection
            std::ifstream checkFile(filename);
            if (checkFile.good()) {
                std::cout << "File already exists. Overwrite? (y/n): ";
                if (!yesorno()) {
                    return;  // User chose not to overwrite
                }
            }
            checkFile.close();
            
            // Create and open output file
            std::ofstream outFile(filename);
            if (!outFile.is_open()) {
                throw std::runtime_error("Unable to create file: Permission denied");
            }

            // Write formatted workout header
            outFile << "======================================\n";
            outFile << "Workout Name: " << workoutTitle << "\n";
            outFile << "Workout Date: " << workoutDate << "\n";
            outFile << "======================================\n\n";

            // Write table header with column alignment
            outFile << std::left 
                    << std::setw(25) << "Exercise Name"
                    << std::setw(12) << "Set"
                    << std::setw(14) << "Weight"
                    << std::setw(12) << "Reps"
                    << "\n=======================================================\n";

            // Write exercise data in tabular format
            for (const auto& exercise : exercises) {
                for (int i = 0; i < exercise.sets; ++i) {
                    // Print exercise name only for first set
                    if (i == 0) {
                        outFile << std::left << std::setw(25) << exercise.name;
                    } else {
                        outFile << std::left << std::setw(25) << " ";  // Alignment spacing
                    }
                    outFile << std::setw(12) << (i + 1)  // Set number
                           << std::setw(14) << exercise.weights[i]  // Weight
                           << std::setw(12) << exercise.reps[i]     // Reps
                           << "\n";
                }
            }
            outFile << "=======================================================\n";
            
            // Close file and confirm save
            outFile.close();
            std::cout << "\nWorkout saved successfully to: " << filename << std::endl;
            
        } catch (const std::exception& e) {
            // Handle any file operation errors
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