#include <vector>
#include <iostream>

#ifndef MATHUTIL
#define MATHUTIL

int dotProduct(std::vector<int> v1, std::vector<int> v2);
int parseOperator(std::string input);
int positiveInteger(std::string input);
std::vector<int> seperateIntegers(std::string input, char seperator);

#endif