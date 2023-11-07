// include
#include "cipher.hpp"

// std libraries
#include <iostream>
#include <string>
#include <cctype>

const std::string keyword = "PLAYFAIR";
void read_message(std::string* message);

int main() {
	// initialize playfair cipher
	Playfair cipher = Playfair(keyword);

	// get the message to encrypt
	std::string message;
	read_message(&message);
	
	message = cipher.encrypt(message);
	// output the encrypted message
	std::cout << "   Encrypted: " << message << std::endl;

	message = cipher.decrypt(message, true);
	// output the decrypted message
	std::cout << "   Decrypted: " << message << std::endl;

	return 0;
}

/// <summary>
/// read a message from the user
/// </summary>
/// <param name="message"></param>
/// <returns></returns>
void read_message(std::string* message) {
	// ask user for the message
	std::cout << "  Enter message to encrypt: ";
	std::getline(std::cin, *message); // recieve the message 
	for (char& c : *message) c = std::toupper(c); // convert message to uppercase
}