#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
using namespace std;

#define FRAME_LIMIT 5

// declare global game variables
int width = 0;
int height = 0;


// prototype functions
bool outside_x(int x);
bool outside_y(int y);
vector<bool> parse_row(string input);



/// <summary>
/// A cell for the game of life
/// </summary>
class Cell {
private:
	bool alive;
	int x, y;
	int neightbors;
public:
	/// <summary>
	/// inits an empty cell, uninitialized position
	/// </summary>
	Cell() {
		this->x = NULL;
		this->y = NULL;
		this->neightbors = 0;
		this->alive = false;
	}

	/// <summary>
	/// sets the cell's position
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void set_position(int x, int y) {
		this->x = x;
		this->y = y;
	}

	/// <summary>
	/// set the cell's alive state
	/// </summary>
	/// <param name="alive"></param>
	void set_alive(bool alive) {
		this->alive = alive;
	}


	/// <summary>
	/// determines the number of alive neighbors to the current cell
	/// </summary>
	/// <param name="board"></param>
	/// <returns></returns>
	void count_neighbors(Cell** board) {
		// the neighbors consist of 
		/* every adjacent cell (including diagonals
					position offsets
		- - -		(-1, -1)   ( 0, -1)   ( 1, -1)
		- @ -		(-1,  0)   ( 0,  0)   ( 1,  0)
		- - -		(-1,  1)   ( 0,  1)   ( 1,  1)
		*/
		neightbors = 0;
		// loop through every offset, twice
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i == 0 && j == 0) continue; // skip 0,0
				int nx = x + j; // determine the neighbor's x
				int ny = y + i; // determine the neighbor's y
				if (outside_x(nx) || outside_y(ny)) continue; // skip any out of bounds
				if (board[ny][nx].is_alive()) {
					neightbors++;
				}
			}
		}
	}

	/// <summary>
	/// returns the number of neighbors the cell has
	/// </summary>
	/// <returns></returns>
	int get_neighbors() {
		return neightbors;
	}

	/// <summary>
	/// swaps between alive or dead
	/// </summary>
	void swap() {
		alive = !alive;
	}

	/// <summary>
	/// returns whether the cell is alive or not
	/// </summary>
	/// <returns></returns>
	bool is_alive() { return alive; }

	/// <summary>
	/// returns the x position
	/// </summary>
	/// <returns></returns>
	int X() { return x; }

	/// <summary>
	/// returns the y position
	/// </summary>
	/// <returns></returns>
	int Y() { return y; }

	/// <summary>
	/// returns the readable state of the cell
	/// </summary>
	/// <returns></returns>
	string to_string() {
		if (alive) return "@";
		else return "-";
	}
};


// prototype cell related functions
void print_board(Cell** board);



int main() {
	// ask the user for the game configuration
	std::cout << "enter game configuration (1 row at a time)" << endl;
	std::cout << "example input: 0 1 0 1 0 0 0 0 1" << endl;
	std::cout << "type: '' to end configuration" << endl;
	// determine configuration based on given rows
	string input;
	// init 2d vectors for dynamic creation of true/false data for game board creation
	vector<vector<bool>> alive;
	while (true) {
		// first get the input
		std::cout << height << "> ";
		getline(cin, input);
		// if input is the escape char, then break the configuration loop
		if (input == "") break;
		// otherwise parse the row given by the user
		vector<bool> row = parse_row(input);
		// if this is the first row given, set the width of the game board
		if (height == 0) width = row.size();
		// if the row's size is not consistent (the same) as the width throw an exception
		if (row.size() != width) {
			throw new exception("incorrect width, make sure width is consistent");
		}
		// all is good add the row to the alive grid
		alive.push_back(row);
		// increase the height size
		height++;
	}

	// print out game board size
	std::cout << "read size: " << width << "x" << height << endl;


	// initialize the game board
	Cell** board = new Cell*[height]; // init: rows
	for (int y = 0; y < height; y++) {// init: columns
		board[y] = new Cell[width];
	}

	// init every single cell
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			// set the cell's position
			board[y][x].set_position(x, y);
			if (alive[y][x]) board[y][x].swap();
		}
	}


	// start the game loop
	int frame = 0;
	while (frame < FRAME_LIMIT) {
		// print the board each iteration
		std::cout << "frame: " << frame << "\n";
		print_board(board);
		
		// first calculate the number of neighbors each cell currently has
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				board[y][x].count_neighbors(board);
			}
		}

		// swap from dead or alive based on set conditions
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				// spawn new cell if there are exactly 3 neighbors and the cell is not yet alive
				// kill the cell if it is too lonely or too crowded
				if ((board[y][x].get_neighbors() == 3 && !board[y][x].is_alive())
					|| ((board[y][x].get_neighbors() <= 1 || board[y][x].get_neighbors() >= 4) && board[y][x].is_alive())) {
					board[y][x].swap();
				}
			}
		}

		frame++;
	}



	// delete allocated memory
	for (int y = 0; y < height; y++) {
		delete[] board[y];
	}
	delete[] board;
	return 0;
}




/// <summary>
/// prints the given game board
/// </summary>
/// <param name="board"></param>
void print_board(Cell** board) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			std::cout << board[y][x].to_string() << " ";
		}
		std::cout << "\n";
	}
}


/// <summary>
/// checks if the given x is out of bounds
/// </summary>
/// <param name="x"></param>
/// <returns></returns>
bool outside_x(int x) {
	return x >= width || x < 0;
}

/// <summary>
/// checks if the given y is out of bounds
/// </summary>
/// <param name="y"></param>
/// <returns></returns>
bool outside_y(int y) {
	return y >= height || y < 0;
}

/// <summary>
/// parses the given string input of a row configuration into usable data
/// </summary>
/// <param name="input"></param>
/// <returns></returns>
vector<bool> parse_row(string input) {
	// init output
	vector<bool> result;
	// input should look like:
	// 0 1 0 1 0 1 0 1 0 1 0 1
	for (char c : input) {
		if (c == ' ' || c == '\n') continue; // skip whitespace
		result.push_back(c == '1');
	}
	return result;
}