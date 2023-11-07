#include "matrix.hpp"
#include "mathutil.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	// get which input file to read
	int file_index = 0;
	std::cout << "which input file? " << std::endl;
	std::string index_input;
	std::getline(std::cin, index_input);
	file_index = positiveInteger(index_input);

	// grab the input file
	std::ifstream input_file;
	input_file.open("input" + std::to_string(file_index) + ".txt");

	// if the file was unable to open
	if (!input_file.is_open()) {
		// return the error
		std::cerr << "Unable to open input" << file_index << ".txt" << std::endl;
		return 1;
	}

	// beging reading file            <------------------------- UNFINISHED SECTION
	std::string line;
	Matrix matricies[2];
	std::vector<std::string> matrix_builders[2];
	int matrix_index = 0;
	int operator_index = 0;
	while (std::getline(input_file, line)) {
		// if the line is empty skip it
		if (line.empty()) {
			continue;
		}
		// testfor: operator
		if (line.length() > 2 && line[0] == 'o' && line[1] == 'p') {
			operator_index = parseOperator(line);
			if (matrix_builders[0].size() > 0) {
				matrix_index++;
			}
			continue;
		}

		// otherwise its a matrix
		matrix_builders[matrix_index].push_back(line);
	}

	// convert matrix builders to matricies
	matricies[0] = Matrix::ConvertFromDataset(matrix_builders[0]);
	if (matrix_builders[1].size() != 0) {
		matricies[1] = Matrix::ConvertFromDataset(matrix_builders[1]);
	}

	// start output
	std::cout << "<output>" << std::endl;

	// apply operators
	switch (operator_index) {
		case 1: // ADDITION operator
		{
			// requires two matricies to work
			if (matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: + requires 2 matricies");
			}
			std::cout << (matricies[0] + matricies[1]) << std::endl;
			break;
		}
		case 2: // SUBTRACTION operator
		{
			// requires two matricies to work
			if (matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: - requires 2 matricies");
			}
			std::cout << (matricies[0] - matricies[1]) << std::endl;
			break;
		}
		case 3: // MULTIPLICATION operator
		{
			// requires two matricies to work
			if (matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: * requires 2 matricies");
			}
			std::cout << (matricies[0] * matricies[1]) << std::endl;
			break;
		}
		case 4: // INCREMENTATION operator
		{
			// only works with one matrix
			if (matricies[0].isEmpty() || !matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: ++ requires 1 matrix");
			}
			matricies[0]++; // use post
			std::cout << matricies[0] << std::endl;
			break;
		}
		case 5: // DECREMENTATION operator
		{
			// only works with one matrix
			if (matricies[0].isEmpty() || !matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: -- requires 1 matrix");
			}
			--matricies[0]; // use pre
			std::cout << matricies[0] << std::endl;
			break;
		}
		case 6: // TRANSPOSITION operator
		{
			// only works with one matrix
			if (matricies[0].isEmpty() || !matricies[1].isEmpty()) {
				throw std::invalid_argument("Invalid input: ~ requires 1 matrix");
			}
			~matricies[0];
			std::cout << matricies[0] << std::endl;
			break;
		}
		default:
		{
			// OPERATORS IGNORED:
			// op 7 - exponential
			// op 0 - null operator
			// DEFAULT TO OUTPUT (op 8)
			std::cout << "defaulting to '<<'" << std::endl;
			for (Matrix matrix : matricies) {
				std::cout << matrix << std::endl;
			}
			break;
		}
	}

	// close file
	input_file.close();

	return 0;
}