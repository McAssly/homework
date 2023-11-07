#include "global.hpp"
#include "intersection.hpp"
#include "util.hpp"

#ifndef VEHICLE
#define VEHICLE

static const double TRUCK_SPAWN_RATE = 0.1;
static const double BUS_SPAWN_RATE = 0.1;
static const double MOTORCYCLE_SPAWN_RATE = 0.2;

static const int SPEED = 2;
static const int CAR_WEIGHT = 2;
static const int TRUCK_WEIGHT = 3;
static const int BUS_WEIGHT = 4;
static const int MOTORCYCLE_WEIGHT = 1;

static const char CAR_CHAR = 'C';
static const char TRUCK_CHAR = 'T';
static const char BUS_CHAR = 'B';
static const char MOTORCYCLE_CHAR = 'M';

static const int MIN_CARGO_WEIGHT = 2;
static const int MAX_CARGO_WEIGHT = 10;
static const int MIN_PASSENGER_COUNT = 0;
static const int MAX_PASSENGER_COUNT = 20;
static const std::string BUS_NAMES[4] = {
	"MetroTransit",
	"PrivateShuttle",
	"SchoolExpress",
	"CampusRider"
};
static const std::string MOTORCYCLE_BRANDS[12] = {
	"Honda",
	"BMW",
	"Kawasaki",
	"KTM",
	"Benelli",
	"Harley",
	"Triumph",
	"Yamaha",
	"Ducati",
	"Suzuki",
	"Aprilia",
	"Vespa"
};

class Vehicle {
public:
	int length = 1;
	std::vector<Place*> pieces;
	int speed;
	int weight;
	int move_counter = 0;
	Direction direction;

	Vehicle();
	Vehicle(Place* head, Direction dir);
	Vehicle(Place* head, int length, Direction dir);

	virtual void Print() const;
	bool IsFinal();
	void Build(Place places[GRID_SIZE][GRID_SIZE]);
	void Move();
};

class Car : public Vehicle {
private:
	Color color;
public:
	Car(Place* head, Direction dir);
	void Print() const override;
};

class Truck : public Vehicle {
private:
	Color color;
	int cargo_weight;
public:
	Truck(Place* head, Direction dir);
	void Print() const override;
	int GetCargoWeight();
};

class Bus : public Vehicle {
private:
	std::string name;
	int passengers;
public:
	Bus(Place* head, Direction dir);
	void Print() const override;
	std::string GetName();
	int GetPassengers();
};

class Motorcycle : public Vehicle {
private:
	std::string brand;
public:
	Motorcycle(Place* head, Direction dir);
	void Print() const override;
	std::string GetBrand();
};

#endif