#include <string>
#include <vector>

#ifndef CIPHER
#define CIPHER

class Playfair {
private:
	std::vector<std::string> grid;
	static std::vector<std::string> to_digraphs(std::string word);
	static void reform(std::string* word);
	std::string _encrypt(std::string digraph);
	std::string _decrypt(std::string digraph);
	int getx(char c);
	int gety(char c);
	int height();
	int width();
public:
	static const std::string letters;
	Playfair(std::string keyword);
	std::string encrypt(std::string word);
	std::string decrypt(std::string word, bool reform=false);
};

#endif