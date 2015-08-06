#include <iostream>
#include <fstream>
#include <random>
#include <list>
#include <vector>
#include "generate_config.h"
using namespace std;



int main() {
	
	// Declare random number engine that will be used to generate independent, uniformly random values that will be fed into the appropriate distributions
	// Seed it with a non-deterministic random value generated by random_device
	default_random_engine engine(random_device{}());

	// Prompt user to input information

	// Get number of simulation iterations from user input
	int numIterations = getNumIterations();

	// Get grid size from user input
	int gridSize = getGridSize();

	// Get number of hours to simulate from user input
	int numHours = getNumHours();

	// Get average demand from user input
	int avgDemand = getAvgDemand();
	
	// Get pricing policy from user input
	int pricePolicy = getPricePolicy();

	// Get number of parking lots from user input except for Pricing Policy 7, for which the number of lots is set to two
	int numLots = 2;
	if (pricePolicy != 7) {
		numLots = getNumLots();
	}

	// Get whether lot capacities should be random or equal from user input
	bool randCapacIn = randCapac();
	
	// If user indicates that capacities should be equal, get capcacity from user input
	int capac = 0;
	if (!randCapacIn) {
		capac = getLotCapac();
	}

	// Get utilization rate from user input - avg fraction of all spots on the grid that are being utilized (reserved/occupied)
	double utilRate = getUtilRate();
	
	// Get max occupation rate from user input
	double occupationRate = getOccupationRate();
	
	// If price policies 2 & 7 are not chosen, get initial lot price from user input. 
	double price = 0.5;
	if ((pricePolicy != 2) && (pricePolicy != 7)) {
		price = getLotPrice();
	}
	
	// Get number of destinations from user input except for Pricing Policy 7, for which the number of destinations is set to one
	int numDests = 1;
	if (pricePolicy != 7) {
		numDests = getNumDests();
	}

	// If pricing policy 7 is not chosen, get whether destination probabilities (prob. that each destination is chosen) should be random or equal from user input
	bool randDestProbsIn = 0;
	if (pricePolicy != 7) {
		bool randDestProbsIn = randDestProbs();
	}

	// Declare output stream "config" that will write to a file called "config.txt"
	// Note: If "config.txt" does not already exist in the present working directory, it will be created automatically. Otherwise, it will be written over.
	ofstream config;
	config.open("config.txt");

	// Write number of iterations to config.txt
	writeIterations(numIterations, config);

	// Write grid size to config.txt
	writeGridSize(gridSize, config);

	// Write number of destinations to config.txt
	writeDestCount(numDests, config);

	// Write random destination locations to config.txt
	writeDestLocs(gridSize, numDests, config, engine);

	// Write destination probabilities (probability that a driver will choose that destination) to config.txt and return the probabilities in a list
	list<double> destProbs = writeDestProbs(randDestProbsIn, numDests, config, engine);
	
	// Write random destination average durations to config.txt
	vector<double> avgDurations = writeDestAvgDurs(numDests, config, engine);

	// Write number of lots to config.txt
	writeLotCount(numLots, config);
	
	// Write random parking lot locations to config.txt
	writeLotLocs(gridSize, numLots, config, engine);

	// Write random parking lot capacities to config.txt
	int totalCapacity = writeLotCapacities(randCapacIn, capac, avgDemand, numLots, config, engine);
	
	writeLotTypes(numLots, config, engine);

	// Write the pricing policy to config.txt
	writePricePolicy(pricePolicy, config);

	// Write random parking lot prices to config.txt
	writeLotPrices(pricePolicy, price, numLots, config, engine);

	// Write lot occupation rate to config.txt
	writeOccupationRate(occupationRate, config);
	
	// Write average demand to config.txt
	writeAvgDemand(avgDemand, config);

	// Get driver arrival times and write number of drivers to config.txt 
	list<list<double>> arrivals = generateArrivals(numIterations, numHours, avgDemand, config, engine);

	// Write number of drivers to config.txt
	list<int> numDrivers = writeNumDrivers(arrivals, config); 

	// Write driver arrival times to config.txt
	writeDriverArrivals(arrivals, config);

	// Write random driver arrival locations to config.txt
	writeDriverLocs(gridSize, numDrivers, config, engine);

	// Write random driver destinations to config.txt
	list<list<int>> dests = writeDriverDests(destProbs, numDrivers, config, engine);

	// Write random driver durations to config.txt
	writeDriverDurs(avgDemand, utilRate, totalCapacity, numDrivers, config, engine);

	// Write random driver max walking distances to config.txt
	writeDriverMaxWalkDists(gridSize, numDrivers, config, engine);

	// Write random driver max prices to config.txt
	writeDriverMaxPrices(numDrivers, config, engine);

	// Write random driver importance weight to config.txt
	writeDriverImportWeights(numDrivers, config, engine);

	// Close output file stream
	config.close();

	return 0;
}


