#include "mathutil.hpp"
#include <vector>
#include <string>

/// <summary>
/// returns the dot product of two vectors
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
int dotProduct(std::vector<int> v1, std::vector<int> v2) {
	// if the vector sizes are not the same, throw exception
	if (v1.size() != v2.size())
		throw std::invalid_argument("Vectors must be the same size");
	// init result
	int result = 0;
	for (size_t i = 0; i < v1.size(); i++) {
		result += v1[i] + v2[i];
	}
	return result;
}

/// <summary>
/// returns the positive integer from the given string
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
int positiveInteger(std::string input) {
	// make sure the input is a positive integer
	int output = 0;
	try {
		// try to convert to integer
		output = std::stoi(input);
		if (output < 0) {
			// the input was not positive therefore return error
			throw std::invalid_argument("Invalid input: not a positive number");
		}
		return output;
	}
	catch (const std::invalid_argument& e) {
		// failed to convert to integer, therefore return an error
		std::cerr << "Invalid input: " << e.what() << "; Make sure its a number" << std::endl;
		return -1;
	}
	return -1;
}

/// <summary>
/// parses the operator from the given input
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
int parseOperator(std::string input) {
	std::string temp;
	int start_index = 0;
	// loop through the input until it reaches a number
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ' ') {
			start_index = i + 1;
			break;
		}
	}

	// build the number
	for (int i = start_index; i < input.length(); i++) {
		temp += input[i];
	}

	return positiveInteger(temp);
}

/// <summary>
/// seperates the given string by the seperator into a vector of integers
/// </summary>
/// <param name="input"></param>
/// <param name="seperator"></param>
/// <returns></returns>
std::vector<int> seperateIntegers(std::string input, char seperator) {
	std::vector<int> result;
	std::string temp = "";
	// loop through the input string
	for (int i = 0; i <= input.length(); i++) {
		if (input[i] == seperator) {
			try { result.push_back(std::stoi(temp)); }
			catch (const std::invalid_argument& e) {
				std::cerr << "Invalid input: " << e.what() << std::endl;
			}
			temp = ""; // reset temp string builder
		}
		else {
			// otherwise build the integer
			temp += input[i];
		}
	}
	try { result.push_back(std::stoi(temp)); }
	catch (const std::invalid_argument& e) {
		std::cerr << "Invalid input: " << e.what() << std::endl;
	}
	return result;
}