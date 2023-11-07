#include "vehicle.hpp"
#include "util.hpp"

// ##############################################################
//			    			THE CAR
// ##############################################################

/// @brief	Constructs the a Car at the head position and will move in the given direction
Car::Car(Place* head, Direction dir) {
	this->length = 2;
	this->pieces.push_back(head);
	this->pieces[0]->Occupy(this);
	this->pieces.push_back(nullptr);
	this->direction = dir;
	this->color = randomColor();
	this->speed = SPEED;
	this->weight = CAR_WEIGHT;
}

/// @brief	Prints out the car
void Car::Print() const {
	std::cout << this->color << CAR_CHAR << COLOR_CLEAR << ' ';
}

// ##############################################################
//			    		   THE TRUCK
// ##############################################################

/// @brief	Constructs a truck at the given place
Truck::Truck(Place* head, Direction dir) {
	this->length = 5;
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			pieces.push_back(head);
			pieces[0]->Occupy(this);
		}
		else pieces.push_back(nullptr);
	}
	this->direction = dir;
	this->color = randomColor();
	this->speed = SPEED;
	this->weight = TRUCK_WEIGHT;
	this->cargo_weight = randomInRange(MIN_CARGO_WEIGHT, MAX_CARGO_WEIGHT);
}

/// @brief	Prints out the truck
void Truck::Print() const {
	std::cout << this->color << TRUCK_CHAR << COLOR_CLEAR << ' ';
}

int Truck::GetCargoWeight() {
	return cargo_weight;
}

// ##############################################################
//			    			THE BUS
// ##############################################################

/// @brief	Constructs a bus
Bus::Bus(Place* head, Direction dir) {
	this->length = 4;
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			pieces.push_back(head);
			pieces[0]->Occupy(this);
		}
		else pieces.push_back(nullptr);
	}
	this->direction = dir;
	this->speed = SPEED;
	this->weight = BUS_WEIGHT;
	this->passengers = randomInRange(MIN_PASSENGER_COUNT, MAX_PASSENGER_COUNT);
	this->name = BUS_NAMES[randomInRange(0, 3)];
}

/// @brief	Prints out the bus
void Bus::Print() const {
	std::cout << COLOR_BRIGHT_WHITE << BUS_CHAR << COLOR_CLEAR << ' ';
}

std::string Bus::GetName() {
	return name;
}

int Bus::GetPassengers() {
	return passengers;
}

// ##############################################################
//		    	       	THE MOTORCYCLE
// ##############################################################

/// @brief	Constructs a motorcycle
Motorcycle::Motorcycle(Place* head, Direction dir) {
	this->length = 1;
	this->pieces.push_back(head);
	this->pieces[0]->Occupy(this);
	this->direction = dir;
	this->speed = SPEED / 2;
	this->weight = MOTORCYCLE_WEIGHT;
	this->brand = MOTORCYCLE_BRANDS[randomInRange(0, 11)];
}

/// @brief	Prints out a motorcycle
void Motorcycle::Print() const {
	std::cout << COLOR_BRIGHT_WHITE << MOTORCYCLE_CHAR << COLOR_CLEAR << ' ';
}

std::string Motorcycle::GetBrand() {
	return brand;
}

// ##############################################################
//			    	   VEHICLE BASE CLASS
// ##############################################################

/// @brief	Default constructor
Vehicle::Vehicle() {
	this->length = 0;
	this->direction = SOUTH;
	this->speed = 0;
	this->weight = 0;
}

/// @brief	Constructs a vehicle with default length = 1
Vehicle::Vehicle(Place* head, Direction dir) {
	this->length = 1;
	pieces.push_back(head);
	pieces[0]->Occupy(this);
	this->direction = dir;
	this->speed = SPEED;
	this->weight = length;
}

/// @brief	Construct a basic vehicle of varying size
Vehicle::Vehicle(Place* head, int length, Direction dir) {
	this->length = length;
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			pieces.push_back(head);
			pieces[0]->Occupy(this);
		}
		else pieces.push_back(nullptr);
	}
	this->direction = dir;
	this->speed = SPEED;
	this->weight = length;
}

/// @brief	Checks if the vehicle has reached the final space on the road
/// @note	Deletes every piece premptively, careful with call
bool Vehicle::IsFinal() {
	if (length == 0) return true;			// delete an empty vehicle
	if (this->pieces[0]->IsFinal()) {		// if the head is at the end
		for (int i = 0; i < length; i++) {	// premptivly delete all pieces
			pieces[i]->UnOccupy();
		}
		return true;
	}
	return false;
}

/// @brief	Builds a vehicle that has more than 1 piece
void Vehicle::Build(Place places[GRID_SIZE][GRID_SIZE]) {
	if (length <= 1 || (length >= 1 && pieces[0] == nullptr)) return;
	for (int i = 1; i < length; i++) {
		if (pieces[i] != nullptr) continue; // skip already built pieces
		if (pieces[i] == nullptr && pieces[i - 1] != nullptr && pieces[i - 1]->PreviousIsFree(places, this->direction)) {
			pieces[i] = pieces[i - 1]->Previous(places, this->direction);
			pieces[i]->Occupy(this);
			return; // exit function (build on piece at a time)
		}
	}
}

/// @brief	Prints out the vehicle
void Vehicle::Print() const {
	std::cout << 'V' << ' ';
}

/// @brief	Moves the vehicle in their direction
void Vehicle::Move() {
	if (length == 0) return;
	if (pieces[0]->IsOpen()) {
		if (move_counter >= speed && pieces[0]->NextIsFree(direction)) {
			// move forward
			for (int i = 0; i < length; i++) {
				if (pieces[i] != nullptr) {
					Place* next = pieces[i]->Next(direction);
					pieces[i]->UnOccupy();
					next->Occupy(this);
					pieces[i] = next;
				}
			}
			// reset move counter
			move_counter = 0;
		}
		else {
			move_counter++;
		}
	}
}