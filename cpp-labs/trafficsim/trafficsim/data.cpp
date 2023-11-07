#include "data.hpp"

TrafficData::TrafficData(int id, int vsr, int tlvt, int tlht) {
	this->id = id;
	this->vehicle_spawn_rate = vsr;
	this->tl_vertical_timer = tlvt;
	this->tl_horizontal_timer = tlht;
	for (std::string bus : BUS_NAMES) {
		bus_names[bus] = 0;
	}
	for (std::string brand : MOTORCYCLE_BRANDS) {
		motorcycle_brands[brand] = 0;
	}
}

void TrafficData::Write(const std::string& filename) {
	std::ofstream of(filename, std::ios::app);
	if (of.is_open()) {
		of << "[Dataset " << id << "]" << std::endl;
		of << "(number of cycles) " << cycles << std::endl;
		// write out global settings
		of << "<global settings>" << std::endl;
		of << " Spawn Rates:" << std::endl;
		of << "  TruckSpawnRate = " << TRUCK_SPAWN_RATE << std::endl;
		of << "  BusSpawnRate = " << BUS_SPAWN_RATE << std::endl;
		of << "  MotorcycleSpawnRate = " << MOTORCYCLE_SPAWN_RATE << std::endl;
		of << " VehicleSpeed = " << SPEED << std::endl;
		// write out user settings
		of << "<user settings>" << std::endl;
		of << " VehicleSpawnRate = " << vehicle_spawn_rate << std::endl;
		of << " Traffic Lights: " << std::endl;
		of << "  VerticalTimer = " << tl_vertical_timer << std::endl;
		of << "  HorizontalTimer = " << tl_horizontal_timer << std::endl;
		// write out the vehicle datasets
		of << "<vehicle data>" << std::endl;
		int sum_cars = cars[NORTH] + cars[EAST] + cars[SOUTH] + cars[WEST];
		int sum_trucks = trucks[NORTH] + trucks[EAST] + trucks[SOUTH] + trucks[WEST];
		int sum_buses = buses[NORTH] + buses[EAST] + buses[SOUTH] + buses[WEST];
		int sum_motorcycles = motorcycles[NORTH] + motorcycles[EAST] + motorcycles[SOUTH] + motorcycles[WEST];
		if (sum_cars != 0) {
			of << " total cars: " << sum_cars << std::endl;
			of << "  NORTH: " << cars[NORTH] << std::endl;
			of << "  EAST : " << cars[EAST] << std::endl;
			of << "  WEST : " << cars[WEST] << std::endl;
			of << "  SOUTH: " << cars[SOUTH] << std::endl;
		}
		if (sum_trucks != 0) {
			of << " total trucks: " << sum_trucks << std::endl;
			of << "  NORTH: " << trucks[NORTH] << std::endl;
			of << "  EAST : " << trucks[EAST] << std::endl;
			of << "  WEST : " << trucks[WEST] << std::endl;
			of << "  SOUTH: " << trucks[SOUTH] << std::endl;
		}
		if (sum_buses != 0) {
			of << " total buses: " << sum_buses << std::endl;
			of << "  NORTH: " << buses[NORTH] << std::endl;
			of << "  EAST : " << buses[EAST] << std::endl;
			of << "  WEST : " << buses[WEST] << std::endl;
			of << "  SOUTH: " << buses[SOUTH] << std::endl;
		}
		if (sum_motorcycles != 0) {
			of << " total motorcycles: " << sum_motorcycles << std::endl;
			of << "  NORTH: " << motorcycles[NORTH] << std::endl;
			of << "  EAST : " << motorcycles[EAST] << std::endl;
			of << "  WEST : " << motorcycles[WEST] << std::endl;
			of << "  SOUTH: " << motorcycles[SOUTH] << std::endl;
		}
		of << "<misc data>" << std::endl;
		of << " total weight: " << total_weight << std::endl;
		of << " total passengers: " << total_passengers << std::endl;
		of << " (buses)" << std::endl;
		for (std::string bus : BUS_NAMES) {
			if (bus_names[bus] != 0) {
				of << " number of " << bus << ": " << bus_names[bus] << std::endl;
			}
		}
		of << " (motorcycles)" << std::endl;
		for (std::string brand : MOTORCYCLE_BRANDS) {
			if (motorcycle_brands[brand] != 0) {
				of << " number of " << brand << ": " << motorcycle_brands[brand] << std::endl;
			}
		}
		of << std::endl << std::endl;
		of.close();
		std::cout << "Data written to " << filename << std::endl;
	}
	else {
		std::cerr << "Unable to open file " << filename << std::endl;
	}
}