#include "guess_the_number.h"
#include <iostream>

#include <cstdlib>
#include <ctime>

int main() {

	const int target_value = generate_random_value(100);
	int current_value = 0;
	bool not_win = true;

	std::cout << "Enter your guess:" << std::endl;

	do {
		std::cin >> current_value;

		if (current_value < target_value) {
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value > target_value) {
			std::cout << "greater than " << current_value << std::endl;
		}
		else {
			std::cout << "you win!" << std::endl;
			break;
		}

	} while(true);

	return 0;
}

const int generate_random_value(const int max_value){
	std::srand(std::time(nullptr)); // use current time as seed for random generator

	const int random_value = std::rand() % max_value;

	return random_value;
}
