#pragma once
#include <vector>
#include <iostream>
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
	std::vector<std::vector<int>> data;
	int rows, cols;
public:
	Matrix(int rows, int cols);
	Matrix();

	bool isEmpty();

	// ----------------------------------------
	//				OPERATORS
	// ----------------------------------------
	Matrix operator+(Matrix& other) const;
	Matrix operator-(Matrix& other) const;
	Matrix operator*(const int& scalar) const;
	Matrix operator*(Matrix& other) const;
	Matrix operator^(const int& exponent);
	friend void operator~(Matrix& matrix);
	friend void operator++(Matrix& matrix);
	friend void operator--(Matrix& matrix);
	friend void operator++(Matrix& matrix, int);
	friend void operator--(Matrix& matrix, int);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

	// ----------------------------------------
	//		      GETTERS/SETTERS
	// ----------------------------------------
	int at(int x, int y) const;
	int* get(int x, int y);

	std::vector<int> getRow(int i) const;
	std::vector<int> getCol(int i) const;

	int getRows() const;
	int getCols() const;

	void setRow(int y, std::vector<int> row);
	void addRow(std::vector<int> row);

	// ----------------------------------------
	//		           STATIC
	// ----------------------------------------
	static Matrix ConvertFromDataset(std::vector<std::string> dataset);
};

#endif