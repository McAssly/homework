#include <iostream>
using namespace std;

// define constants
#define TRACK_LENGTH 10
#define MAX_TRAIN_COUNT 4
#define MAX_ROUNDS 50



/// <summary>
/// a train track segment, stores the segments connected to it, and switches to it, and what train is on it
/// </summary>
struct Segment {
	Segment* next;
	Segment* prev;

	Segment* next_switch;
	Segment* prev_switch;

	int train;
};


// prototype functions

void initializeTracks(Segment*& inner_track, Segment*& outer_track);
void initializeTrains(Segment**& trains, Segment* inner_track, Segment* outer_track);
void moveTrains(Segment**& trains);
int randInt(int min, int max);
void printTracks(Segment* inner, Segment* outer);
string trainToString(int train);


// main function
int main() {
	srand(time(NULL)); // seed rand

	// 1. initialize the tracks
	Segment* inner_track;
	Segment* outer_track;
	initializeTracks(inner_track, outer_track);


	// 2. add the trains
	Segment** trains;
	initializeTrains(trains, inner_track, outer_track);
	

	// 3. loop through the tracks and print/update them
	for (int round = 0; round < MAX_ROUNDS; round++) {
		// a. print out the current round
		std::cout << "Round: " << round << endl;
		printTracks(inner_track, outer_track);

		// b. move all the trains forward
		moveTrains(trains);
	}


	// 4. output the final round
	std::cout << "Round: " << MAX_ROUNDS << endl;
	printTracks(inner_track, outer_track);


	// 5. delete memory allocation
	delete[] trains;
	delete[] inner_track;
	delete[] outer_track;
}

/// <summary>
/// Initializes an inner and outer track
/// </summary>
void initializeTracks(Segment*& inner_track, Segment*& outer_track) {
	// allocate the inner and outer tracks
	inner_track = new Segment[TRACK_LENGTH];
	outer_track = new Segment[TRACK_LENGTH];

	// loop through each segment in both tracks
	for (int i = 0; i < TRACK_LENGTH; i++) {
		// Initialize the inner track
		inner_track[i] = {}; // set the segment
		// set the connections along the track
		inner_track[i].prev = (i - 1 >= 0) ?		   &inner_track[i - 1] : &inner_track[TRACK_LENGTH - 1];
		inner_track[i].next = (i + 1 < TRACK_LENGTH) ? &inner_track[i + 1] : &inner_track[0];
		// set the connections to the track
		inner_track[i].next_switch = (i + 1 < TRACK_LENGTH) ? &outer_track[i + 1] : &outer_track[0];
		inner_track[i].prev_switch = (i - 1 >= 0) ?			  &outer_track[i - 1] : &outer_track[TRACK_LENGTH - 1];
		inner_track[i].train = 0;

		// Initialize the outer track
		outer_track[i] = {}; // set the segment
		// set the conenctions along the track
		outer_track[i].prev = (i - 1 >= 0) ?		   &outer_track[i - 1] : &outer_track[TRACK_LENGTH - 1];
		outer_track[i].next = (i + 1 < TRACK_LENGTH) ? &outer_track[i + 1] : &outer_track[0];
		// set the connections to the other track
		outer_track[i].next_switch = (i + 1 < TRACK_LENGTH) ? &inner_track[i + 1] : &inner_track[0];
		outer_track[i].prev_switch = (i - 1 >= 0) ?			  &inner_track[i - 1] : &inner_track[TRACK_LENGTH - 1];
		outer_track[i].train = 0;
	}
}


/// <summary>
/// Initializes an array of segment pointers that point to a valid train segment
/// </summary>
void initializeTrains(Segment**& trains, Segment* inner_track, Segment* outer_track) {
	// allocate memory to the trains
	trains = new Segment * [MAX_TRAIN_COUNT];
	// loop until every train has been added
	int i = 0;
	while (i < MAX_TRAIN_COUNT) {
		// grab a random index between 0 and both track lengths combined
		int index = rand() % (TRACK_LENGTH * 2);
		// if the second half of the length, refer to the outer track
		if (index >= TRACK_LENGTH) {
			// compensate for the added length by subtracting it
			if (outer_track[index - TRACK_LENGTH].train == 0) { // if there is no train there add one
				outer_track[index - TRACK_LENGTH].train = rand() % 2 == 0 ? 1 : -1; // randomize direction (-1 || 1)
				trains[i] = &outer_track[index - TRACK_LENGTH]; // set the train array to point to it
				i++; // train was successfully added
			}
		}
		// otherwise refer to the inner track
		else {
			if (inner_track[index].train == 0) {
				inner_track[index].train = rand() % 2 == 0 ? 1 : -1;
				trains[i] = &inner_track[index];
				i++;
			}
		}
	}
}


/// <summary>
/// Moves the given train segments in their respective directions
/// </summary>
void moveTrains(Segment**& trains) {
	// loop through every train
	for (int i = 0; i < MAX_TRAIN_COUNT; ++i) {
		// get the current train segment
		Segment* train = trains[i];

		// if the train isn't null, and the train is moving left (-1 : previous)
		if (train && train->train == -1) {
			// move to the left (refers to previous in the array)
			if (train->prev && train->prev->train == 0) { // if it can move along its on track, remain within
				// move along the same track to the left
				train->prev->train = -1;
				train->train = 0; // remove train from old position
				trains[i] = train->prev; // update train pointer
			}
			else if (train->prev_switch) { // if it cannot move on its own track, switch tracks
				// switch tracks to the left
				train->prev_switch->train = -1;
				train->train = 0;
				trains[i] = train->prev_switch;
			}
		}

		// if the train isn't null, and the train is moving right (+1 : next)
		else if (train && train->train == 1) {
			if (train->next && train->next->train == 0) {
				// move along the same track to the right
				train->next->train = 1;
				train->train = 0;
				trains[i] = train->next;
			}
			else if (train->next_switch) {
				// switch tracks to the right
				train->next_switch->train = 1;
				train->train = 0;
				trains[i] = train->next_switch;
			}
		}
	}
}




/// <summary>
/// converts the given train direction to its respective arrow
/// </summary>
/// <param name="train"></param>
/// <returns></returns>
string trainToString(int train) {
	switch (train) {
	case -1:
		return "<";
	case 1:
		return ">";
	default: return "-";
	}
}


/// <summary>
/// gets a random int between the given min, max
/// </summary>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns></returns>
int randInt(int min, int max) {
	return rand() % (max - min + 1) + min;
}

/// <summary>
/// given the inner/outer tracks prints the 1st or 2nd half of the circlular track
/// </summary>
/// <param name="inner"></param>
/// <param name="outer"></param>
/// <param name="track"></param>
/// <param name="half"></param>
void printTrackCircular(Segment* inner, Segment* outer, int track, int half) {
	// print the header for the track
	if (track == 0) std::cout << "+--"; // outer header
	else std::cout << "|  ";			// inner header
	// print the track
	for (int i = TRACK_LENGTH / 2 * half; i < (TRACK_LENGTH / 2) * (half + 1); i++) {
		string out = (track == 0) ? trainToString(inner[i].train) : trainToString(outer[i].train);
		std::cout << out;
		if (i < (TRACK_LENGTH / 2 * (half + 1)) - 1) {
			std::cout << "--";
		}
	}
	// print the footer for the track
	// set the switcher row
	string out = "|  x  x  x  x  x  |";
	// output line endings, then the switcher/spacer rows
	if (track == 0) {
		std::cout << "--+" << endl;
		if (half == 1) out = "";
	}
	else {
		std::cout << "  |" << endl;
		// print the switcher row
		if (half == 0) out = "|  |           |  |";
	}
	std::cout << out << endl;
}

/// <summary>
/// prints the outer and inner tracks (circular)
/// </summary>
/// <param name="inner"></param>
/// <param name="outer"></param>
void printTracks(Segment* inner, Segment* outer) {
	// top half of the tracks
	for (int track = 0; track < 2; track++) {
		printTrackCircular(inner, outer, track, 0);
	}
	for (int track = 1; track >= 0; track--) {
		printTrackCircular(inner, outer, track, 1);
	}
}