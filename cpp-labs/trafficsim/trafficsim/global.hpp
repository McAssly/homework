#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <list>
#include <fstream>
#include <map>

#ifndef GLOBAL
#define GLOBAL

static int VerticalGreenDuration = 0;
static int HorizontalGreenDuration = 0;
static unsigned int VehicleSpawnRate = 0; // inverse, less means more
static const int GRID_SIZE = 24;
static const int LOOP_DELAY = 100; // ms

#endif