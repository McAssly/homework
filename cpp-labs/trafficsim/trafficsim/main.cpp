#include "intersection.hpp"
#include "road.hpp"
#include "global.hpp"
#include "util.hpp"
#include "data.hpp"

void printSimulation(Place places[GRID_SIZE][GRID_SIZE], TrafficLight vertical, TrafficLight horizontal, Road roads[4]);

int main() {
	int simulations = 0;
	std::string input;
	while (true) {
		static Place places[GRID_SIZE][GRID_SIZE]; // initialize array of places
		for (int y = 0; y < GRID_SIZE; y++) {
			for (int x = 0; x < GRID_SIZE; x++) {
				places[y][x].SetPosition(x, y);
			}
		}

		// Store each of the four roads going in each cardinal direction
		static Road roads[4];
		// build all 4 roads
		roads[NORTH] = Road::BuildRoad(places, NORTH);
		roads[EAST] = Road::BuildRoad(places, EAST);
		roads[SOUTH] = Road::BuildRoad(places, SOUTH);
		roads[WEST] = Road::BuildRoad(places, WEST);
		// get all simulation settings (at any point the user enters 0, exit the program)
		promptUser("simulation cycles: (0 to exit)", &input);	// prompt user for simulation setting
		if (input == "0") break;								// if exit value is given, exit program
		unsigned int cycle_limit = safe_stoul(input);			// set the setting
		if (cycle_limit == 0) continue;							// restart loop and redo settings

		promptUser("vehicle spawn rate: ", &input);
		if (input == "0") break;
		VehicleSpawnRate = safe_stoul(input);
		if (VehicleSpawnRate == 0) continue;

		promptUser("vertical light timing: ", &input);
		if (input == "0") break;
		VerticalGreenDuration = safe_stoi(input);
		if (VerticalGreenDuration == 0) continue;

		promptUser("horizontal light timing: ", &input);
		if (input == "0") break;
		HorizontalGreenDuration = safe_stoi(input);
		if (HorizontalGreenDuration == 0) continue;

		// initalize the traffic lights for both sections
		TrafficLight vertical_traffic_light = TrafficLight(
			TRAFFIC_LIGHT_GREEN, VerticalGreenDuration, HorizontalGreenDuration,
			&places[GRID_SIZE / 2 - 1][GRID_SIZE / 2 - 2], &places[GRID_SIZE / 2 + 3][GRID_SIZE / 2]
		);
		TrafficLight horizontal_traffic_light = TrafficLight(
			TRAFFIC_LIGHT_RED, HorizontalGreenDuration, VerticalGreenDuration,
			&places[GRID_SIZE / 2][GRID_SIZE / 2 + 1], &places[GRID_SIZE / 2 + 2][GRID_SIZE / 2 - 3]
		);

		// initalize our data collector
		TrafficData data = TrafficData(simulations, VehicleSpawnRate, VerticalGreenDuration, HorizontalGreenDuration);

		// initialize each cycle for the simulation
		unsigned int cycle = 0;
		// run the simulation
		while (cycle < cycle_limit) {
			clearConsole();
			std::cout << "Cycle: " << cycle << std::endl;
			printSimulation(places, vertical_traffic_light, horizontal_traffic_light, roads);

			// loop through every vehicle
			for (int i = 0; i < 4; i++) {
				Road* road = &roads[i];
				for (Vehicle* vehicle : road->vehicles.Get()) {
					vehicle->Move();
					vehicle->Build(places);
				}
				if (chance(VehicleSpawnRate) && road->IsOpen()) {
					std::cout << "vehicle spawned :: " << road->direction << std::endl;
					road->SpawnVehicle(&data);
				}
				road->vehicles.Exit();
			}

			// 5. update traffic lights
			vertical_traffic_light.Update();
			horizontal_traffic_light.Update();

			wait(LOOP_DELAY);
			data.cycles++;
			cycle++;
		}
		data.Write("data.txt");
		simulations++;
	}

	std::cout << "Simulation finished." << std::endl;

	return 0;
}

/// @brief	Prints out the simulation space
void printSimulation(Place places[GRID_SIZE][GRID_SIZE], TrafficLight vertical, TrafficLight horizontal, Road roads[4]) {
	std::cout << " V: " << vertical << "   H: " << horizontal << std::endl;
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			if (!places[y][x].IsFree() && !places[y][x].IsEmpty() && places[y][x].Occupee() != nullptr) {
				Vehicle* v = places[y][x].Occupee();
				places[y][x].Occupee()->Print();
			}
			else {
				std::cout << places[y][x] << ' ';
			}
		}
		std::cout << std::endl;
	}
}