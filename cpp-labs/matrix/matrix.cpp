#include "matrix.hpp"
#include "mathutil.hpp"
#include <vector>
#include <iostream>

/// <summary>
/// construct an empty matrix with a given size
/// </summary>
/// <param name="rows"></param>
/// <param name="cols"></param>
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
	// allocate the size to the matrix
	data.resize(rows, std::vector<int>(cols, 0));
}

/// <summary>
/// empty constructor
/// </summary>
Matrix::Matrix() {
	this->rows = 0;
	this->cols = 0;
	data.resize(rows, std::vector<int>(cols, 0));
}

/// <summary>
/// returns whether or not the matrix is empty
/// </summary>
/// <returns></returns>
bool Matrix::isEmpty() {
	return data.empty();
}

// ----------------------------------------
//				OPERATORS
// ----------------------------------------

/// <summary>
/// Matrix addition operator
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Matrix Matrix::operator+(Matrix& other) const {
	// if the matrix sizes are not the same, throw an exception
	if (this->cols != other.cols && this->rows != other.rows)
		throw std::invalid_argument("add: dimensions are not exactly the same");
	// initialize the resulting matrix
	Matrix result = Matrix(this->rows, this->cols);
	// loop through both matricies
	for (int y = 0; y < this->rows; y++) {
		for (int x = 0; x < this->cols; x++) {
			// add the two values in the same position together
			*result.get(x, y) = this->at(x, y) + other.at(x, y);
		}
	}
	return result;
}

/// <summary>
/// Matrix subtraction operator
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Matrix Matrix::operator-(Matrix& other) const {
	// if the matrix sizes are not equal, throw exception
	if (this->cols != other.cols && this->rows != other.rows)
		throw std::invalid_argument("sub: dimensions are not exactly the same");
	// initialize result
	Matrix result = Matrix(this->rows, this->cols);
	// loop through both matricies
	for (int y = 0; y < this->rows; y++) {
		for (int x = 0; x < this->cols; x++) {
			// subtract the other matrix value from this matrix value
			*result.get(x, y) = this->at(x, y) - other.at(x, y);
		}
	}
	return result;
}

/// <summary>
/// Matrix scalar multiplication
/// </summary>
/// <param name="other_int"></param>
/// <returns></returns>
Matrix Matrix::operator*(const int& scalar) const {
	// init result
	Matrix result = Matrix(this->rows, this->cols);
	// loop through initial matrix
	for (int y = 0; y < this->rows; y++) {
		for (int x = 0; x < this->cols; x++) {
			// multiply scalar to the original matrix
			*result.get(x, y) = scalar * this->at(x, y);
		}
	}
	return result;
}

/// <summary>
/// Matrix multiplication
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Matrix Matrix::operator*(Matrix& other) const {
	// if this matrix's columns doesn't equal the number of rows in the other, throw exception
	if (this->cols != other.rows)
		throw std::invalid_argument("mult: this matrix's cols must equal the other's rows");
	// init the resulting matrix, cols = other.cols, rows = this.rows
	Matrix result = Matrix(this->rows, other.cols);
	// loop through empty result
	for (int y = 0; y < result.rows; y++) {
		for (int x = 0; x < result.cols; x++) {
			*result.get(x, y) = dotProduct(this->getRow(y), other.getCol(x));
		}
	}
	return result;
}

/// <summary>
/// Matrix positive exponential
/// </summary>
/// <param name="other"></param>
/// <returns></returns>
Matrix Matrix::operator^(const int& exponent) {
	// copy original matrix into the resulting matrix
	Matrix result = Matrix(this->rows, this->cols);
	for (int y = 0; y < result.rows; y++) {
		for (int x = 0; x < result.cols; x++) {
			*result.get(x, y) = this->at(x, y);
		}
	}
	// multiply by the given exponent
	for (int e = 0; e < exponent; e++) {
		result = result * (*this);
	}
	return result;
}

/// <summary>
/// Matrix transposition
/// </summary>
/// <param name="matrix"></param>
void operator~(Matrix& matrix) {
	// initialize a new matrix with the columns and rows swapped
	Matrix transposed = Matrix(matrix.cols, matrix.rows);
	// place the columns of the original matrix into the new one as rows
	for (int x = 0; x < matrix.cols; x++) {
		transposed.data[x] = matrix.getCol(x);
	}
	// update original matrix
	matrix = transposed;
}

/// <summary>
/// Matrix incrementation (PRE)
/// </summary>
/// <returns></returns>
void operator++(Matrix& matrix) {
	for (int y = 0; y < matrix.rows; y++) {
		for (int x = 0; x < matrix.cols; x++) {
			*matrix.get(x, y) += 1;
		}
	}
}

/// <summary>
/// Matrix incrementation (POST)
/// </summary>
/// <param name="matrix"></param>
/// <param name=""></param>
void operator++(Matrix& matrix, int) {
	++matrix;
}

/// <summary>
/// Matrix decrementation (PRE)
/// </summary>
/// <returns></returns>
void operator--(Matrix& matrix) {
	for (int y = 0; y < matrix.rows; y++) {
		for (int x = 0; x < matrix.cols; x++) {
			*matrix.get(x, y) -= 1;
		}
	}
}

/// <summary>
/// Matrix decrementation (POST)
/// </summary>
/// <returns></returns>
void operator--(Matrix& matrix, int) {
	--matrix;
}

/// <summary>
/// Matrix output operator
/// </summary>
/// <param name="os"></param>
/// <param name="matrix"></param>
/// <returns></returns>
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
	for (int y = 0; y < matrix.getRows(); y++) {
		for (int x = 0; x < matrix.getCols(); x++) {
			os << matrix.at(x, y) << " ";
		}
		os << '\n';
	}
	return os;
}

// ----------------------------------------
//		      GETTERS/SETTERS
// ----------------------------------------

/// <summary>
/// gets the address of the value in the matrix's given position
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int* Matrix::get(int x, int y) {
	return &this->data[y][x];
}

/// <summary>
/// returns the value at the matrix's given position
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
int Matrix::at(int x, int y) const {
	return this->data[y][x];
}

/// <summary>
/// gets the row at the given index
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
std::vector<int> Matrix::getRow(int y) const {
	return data[y];
}

/// <summary>
/// gets the column at the given index
/// </summary>
/// <param name="i"></param>
/// <returns></returns>
std::vector<int> Matrix::getCol(int x) const {
	std::vector<int> column(this->rows);
	for (int y = 0; y < this->rows; y++) {
		column[y] = this->at(x, y);
	}
	return column;
}

/// <summary>
/// returns the amount of columns in the matrix
/// </summary>
/// <returns></returns>
int Matrix::getCols() const {
	return this->cols;
}

/// <summary>
/// returns the amount of rows in the matrix
/// </summary>
/// <returns></returns>
int Matrix::getRows() const {
	return this->rows;
}

/// <summary>
/// sets the row at the given y to the given row
/// </summary>
/// <param name="y"></param>
/// <param name="row"></param>
void Matrix::setRow(int y, std::vector<int> row) {
	this->data[y] = row;
}

/// <summary>
/// adds a row to the end of the matrix and updates size accordingly
/// </summary>
/// <param name="row"></param>
void Matrix::addRow(std::vector<int> row) {
	if (this->cols == 0) { // update column size
		this->cols = row.size();
	}
	else if (this->cols != row.size()) {
		throw std::invalid_argument("Invalid Input: rows must be the same length (column size inconsistent)");
	}

	// update row size
	this->rows++;
	this->data.resize(rows, std::vector<int>(cols, 0));

	// add row
	this->data[this->rows - 1] = row;
}

// ----------------------------------------
//		           STATIC
// ----------------------------------------

/// <summary>
/// converts the given string dataset into a matrix
/// </summary>
/// <param name="dataset"></param>
/// <returns></returns>
Matrix Matrix::ConvertFromDataset(std::vector<std::string> dataset) {
	Matrix result = Matrix();
	// if the first line is not the same length as the next (or contains 'x')
	// then -> has a size initializer
	if ((dataset.size() > 1 && dataset[0].length() != dataset[1].length()) || dataset[0].find('x') != std::string::npos) {
		// read size initializer (mxn)
		if (dataset[0].find('x') != std::string::npos) {
			std::vector<int> size = seperateIntegers(dataset[0], 'x');
			result = Matrix(size[0], size[1]);
		}
		// read size initializer (s)
		else {
			int size = positiveInteger(dataset[0]);
			result = Matrix(size, size);
		}
		
		// read matrix
		for (int y = 0; y < result.rows; y++) {
			result.setRow(y, seperateIntegers(dataset[y + 1], ' '));
		}
	}
	// else -> no initializer
	else {
		// read matrix
		for (int y = 0; y < dataset.size(); y++) {
			result.addRow(seperateIntegers(dataset[y], ' '));
		}
	}

	return result;
}