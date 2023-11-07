#include <iostream>
#include <string>
using namespace std;

#define MAX 100
#define MIN 10
#define TAB "\t"


bool cycle(bool boolean) {
	if (boolean)
		return false;
	return true;
}


int main() {
	srand(time(NULL)); // Seed the time
	int marbles = rand() % (MAX - MIN + 1) + MIN;
	bool users_turn = true;
	
	// loop through the game until all marbles have been taken
	while (marbles > 1) {
		// 1. cycle the player
		users_turn = cycle(users_turn);

		// 2. output the pile
		std::cout << TAB << "Marble Count: " << marbles << endl;

		// 3. get the amount to take from the pile
		int amount = 0;
		if (users_turn) {
			// ask until the allowed amount is given
			while (amount < 1 || amount > marbles / 2) {
				// ask the user for their amount
				std::cout << TAB << "Enter the amount of marbles to take: (1-" << marbles / 2 << ")" << endl;
				std::cout << TAB << ">> ";
				string input;
				getline(cin, input);
				// set the amount
				amount = std::stoi(input);
			}
		}
		else // computer's turn
		{
			// get a random amount
			amount = rand() % (marbles / 2) + 1;
			// output:
			std::cout << TAB << "Computer's turn: " << amount << endl;
		}

		// 4. subtract the marble count
		marbles -= amount;
	}

	// whoever lost is the last player left on the cycle
	if (users_turn) {
		// the player lost
		std::cout << TAB << "You lost." << endl;
	}
	else {
		// the computer lost
		std::cout << TAB << "You won!" << endl;
	}
}