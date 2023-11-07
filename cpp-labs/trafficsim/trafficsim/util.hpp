#include "global.hpp"

#ifndef UTIL
#define UTIL

/// @brief  Defines a direction (4-cardinal, NESW)
enum Direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

/// @brief  Defines a color (12 colors)
enum Color {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_BRIGHT_RED,
	COLOR_BRIGHT_GREEN,
	COLOR_BRIGHT_YELLOW,
	COLOR_BRIGHT_BLUE,
	COLOR_BRIGHT_MAGENTA,
	COLOR_BRIGHT_CYAN,
	COLOR_BRIGHT_BLACK,
	COLOR_BRIGHT_WHITE,
	COLOR_CLEAR,
	COLOR_COUNT
};

/// @brief  Get a random number between two numbers
int randomInRange(int min, int max);
/// @brief  Returns a random color from the color table
Color randomColor();
/// @brief  Allows for sending a color to the outstream (requires manual color clearing)
std::ostream& operator<<(std::ostream& os, const Color& color);

/// @brief  Clears the console
void clearConsole();
/// @brief  Makes the program wait a certain number of seconds before continuing
void wait(int milliseconds);

/// @brief  prompts the user a message and awaits input, the input is then modified
void promptUser(const char* message, std::string* input);

/// @brief  Converts a string to an unsigned int and handles the error
unsigned int safe_stoul(std::string string);
/// @brief  Converts a string to an integer and handles the error
int safe_stoi(std::string string);

/// @brief  Rolls a random normalized number between 0 and 1, if the number is <= 1/rarity, returns true
bool chance(unsigned int rarity);
/// @brief	Rollas a random normalized number between 0 and 1, if the number is <= rate, returns true
bool chance(double rate);

#endif