#include <iostream>
#include <fstream>
#include <string>
#include <map>

const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string format_frequency(float freq);

int main() {
	// open file
	std::ifstream file("input.txt");

	// run error if unable to open file
	if (!file.is_open()) {
		std::cerr << "unable to open file" << std::endl;
		return -1;
	}

	// setup output
	std::map<char, int> letter_counts;
	std::map<char, float> frequencies;

	// READ input
	std::string line; // (each input line)
	while (std::getline(file, line)) {
		// make sure each char is uppercase
		for (char& c : line) { c = std::toupper(c); }

		// get the total count for each character
		for (char c : line) {
			letter_counts[c]++;
		}
	}

	// close file
	file.close();

	// convert to frequency
	float sum = 0; // determine the sum of letters
	for (char c : letters) {
		sum += letter_counts[c];
	}
	std::cout << "sum: " << sum << std::endl;
	// now that we have the sum of all letters, calculate frequencies
	for (char c : letters) {
		frequencies[c] = letter_counts[c] / sum;
	}

	// output to screen
	int x = 0;
	for (char c : letters) {
		if (x > 3) {
			std::cout << std::endl; // add new row
			x = 0;
		}
		std::cout << "   " << c << " " << format_frequency(frequencies[c]) << "  ";
		x++; // a column has been added
	}

	return 0;
}

/// <summary>
/// formats the given frequency to an aligned output
/// </summary>
/// <param name="freq"></param>
/// <returns></returns>
std::string format_frequency(float freq) {
	float percentage = freq * 100;
	std::string flattened = std::to_string(percentage).substr(0, std::to_string(percentage).find('.'));
	// if less than 1
	if (percentage < 1) {
		return "<1%"; // return it as <1
	}
	// if 2-digits
	else if (percentage >= 10) {
		return flattened + "%"; // return is as the two digits
	}
	// 1 digit
	else {
		return " " + flattened + "%"; // return as a single digit
	}
}