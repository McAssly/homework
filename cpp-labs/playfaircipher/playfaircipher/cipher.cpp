#include "cipher.hpp"
#include <iostream>

// init constants
const std::string Playfair::letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/// <summary>
/// constructs a playfair cipher, keyword cannot have duplicate letters
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
Playfair::Playfair(std::string keyword) {
	// 1. remove all letters of keyword from letters
	//		-> remove I or J based on the keyword
	char removable = (keyword.find('J') != std::string::npos) ? 'I' : 'J'; // remove J by default
	std::string alphabet = "";
	for (char c : letters) {
		// if the keyword does not contain the letter add it
		if (keyword.find(c) == std::string::npos && c != removable) {
			alphabet += c;
		}
	}

	// 2. build cipher
	std::string build = keyword + alphabet;

	// 3. generate the 5x5 grid
	for (int y = 0; y < 5; y++) {
		std::string row = "";
		for (int x = 0; x < 5; x++) {
			row += build[x + (y * 5)];
		}
		grid.push_back(row);
	}
}


/// <summary>
/// encrypts the given word
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
std::string Playfair::encrypt(std::string word) {
	std::string encrypted = "";
	// split into a list of digraphs
	std::vector<std::string> digraphs = to_digraphs(word);
	for (std::string digraph : digraphs) {
		encrypted += _encrypt(digraph);
	}
	return encrypted;
}

/// <summary>
/// encrypts the given digraph (two letters)
/// </summary>
/// <param name="digraph"></param>
/// <returns></returns>
std::string Playfair::_encrypt(std::string digraph) {
	std::string encrypted = "";
	// get the position of each letter
	int ax = getx(digraph[0]);
	int ay = gety(digraph[0]);
	int bx = getx(digraph[1]);
	int by = gety(digraph[1]);
	// if in same COL:    meaning their x is the same
	if (ax == bx) {
		// move each letter down 1 (wrap around if necessary)
		ax++; // move 1st letter down 1
		bx++; // move second letter down 1
		// handle wrapping around the table
		if (ax >= width()) ax = 0;
		if (bx >= width()) bx = 0;
	}
	// if in same ROW:    meaning their y is the same
	else if (ay == by) {
		// move each letter to the right 1 (wrap around if necessary)
		ay++; // move letter 1 right
		by++; // move letter 2 right
		// handle wrapping around the table
		if (ay >= height()) ay = 0;
		if (by >= height()) by = 0;
	}
	// else:
	else {
		// for second letter (b) swap its x with letter 1 (a)
		int tempx = bx;
		bx = ax;
		// For first letter (a) swap its x with letter 2 (b)
		ax = tempx;
	}
	// set the new letters
	encrypted += grid[ay][ax];
	encrypted += grid[by][bx];
	return encrypted;
}

/// <summary>
/// decrypts the given word
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
std::string Playfair::decrypt(std::string word, bool reform) {
	std::string decrypted = "";
	// split into a list of digraphs
	std::vector<std::string> digraphs = to_digraphs(word);
	for (std::string digraph : digraphs) {
		decrypted += _decrypt(digraph);
	}
	if (reform) Playfair::reform(&decrypted);
	return decrypted;
}

/// <summary>
/// decrypts the given digraph (two letters)
/// </summary>
/// <param name="digraph"></param>
/// <returns></returns>
std::string Playfair::_decrypt(std::string digraph) {
	std::string decrypted = "";
	// get the position of each letter
	int ax = getx(digraph[0]);
	int ay = gety(digraph[0]);
	int bx = getx(digraph[1]);
	int by = gety(digraph[1]);
	// if in same COL:   meaning their x is the same
	if (ax == bx) {
		// move each letter up 1 (wrap around if necessary)
		ax--; // move 1st letter up 1
		bx--; // move second letter up 1
		// handle wrapping around the table
		if (ax < 0) ax = width() - 1;
		if (bx < 0) bx = width() - 1;
	}
	// if in same ROW:   meaning their y is the same
	else if (ay == by) {
		// move each letter to the left 1 (wrap around if necessary)
		ay--; // move letter 1 left
		by--; // move letter 2 left
		// handle wrapping around the table
		if (ay < 0) ay = height() - 1;
		if (by < 0) by = height() - 1;
	}
	// else:
	else {
		// for second letter (b) swap its x with letter 1 (a)
		int tempx = bx;
		bx = ax;
		// For first letter (a) swap its x with letter 2 (b)
		ax = tempx;
	}
	// set the new letters
	decrypted += grid[ay][ax];
	decrypted += grid[by][bx];
	return decrypted;
}

/// <summary>
/// converts the given word into a vector of digraphs
/// </summary>
/// <param name="word"></param>
/// <returns></returns>
std::vector<std::string> Playfair::to_digraphs(std::string word) {
	std::vector<std::string> digraphs;
	int count = 0; // init letter counter
	std::string digraph = ""; // init digraph builder
	for (size_t i = 0; i < word.length() + 1; i++) {
		if (count >= 2) {
			digraphs.push_back(digraph);
			digraph = ""; // reset digraph
			count = 0; // reset letter counter
			if (i >= word.length()) break;
		}
		// add letter to digraph
		digraph += word[i];
		// if not the final letter in the word (peek forward)
		if (i != word.length() - 1) {
			// check for duplicate letter
			if (word[i + 1] == word[i]) {
				digraph += "X"; // add duplicate letter identifier
				count++; // append count
			}
		}
		count++; // append count
	}
	return digraphs;
}

/// <summary>
/// reforms the duplicate letters back to normal (from *X* to **)
/// </summary>
/// <param name="word"></param>
void Playfair::reform(std::string* word) {
	std::string reformed = "";
	for (int i = 0; i < word->length(); i++) {
		if (i > 0 && i < word->length()-1 
			&& (word->at(i) == 'X' && word->at(i - 1) == word->at(i + 1))) 
			continue; // SKIP 'X' only if the surrounding characters are equal
		reformed += word->at(i);
	}
	*word = reformed; // set the reformed word
}

/// <summary>
/// get the x position of the given char
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
int Playfair::getx(char c) {
	for (std::string row : grid) {
		if (row.find(c) != std::string::npos) {
			return row.find(c);
		}
	}
	return -1;
}

/// <summary>
/// get the y position of the given char
/// </summary>
/// <param name="c"></param>
/// <returns></returns>
int Playfair::gety(char c) {
	for (size_t i = 0; i < grid.size(); i++) {
		if (grid[i].find(c) != std::string::npos) {
			return i;
		}
	}
	return -1;
}

/// <summary>
/// returns the height of the playfair grid
/// </summary>
/// <returns></returns>
int Playfair::height() {
	return grid.size();
}

/// <summary>
/// returns the width of the playfair grid
/// </summary>
/// <returns></returns>
int Playfair::width() {
	return grid[0].length();
}
