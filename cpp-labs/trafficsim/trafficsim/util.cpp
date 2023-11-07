#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "util.hpp"

/// @brief  Get a random number between two numbers
int randomInRange(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

/// @brief  Get a random color
Color randomColor() {
	return static_cast<Color>(randomInRange(0, 11));
}

/// @brief  Send the color through the outstream
std::ostream& operator<<(std::ostream& os, const Color& color) {
	static const char* color_table[COLOR_COUNT] = {
			"\x1b[31m", // red
			"\x1b[32m", // green
			"\x1b[33m", // yellow
			"\x1b[34m", // blue
			"\x1b[35m", // magenta
			"\x1b[36m", // cyan
			"\x1b[91m", // bright red
			"\x1b[92m", // bright green
			"\x1b[93m", // bright yellow
			"\x1b[94m", // bright blue
			"\x1b[95m", // bright magenta
			"\x1b[96m", // bright cyan
			"\x1b[90m", // bright black (grey)
			"\x1b[97m", // bright white
			"\033[0m"   // clears the color
	};
	os << color_table[color];
	return os;
}

/// @brief  Clears the console
void clearConsole() {
#ifdef _WIN32 // if the user is on windows use this method
	std::system("cls");
#else		  // otherwise use an ANSI escape code (linux/mac)
	std::cout << "\x1B[2J\x1B[H";
#endif
}

/// @brief  Makes the program wait a certain number of seconds before continuing
void wait(int milliseconds) {
	std::chrono::milliseconds duration(milliseconds);
	std::this_thread::sleep_for(duration);
}

/// @brief  Prompts the user for input and modifies it
void promptUser(const char* message, std::string* input) {
	std::cout << " " << message << std::endl;
	std::cout << "  >> ";
	std::getline(std::cin, *input);
}

/// @brief  Converts a string to unsigned int, with error handling
unsigned int safe_stoul(std::string string) {
	try {
		int signedInt = std::stoi(string);
		if (signedInt < 0) {
			std::cerr << "Invalid sign. Number must be positive." << std::endl;
			return 0;
		}
		return static_cast<unsigned int>(signedInt);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid input, must be an unsigned integer." << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of range, number is too large." << std::endl;
	}
	return 0;
}

/// @brief  Converts a string to an integer, with error handling
int safe_stoi(std::string string) {
	try {
		return std::stoi(string);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid input, must be an integer." << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cerr << "Out of range, number too large" << std::endl;
	}
	return 0;
}

/// @brief  Rolls a random normalized number between 0 and 1, if the number is <= 1/rarity, returns true
bool chance(unsigned int rarity) {
	return chance(1.0 / static_cast<double>(rarity));
}
/// @brief	Rollas a random normalized number between 0 and 1, if the number is <= rate, returns true
bool chance(double rate) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0, 1);
	if (distribution(gen) <= rate) {
		return true;
	}
	return false;
}
