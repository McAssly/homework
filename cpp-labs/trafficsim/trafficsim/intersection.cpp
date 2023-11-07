#include "intersection.hpp"
#include "vehicle.hpp"
#include "global.hpp"

Place::Place(bool is_free) : free(is_free) {}

void Place::SetPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

/// @brief	Links the place to another in a given direction
void Place::Link(Direction dir, Place* place) {
	this->links[dir] = place;
}

bool Place::PreviousIsFree(Place places[GRID_SIZE][GRID_SIZE], Direction dir) {
	int px = x;
	int py = y;
	switch (dir) {
	case NORTH: py++; break;
	case EAST: px--; break;
	case SOUTH: py--; break;
	case WEST: px++; break;
	}
	if (px < 0 || px >= GRID_SIZE || py < 0 || py >= GRID_SIZE) return false; // out of bounds
	else return places[py][px].IsFree();
}

Place* Place::Previous(Place places[GRID_SIZE][GRID_SIZE], Direction dir) {
	int px = x;
	int py = y;
	switch (dir) {
	case NORTH: py++; break;
	case EAST: px--; break;
	case SOUTH: py--; break;
	case WEST: px++; break;
	}
	return &places[py][px];
}

bool Place::NextIsFree(Direction dir) {
	Place* next = links[dir];
	if (next == nullptr) return false;
	return next->IsFree();
}

Place* Place::Next(Direction dir) {
	if (!this->NextIsFree(dir)) return nullptr;
	else return links[dir];
}

/// @brief	Checks if the place is free
bool Place::IsFree() {
	return this->free;
}

/// @brief	Checks if the place is empty
bool Place::IsEmpty() {
	for (int d = 0; d < 4; d++) {
		if (links[d] != nullptr) {
			return false;
		}
	}
	return true;
}

/// @brief	Checks if the place is the final node in a road
bool Place::IsFinal() {
	return this->final;
}

/// @brief	Sets the place to a road's final node
void Place::SetFinal() {
	this->final = true;
}

void Place::Occupy(Vehicle* vehicle) {
	this->occupee = vehicle;
	this->free = false;
}

void Place::UnOccupy() {
	this->occupee = nullptr;
	this->free = true;
}

Vehicle* Place::Occupee() {
	return occupee;
}

void Place::Open() {
	this->open = true;
}

void Place::Close() {
	this->open = false;
}

bool Place::IsOpen() {
	return this->open;
}

bool Place::operator==(const Place& other) const {
	return this->x == other.x && this->y == other.y;
}

// ###################################################################
//					    TRAFFIC LIGHT METHODS
// ###################################################################

/// @brief	Constructs a traffic light with a given state and timer settings
TrafficLight::TrafficLight(TrafficState state, int green_duration, int opposing_green_duration, Place* gate1, Place* gate2) {
	// set max timers
	this->yellow_duration = 2 * SPEED + 1;
	this->green_duration = green_duration;
	this->red_duration = yellow_duration + (opposing_green_duration + 5);

	this->gate1 = gate1;
	this->gate2 = gate2;

	// set the state
	this->state = state;
	this->SetTimer(); // set the timer
	this->ChangeGates();
}

/// @brief	Sets the timer for the traffic light based on its current state
void TrafficLight::SetTimer() {
	switch (this->state) {
	case TRAFFIC_LIGHT_GREEN:
		this->timer = this->green_duration;
		break;
	case TRAFFIC_LIGHT_YELLOW:
		this->timer = this->yellow_duration;
		break;
	case TRAFFIC_LIGHT_RED:
		this->timer = this->red_duration;
		break;
	}
}

/// @brief	Updates the traffic light
void TrafficLight::Update() {
	if (this->timer > 0) { // update the timer if greater than 0
		this->timer--;
	}
	else { // otherwise change state and reset the timer
		switch (this->state) {
		case TRAFFIC_LIGHT_GREEN:
			this->state = TRAFFIC_LIGHT_YELLOW;
			this->SetTimer();
			break;
		case TRAFFIC_LIGHT_YELLOW:
			this->state = TRAFFIC_LIGHT_RED;
			this->SetTimer();
			break;
		case TRAFFIC_LIGHT_RED:
			this->state = TRAFFIC_LIGHT_GREEN;
			this->SetTimer();
			break;
		}
	}
	this->ChangeGates();
}

void TrafficLight::ChangeGates() {
	switch (this->state) {
	case TRAFFIC_LIGHT_GREEN:
		this->gate1->Open();
		this->gate2->Open();
		break;
	case TRAFFIC_LIGHT_YELLOW: case TRAFFIC_LIGHT_RED:
		this->gate1->Close();
		this->gate2->Close();
		break;
	}
}

// ###################################################################
//						   OUTPUT METHODS
// ###################################################################

/// @brief	Handles traffic lights in the outstream
std::ostream& operator<<(std::ostream& os, TrafficLight& traffic_light) {
	switch (traffic_light.state) {
	case TRAFFIC_LIGHT_GREEN:
		os << COLOR_GREEN;
		break;
	case TRAFFIC_LIGHT_YELLOW:
		os << COLOR_YELLOW;
		break;
	case TRAFFIC_LIGHT_RED:
		os << COLOR_RED;
		break;
	}
	os << '@' << COLOR_CLEAR;
	return os;
}
std::ostream& operator<<(std::ostream& os, Place& place) {
	if (place.IsEmpty() && !place.IsFinal())
		os << ' ';
	else {
		if (place.IsFinal())
			os << COLOR_BRIGHT_BLACK << '#' << COLOR_CLEAR;
		else if (place.IsFree() && place.Occupee() == nullptr && place.IsOpen())
			os << COLOR_BRIGHT_BLACK << '*' << COLOR_CLEAR;
		else
			os << 'x';
	}
	return os;
}
std::ostream& operator<<(std::ostream& os, Direction& direction) {
	switch (direction) {
	case NORTH: os << "NORTH"; return os;
	case EAST: os << "EAST"; return os;
	case SOUTH: os << "SOUTH"; return os;
	case WEST: os << "WEST"; return os;
	}
	return os;
}