#include "road.hpp"

bool Road::IsOpen() {
	return this->places.front()->IsFree();
}

void Road::SpawnVehicle(TrafficData* data) {
	if (chance(TRUCK_SPAWN_RATE)) {
		Truck* truck = new Truck(this->places.front(), this->direction);
		data->trucks[direction]++;
		data->total_weight += truck->weight + truck->GetCargoWeight();
		this->vehicles.Enter(truck);
	}
	else if (chance(BUS_SPAWN_RATE)) {
		Bus* bus = new Bus(this->places.front(), this->direction);
		data->buses[direction]++;
		data->total_weight += bus->weight;
		data->total_passengers += bus->GetPassengers();
		data->bus_names[bus->GetName()]++;
		this->vehicles.Enter(bus);
	}
	else if (chance(MOTORCYCLE_SPAWN_RATE)) {
		Motorcycle* motorcycle = new Motorcycle(this->places.front(), this->direction);
		data->motorcycles[direction]++;
		data->total_weight += motorcycle->weight;
		data->motorcycle_brands[motorcycle->GetBrand()]++;
		this->vehicles.Enter(motorcycle);
	}
	else {
		Car* car = new Car(this->places.front(), this->direction);
		data->cars[direction]++;
		data->total_weight += car->weight;
		this->vehicles.Enter(car);
	}
}

/// @brief	Builds a 2-lane road starting from the given position
Road Road::BuildRoad(Place places[GRID_SIZE][GRID_SIZE], Direction dir) {
	Road road;
	road.direction = dir;
	switch (dir) { // build in the given direction
	case NORTH: {
		// the starting positions:
		int start_y = GRID_SIZE - 1;
		int x = GRID_SIZE / 2;
		// build in the (-y) direction
		for (int y = start_y; y >= 0; y--) {
			// get the place in the current position
			Place* place = &places[y][x];
			// if not final get the next place
			if (y != 0) {
				Place* next = &places[y - 1][x];
				place->Link(dir, next); // link the current place to it
			}
			else { // if it is final, mark it as final
				place->SetFinal();
			}
			// add the place to the road
			place->UnOccupy();
			road.places.push_back(place);
		}
		break;
	}
	case EAST: {
		int y = GRID_SIZE / 2 + 2;
		int start_x = 0;
		// build in the (+x) direction
		for (int x = start_x; x < GRID_SIZE; x++) {
			// same idea as in north
			Place* place = &places[y][x];
			if (x != GRID_SIZE - 1) place->Link(dir, &places[y][x + 1]);
			else place->SetFinal();
			place->UnOccupy();
			road.places.push_back(place);
		}
		break;
	}
	case SOUTH: {
		int start_y = 0;
		int x = GRID_SIZE / 2 - 2;
		// build in the (+y) direction
		for (int y = start_y; y < GRID_SIZE; y++) {
			Place* place = &places[y][x];
			if (y != GRID_SIZE - 1) place->Link(dir, &places[y + 1][x]);
			else place->SetFinal();
			place->UnOccupy();
			road.places.push_back(place);
		}
		break;
	}
	case WEST: {
		int y = GRID_SIZE / 2;
		int start_x = GRID_SIZE - 1;
		// build in the (-x) direction
		for (int x = start_x; x >= 0; x--) {
			Place* place = &places[y][x];
			if (x != 0) place->Link(dir, &places[y][x - 1]);
			else place->SetFinal();
			place->UnOccupy();
			road.places.push_back(place);
		}
		break;
	}
	}
	return road;
}

std::list<Vehicle*> VehicleQueue::Get() {
	return vehicles;
}

void VehicleQueue::Enter(Vehicle* vehicle) {
	this->vehicles.push_back(vehicle);
}

void VehicleQueue::Exit() {
	// each vehicle is allocated memory and must be deleted, when exitting
	if (!vehicles.empty()) {
		Vehicle* vehicle = this->vehicles.front();
		if (vehicle->IsFinal()) {
			this->vehicles.pop_front();
			delete vehicle;
		}
	}
}