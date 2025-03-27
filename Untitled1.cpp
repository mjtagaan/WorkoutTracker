#include <iostream>
#include <iomanip>

void ui(){
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
}

int main(){
	ui();
	return 0;
}