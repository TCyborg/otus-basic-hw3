#include "guess_the_number.h"
#include <iostream>

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

const std::string high_scores_filename = "high_scores.txt";

int main(int argc, char** argv) {
	int max_value = 100;
	int current_value = 0;
	bool not_win = true;
	int attempts_count = 0;

	// argc - it is a count of arguments
	// But there is some detail - OS always pass one system argument - the name of the executable
	// So, is the application was executed without arguments at all, argc will be still == 1

	// Let's print this argument
	if (argc > 0) {
		std::cout << "We have at least one argument!" << std::endl;
		std::cout << "argv[0] = " << argv[0] << std::endl;
	}

	// To check - does use print some other argument we should check if the argc >= 2
	if (argc >= 2) {
		std::cout << "We have one more argument!" << std::endl;
		std::cout << "argv[1] = " << argv[1] << std::endl;

		std::string arg1_value{ argv[1] };
		if (arg1_value == "-max") {
			std::cout << "-parameter max was detected!" << std::endl;

			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-parameter' requires some value!" << std::endl;
				return -1;
			}
			// We need to parse the string to the int value
			max_value = std::stoi(argv[2]);
			std::cout << "The '-parameter' value = " << max_value << std::endl;
		}
		if (arg1_value == "-table") {
			print_leaderboard();
			return 0;
		}
	}

	const int target_value = generate_random_value(max_value);

	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;
	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;
		attempts_count++;
		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win! attempts = " << attempts_count << std::endl << std::endl;
			break;
		}

	} while(true);

	// Write new high score to the records table
	{
		// We should open the output file in the append mode - we don't want
		// to erase previous results.
		std::ofstream out_file{high_scores_filename, std::ios_base::app};
		if (!out_file.is_open()) {
			std::cout << "Failed to open file for write: " << high_scores_filename << "!" << std::endl;
			return -1;
		}

		// Append new results to the table:
		out_file << user_name << ' ';
		out_file << attempts_count;
		out_file << std::endl;
	} // end of score here just to mark end of the logic block of code

	print_leaderboard();

	return 0;
}

const int generate_random_value(const int max_value){
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % max_value;

	return random_value;
}

int print_leaderboard()
	// Read the high score file and print all results
{
	std::ifstream in_file{high_scores_filename};
	if (!in_file.is_open()) {
		std::cout << "Failed to open file for read: " << high_scores_filename << "!" << std::endl;
		return -1;
	}

	std::cout << "High scores table:" << std::endl;

	std::string username;
	int high_score = 0;
	while (true) {
		// Read the username first
		in_file >> username;
		// Read the high score next
		in_file >> high_score;
		// Ignore the end of line symbol
		in_file.ignore();

		if (in_file.fail()) {
			break;
		}

		// Print the information to the screen
		std::cout << username << '\t' << high_score << std::endl;
	}
return 0;
}
