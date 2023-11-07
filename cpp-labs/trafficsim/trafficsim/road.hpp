#include "intersection.hpp"
#include "vehicle.hpp"
#include "data.hpp"

#ifndef ROAD
#define ROAD

/// @brief	A queue of vehicles
class VehicleQueue {
private:
	std::list<Vehicle*> vehicles;
public:
	std::list<Vehicle*> Get();
	void Enter(Vehicle* vehicle);
	void Exit();
};

/// @brief	Stores two lanes of traffic
struct Road {
	Direction direction;
	std::list<Place*> places;
	VehicleQueue vehicles;

	bool IsOpen();
	void SpawnVehicle(TrafficData* data);

	static Road BuildRoad(Place places[GRID_SIZE][GRID_SIZE], Direction dir);
};

#endif