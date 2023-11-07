#include "global.hpp"
#include "vehicle.hpp"

#ifndef DATA
#define DATA

struct TrafficData {
	int id;
	// number of cycles the simulation ran
	int cycles = 0;
	
	// total count for each vehicle type in each direction
	int cars[4] = { 0 };
	int trucks[4] = { 0 };
	int buses[4] = { 0 };
	int motorcycles[4] = { 0 };

	// misc vehicle data
	int total_passengers = 0;
	std::map<std::string, int> bus_names;
	std::map<std::string, int> motorcycle_brands;

	// user settings
	int vehicle_spawn_rate = 0;
	int tl_vertical_timer = 0;
	int tl_horizontal_timer = 0;

	// the total weight applied on the intersection
	int total_weight = 0;

	TrafficData(int id, int vsr, int tlvt, int tlht);
	void Write(const std::string& filename);
};

#endif