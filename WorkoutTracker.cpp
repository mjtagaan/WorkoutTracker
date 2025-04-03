#include <iostream> // For the basic input and output functions.
#include <vector> // For handling dynamic inputs.	
#include <limits> // Limits library to add min/max value.
#include <cctype> // Include cctype library for character handling.
#include <cmath> // For future calculations.
#include <iomanip> // Include iomanip library for formatting output.
#include <cstdlib> // For the exit() function.

 /* Struct to represent the main menu and its associated functions. */

struct mainmenu { 

    /* Everything that happens within the main menu/display
       Function to serve as the back door to get back to the main menu. */

    /* Function to serve as the layout/default main menu when the program is launched. */

    void ui() { 

        // This function serves as the layout/default main menu when the program is launched.

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
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                std::cout << "save workout \n";
                repUi();
                break;
            case 6:   
                std::cout << "Thank you for using the workout tracker!";
                exit(0);
                break;
            default:   
                std::cout << "Invalid choice! Please choose between the numbers of [1-6].\n";
                repUi();
                break;
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
    	
    	Exercise newWorkout;
    	
    /* An if statement that checks if the user has already inputted a workout title and date.
       This is to prevent the enter workout title and date to keep on getting called if the user chooses the [1] Add Exercises for Workout choice in the main menu */
       
    	if (workoutTitle.empty() && workoutDate.empty()) { 
    		std::cout << "Enter workout title: ";				
        	std::getline(std::cin, workoutTitle);
        	std::cout << "Enter workout date (YYYY-MM-DD): ";
        	std::getline(std::cin, workoutDate);
        	std::cout << "\n";
		} else {
			std::cout << "\nWorkout Name: " << workoutTitle << std::endl;
        	std::cout << "Workout Date: " << workoutDate << std::endl;
        	std::cout << "\n";
		}	
	}

    void addExercise() {
    	
        Exercise newExercise;
       
        std::cout << "Enter exercise name: ";
        std::getline(std::cin, newExercise.name);
        std::cout << "Enter number of sets: ";
        std::cin >> newExercise.sets;
        std::cin.ignore(); // Ignore newline character left in the buffer

        newExercise.reps.resize(newExercise.sets); // Resize reps vector
        newExercise.weights.resize(newExercise.sets); // Resize weights vector

        for (int i = 0; i < newExercise.sets; ++i) {
            std::cout << "Enter reps for set " << (i + 1) << ": ";
            std::cin >> newExercise.reps[i];
            std::cout << "Enter weight for set " << (i + 1) << " (in kg): ";
            std::cin >> newExercise.weights[i];
        }

        exercises.push_back(newExercise); // Add new exercise to the vector
        std::cout << "\nExercise added successfully!\n";

        // Use the yes or no function to ask if the user wants to add another exercise
        
        if (yesorno()) {
            addExercise();
        } else {
        	system("cls");
            ui(); // Return to main menu	
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
};

int main(){
    mainmenu mm1;  // This is the main menu struct object.
    mm1.ui(); // Object accessing the ui.
    return 0;
}

/* Functions to add: Proceed function in the add exercises for workout function to briefly show the user their current workout list to avoid user redundancy.
   It's okay to do the same exercises repeatedly but this is to prevent the user from forgetting their added exercise(s). */