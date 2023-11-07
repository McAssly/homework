#include "global.hpp"
#include "util.hpp"

#ifndef INTERSECTION
#define INTERSECTION

class Vehicle;

/// @brief	A place of asphalt where a vehicle can drive
class Place {
private:
	int x, y;
	bool final = false;
	bool free;							// whether the place is free or occupied
	Place* links[4] = { nullptr };		// link to next place (nullptr means no connection)
	Vehicle* occupee;
	bool open = true;

public:
	Place(bool is_free = false);	// constructs a new place node
	void SetPosition(int x, int y);
	void Link(Direction dir, Place* place); // links this place to another in the given direction

	bool PreviousIsFree(Place places[GRID_SIZE][GRID_SIZE], Direction dir);	// checks if the place in the opposite direction is free or not
	Place* Previous(Place places[GRID_SIZE][GRID_SIZE], Direction dir);		// returns the place that is behind this one
	bool NextIsFree(Direction dir);		// returns the place in the next direction, only if its free
	Place* Next(Direction dir);			// returns the next place in the given direction
	bool IsFree();						// returns if this place is free or not
	bool IsEmpty();						// checks if the place is empty or not
	bool IsFinal();
	void SetFinal();
	void Occupy(Vehicle* vehicle);
	void UnOccupy();
	Vehicle* Occupee();
	void Open();
	void Close();
	bool IsOpen();

	bool operator==(const Place& other) const;
};

/// @brief	Stores the state of a traffic light
enum TrafficState {
	TRAFFIC_LIGHT_GREEN,
	TRAFFIC_LIGHT_YELLOW,
	TRAFFIC_LIGHT_RED
};

/// @brief	Controls traffic
struct TrafficLight {
	// timer maximums
	int red_duration;
	int yellow_duration;
	int green_duration;

	// traffic state
	TrafficState state;
	int timer;

	Place* gate1;
	Place* gate2;

	/// @brief	Constructs a traffic light with a given state and timer settings
	TrafficLight(TrafficState state, int green_duration, int opposing_green_duration, Place* gate1, Place* gate2);
	/// @brief	Sets the timer for the traffic light based on its current state
	void SetTimer();
	/// @brief	Updates the traffic light
	void Update();
	/// @brief	Changes the gates based on the current state
	void ChangeGates();
};

// ###################################################################
//						   OUTPUT METHOD
// ###################################################################
std::ostream& operator<<(std::ostream& os, TrafficLight& traffic_light);
std::ostream& operator<<(std::ostream& os, Place& place);
std::ostream& operator<<(std::ostream& os, Direction& direction);

#endif