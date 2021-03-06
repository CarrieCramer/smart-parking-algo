#include <iostream>
#include <limits>
#include <string>
#include <list>
#include "generate_config.h"
using namespace std;


// Obtain the number of simulation iterations. In each iteration, the grid, lot, and destination attributes will remain the same, but there will be a different set of drivers. 
int getNumIterations() {

	// Prompt user to enter the number of iterations
	cout << "Enter the number of iterations. In each iteration, the grid, lot, and destination attributes will remain the same, but there will be a different set of drivers: ";

	// Read in the number of iterations
	int numIterations = 1;
	cin >> numIterations;

	return numIterations;
}

// Obtain grid size from user input
int getGridSize() {

	// Prompt user to enter the grid size (length of one side of the square grid)
	cout << "\nEnter grid size (length of one side of the square grid): ";

	// Read in grid size
	int gridSize = 0;
	cin >> gridSize;

	return gridSize;
}

// Obtain number of hours to simulate from user input
int getNumHours() {

	// Prompt user to enter the number of hours
	cout << "\nEnter number of hours to simulate: ";

	// Read in the number of hours
	int numHours = 0;
	cin >> numHours;

	return numHours;
}

// Obtain average demand from user input
int getAvgDemand() {

	// Prompt user to enter the average demand (average number of drivers per hour)
	cout <<"\nEnter average demand (number of drivers that arrive per hour): ";

	// Read in the average demand
	int avgDemand = 0;
	cin >> avgDemand;

	return avgDemand;
}

// Obtain number of parking lots from user input
int getNumLots() {

	// Prompt user to enter the number of parking lots 
	cout << "\nEnter number of parking lots: ";

	// Read in the number of parking lots
	int numLots = 0;
	cin >> numLots;

	return numLots;
}

// Obtain whether lot capacities are equal or random from user input
bool randCapac() {

	// Prompt user to enter 0 for equal lot capacities or 1 for random
	cout << "\nEnter 0 for equal lot capacities or 1 for random: ";

	// Read in user response
	bool randCapacIn = 0;
	cin >> randCapacIn;

	return randCapacIn;
}

// Obtain lot capacity if user chooses to use equal lot capacities
int getLotCapac() {

	// Prompt user to enter lot capacity
	cout << "\nEnter lot capacity: ";

	// Read in lot capacity
	int capac = 0;
	cin >> capac;

	return capac;
}

// Obtain utilization rate 
double getUtilRate() {

	// Prompt user to enter utilization rate
	cout << "\nEnter avg utilization rate (fraction of all parking spots that are being utilized by drivers): ";

	// Read in utilization rate
	double utilRate = 0;
	cin >> utilRate;

	return utilRate;
}

// Obtain lot pricing policy number
int getPricePolicy() {

	// Prompt user to enter lot pricing policy number
	cout << "\nPricing Policies:\n";
	cout << "1 | Equal Static Pricing: all lots have the same price, which remains the same throughout the simulation\n";
	cout << "2 | Random Static Pricing: lots have randomized prices, which remain the same throughout the simulation\n";
	cout << "3 | Proportional Dynamic Pricing\n";
	cout << "4 | LA Express Park Dynamic Pricing\n";
	cout << "5 | Proportional-Derivative Dynamic Pricing\n";
	cout << "6 | Uber Dynamic Pricing\n";
	cout << "7 | Competitive Dynamic Pricing Game";
	cout << "Enter one of the numbers above to select a lot pricing policy: ";

	// Read in lot policy number
	int pricePolicy = 0;
	cin >> pricePolicy;

	return pricePolicy;
}

double getOccupationRate() {
	// Prompt user to enter occupation rate
	
	cout << "Enter the occupation rate for non-reserving drivers.\n";
	double rate = 0;
	cin >> rate;
	
	return rate;
}

// Obtain lot prices
double getLotPrice() {

	// Prompt user to enter lot price
	cout << "\nEnter lot price (real number in the range [0,1]). For dynamic pricing policies, this will be the initial price for all lots: ";

	// Read in lot price
	double price = 0.0;
	cin >> price;

	return price;
}

// Obtain number of destinations from user input
int getNumDests() {

	// Prompt user to enter the number of destinations
	cout << "\nEnter number of destinations: ";

	// Read in the number of destinations
	int numDests = 0;
	cin >> numDests;

	return numDests;
}

// Obtain whether destination probabilities are equal or random from user input
bool randDestProbs() {

	// Prompt user to enter 0 for equal destination probabilities, or 1 for random destination probabilities
	cout << "\nEnter 0 for equal destination probabilities or 1 for random destination probabilities: ";

	// Read in 0 or 1
	bool destProbs = 0;
	cin >> destProbs;

	return destProbs;
}

const std::string asterisks = "****************************************************************************************************\n";

// Write iteration count to config
void writeIterations(int numIterations, ofstream& config) {
	config << asterisks;
	config << "NUMBER OF ITERATIONS:\n";
	config << "During each iteration, a new set of drivers with random attributes will be generated.\n";
	config << "The grid, lot, and destination attributes will remain the same throughout all iterations.\n";
	config << asterisks;
	config << numIterations << "\n\n";
}

// Write grid size to config
void writeGridSize(double gridSize, ofstream& config) {
	config << asterisks;
	config << "GRID SIZE:\n";
	config << "The grid represents a 2-D, square, Cartesian space, with its lower left corner at (0, 0).\n";
	config << "The grid size is a positive integer value representing the maximum x and y-coordinates.\n";
	config << asterisks;
	config << gridSize << "\n\n";
}

// Write destination count to config
void writeDestCount(int numDests, ofstream& config) {
	config << asterisks;
	config << "DESTINATION COUNT:\n";
	config << "Total number of destinations on the grid.\n";
	config << asterisks;
	config << numDests << "\n\n";
}

// Write random destination locations to output stream
void writeDestLocs(int gridSize, int numDests, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DESTINATION LOCATIONS:\n";
	config << "Coordinates of each destination in the format: (x1,y1) (x2,y2) (x3,y3) ...\n";
	config << "The coordinates are real numbers that do not exceed the grid size.\n";
	config << asterisks;

	// Define a continuous Uniform(0,gridSize) distribution
	uniform_real_distribution<double> distribution(0, gridSize);

	//Write locations to config in the format: (x1,y1) (x2,y2) ...
	for (int i = 0; i < numDests; i++) {

		config << "(" << distribution(engine) << "," << distribution(engine) << ") ";
	}

	config << "\n\n";
}

// Write destination probabilities (probability that a driver will choose that destination) to config and return the probabilities in a list
list<double> writeDestProbs(bool randDestProbsIn, int numDests, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DESTINATION PROBABILITIES:\n";
	config << "Probability that each destination will be chosen by a particular driver.\n";
	config << "These values must add to 1.\n";
	config << asterisks;

	// Define list that will hold all destination probabilities
	list<double> destProbs;

	// If user requests random destination probabilities
	if (randDestProbsIn) {

		// Define a continuous Uniform(0,1) distribution
		uniform_real_distribution<double> distribution(0, 1);

		// Keep track of max and min values for normalization
		double min = 1.0;
		double max = 0.0;

		// For each destination, generate a random value from 0 to 1 using the distribution
		for (int i = 0; i < numDests; i++) {
			double prob = distribution(engine);
			destProbs.push_back(prob);
		}

		// Normalize the probabilities by dividing each value by the sum of all values
		double sum = 0;
		for (list<double>::iterator it = destProbs.begin(); it != destProbs.end(); it++) {
			sum += *it; // Running sum
		}
		for (list<double>::iterator it = destProbs.begin(); it != destProbs.end(); it++) {
			*it /= sum; // Divide current value by sum
		}
	}
	else {
		// Generate equal destination probabilities
		double prob = 1.0 / numDests;

		for (int i = 0; i < numDests; i++) {
			destProbs.push_back(prob);
		}
	}

	// Write the destination probabilities to config
	for (list<double>::iterator it = destProbs.begin(); it != destProbs.end(); it++) {
		config << *it << " ";
	}

	config << "\n\n";

	return destProbs;
}

// Write random destination average durations to config
vector<double> writeDestAvgDurs(int numDests, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DESTINATION AVERAGE DURATIONS:\n";
	config << "Average amount of time that drivers spend at each destination.\n";
	config << "Note that the simulation time is normalized from 0 to 1.\n";
	config << asterisks;

	// Define a continuous Uniform(0,1) distribution
	uniform_real_distribution<double> distribution(0, 1);

	// Write the durations to config and save in avgDurations vector (to be used when calculating drivers' durations)
	double avgDur;
	vector<double> avgDurations;
	for (int i = 0; i < numDests; i++) {
		avgDur = distribution(engine);
		avgDurations.push_back(avgDur);
		config << avgDur << " ";
	}

	config << "\n\n";

	return avgDurations;
}

void writeLotCount(int numLots, ofstream& config) {
	config << asterisks;
	config << "LOT COUNT:\n";
	config << "Total number of parking lots on the grid.\n";
	config << asterisks;
	config << numLots << "\n\n";
}

//Write random lot locations to config
void writeLotLocs(int gridSize, int numLots, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "LOT LOCATIONS:\n";
	config << "Coordinates of each lot in the format: (x1,y1) (x2,y2) (x3,y3) ...\n";
	config << "The coordinates are real numbers that do not exceed the grid size.\n";
	config << asterisks;


	// Define a continuous Uniform(0,gridSize) distribution
	uniform_real_distribution<double> distribution(0, gridSize);

	// Write locations to config in the format: (x1,y1) (x2,y2) ...
	for (int i = 0; i < numLots; i++) {

		config << "(" << distribution(engine) << "," << distribution(engine) << ") ";
	}

	config << "\n\n";
}

// Write random parking lot capacities to config
int writeLotCapacities(bool randCapacIn, int capac, int avgDemand, int numLots, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "LOT CAPACITIES:\n";
	config << "Number of parking spots in each parking lot.\n";
	config << asterisks;
	
	int totalCapacity = 0;
	int currentCapacity;

	if (randCapacIn) {
		// Define a discrete Uniform(1,avgDemand) distribution
		uniform_int_distribution<int> distribution(1, avgDemand);

		// Write random capacities to config
		for (int i = 0; i < numLots; i++) {
			currentCapacity = distribution(engine);
			config << currentCapacity << " ";
			totalCapacity += currentCapacity;
		}
	}
	else {
		// Write equal capacities to config
		for (int i = 0; i < numLots; i++) {
	
			config << capac << " ";
		}
		totalCapacity = capac*numLots;
	}

	config << "\n\n";
	return totalCapacity;
}

// Write the lot types to config
void writeLotTypes(int numLots, int pricePolicy, ofstream& config, default_random_engine& engine) {
	const int numOfLotTypes = 3;
	config << asterisks;
	config << "LOT TYPES:\n";
	config << "Types of parking at the parking lot.\n";
	config << asterisks;
	
	char lotType;
	int distResult;
	uniform_int_distribution<int> distribution(1, numOfLotTypes);

	for (int i = 0; i < numLots; i++) {
		if (pricePolicy == 7) {
			lotType = 'r';
		}
		else {
			distResult = distribution(engine);
			switch (distResult) {
			case 1:
				lotType = 'r';
				break;
			case 2:
				lotType = 'e';
				break;
			default:
				lotType = 'n';
			}
		}
		config << lotType << " ";
		}

	config << "\n\n";
}

// Write the pricing policy to config
void writePricePolicy(int pricePolicy, ofstream& config) {

	config << asterisks;
	config << "LOT PRICING POLICY:\n";
	config << "Options:\n";
	config << "1 | Equal Static Pricing: all lots have the same price, which remains the same throughout the simulation\n";
	config << "2 | Random Static Pricing: lots have randomized prices, which remain the same throughout the simulation\n";
	config << "3 | Proportional Dynamic Pricing\n";
	config << "4 | LA Express Park Dynamic Pricing\n";
	config << "5 | Proportional-Derivative Dynamic Pricing\n";
	config << "6 | Uber Dynamic Pricing\n";
	config << "7 | Competitive Dynamic Pricing Game\n";
	config << asterisks;
	config << pricePolicy <<"\n\n";
}

// Write random parking lot prices to config
void writeLotPrices(int pricePolicy, double price, int numLots, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "LOT PRICES:\n";
	config << "Parking price per hour for each lot.\n";
	config << "Note that parking prices are normalized from 0 to 1.\n";
	config << asterisks;

	if (pricePolicy == 2) {
		
		// Define a continuous Uniform(0,1) distribution 
		uniform_real_distribution<double> distribution(0, 1);

		// Write random prices to config
		for (int i = 0; i < numLots; i++) {

			config << distribution(engine) << " ";
		}
	}
	else {

		//Write equal prices to config
		for (int i = 0; i < numLots; i++) {

			config << price << " ";
		}
	}

	config << "\n\n";
}

void writeOccupationRate(double rate, ofstream& config) {
	config << asterisks;
	config << "MAX OCCUPATION RATE:\n";
	config << "The ratio of non-reserved parking spaces to all parking spaces needed for\n";
	config << "a person to consider reserving a parking space at a lot of type 'e'.\n";
	config << asterisks;
	
	config << rate << "\n\n";
}

// Write average demand
void writeAvgDemand(int avgDemand, ofstream& config) {
	config << asterisks;
	config << "AVERAGE DEMAND:\n";
	config << "Average number of drivers that arrive per hour.\n";
	config << asterisks;
	config << avgDemand << "\n\n";
}

// Get driver arrival times and return them in a matrix
list<list<double> > generateArrivals(int numIterations, int numHours, int avgDemand, ofstream& config, default_random_engine& engine) {

	//Define exponential distribution with arrival rate parameter 
	exponential_distribution<double> distribution(avgDemand);

	// t will store current arrival time
	double t;

	// Matrix that will store arrival times
	// 1st dimension corresponds to simulation iteration number
	// 2nd dimension corresponds to driver ID

	list< list<double> > arrivals;

	// List of arrival times for current iteration
	list<double> currentArrivals;

	// For each simulation iteration
	for (int i = 0; i < numIterations; i++) {
		
		// Clear currentArrivals
		currentArrivals.clear();

		t = 0;

		// For each hour
		for (int currentHour = 1; currentHour <= numHours; currentHour++) {

			// Loop until a generated arrival time exceeds the end of the current hour
			while (t <= currentHour) {

				// Generate next arrival interval and add it to t
				t += distribution(engine);

				// Add arrival time to currentArrivals
				if (t <= currentHour) {
					currentArrivals.push_back(t);
				}
			}
		}

		// Add a copy of currentArrivals to arrivals
		arrivals.push_back(currentArrivals);
	}

	return arrivals;
}

// Write number of drivers in each simulation iteration to config and return them in a list
list<int> writeNumDrivers(list<list<double>> arrivals, ofstream& config) {

	config << asterisks;
	config << "DRIVER COUNT:\n";
	config << "Number of drivers that arrives during each simulation iteration.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Stores the number of drivers in each simulation iteration
	list<int> numDrivers;

	// Counter storing number of drivers in current simulation iteration
	int currentNumDrivers;

	// Iterate through 1st dimension of arrivals
	for (list<list<double>>::iterator arrivalsIt = arrivals.begin(); arrivalsIt != arrivals.end(); arrivalsIt++) {

		currentNumDrivers = (*arrivalsIt).size();

		// Write number of drivers to config
		config << currentNumDrivers << "\n";

		// Store number of drivers in numDrivers
		numDrivers.push_back(currentNumDrivers);
	}

	config << "\n";

	return numDrivers;
}

// Write driver arrival times to config
void writeDriverArrivals(list<list<double>> arrivals, ofstream& config) {

	config << asterisks;
	config << "DRIVER ARRIVAL TIMES:\n";
	config << "Arrival times of each driver in ascending order.\n";
	config << "Note that the simulation time is normalized from 0 to 1.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Iterate through 1st dimension of arrivals
	for (list<list<double>>::iterator arrivalsIt = arrivals.begin(); arrivalsIt != arrivals.end(); arrivalsIt++) {
		
		// Iterate through 2nd dimension of arrivals
		for (list<double>::iterator arrivalsIt2 = (*arrivalsIt).begin(); arrivalsIt2 != (*arrivalsIt).end(); arrivalsIt2++) {

			// Write current arrival time to config
			config << *arrivalsIt2 << " ";
		}
			
		config << "\n";
	}

	config << "\n";
}

// Write random driver arrival locations to config
void writeDriverLocs(int gridSize, list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER ARRIVAL LOCATIONS:\n";
	config << "Coordinates of the location of each driver at its arrival time in the format: (x1,y1) (x2,y2) (x3,y3) ...\n";
	config << "The coordinates are real numbers that do not exceed the grid size.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Define a continuous Uniform(0,gridSize) distribution
	uniform_real_distribution<double> distribution(0, gridSize);
	
	int currentNumDrivers = 0;

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {
		
		// Get the number of drivers in the current simulation iteration
		currentNumDrivers = *numDriversIt;

		// Write locations to config in the format: (x1,y1) (x2,y2) ...
		for (int i = 0; i < currentNumDrivers; i++) {

			config << "(" << distribution(engine) << "," << distribution(engine) << ") ";
		}
		// Go to the next line in config
		config << "\n";
	}

	config << "\n";
}

// Write random driver destinations to config and return list of destinations
list<list<int>> writeDriverDests(list<double> destProbs, list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER DESTINATIONS:\n";
	config << "ID number of each driver's destination.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Define a discrete distribution over the destination IDs based on the destination probabilities
	list<double>::iterator it = destProbs.begin();
	discrete_distribution<int> distribution(destProbs.size(), 0, 1,
		[&destProbs, &it](double){
		auto w = *it;
		it++;
		return w;
	}
	);

	// This list will contain a list of driver destinations for each simulation iteration
	list<list<int>> dests;

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {
		
		int dest;
		
		// This list will store the driver destinations for the current simulation iteration
		list<int> currentDests;

		// For each driver in the current simulation iteration
		for (int i = 0; i < *numDriversIt; i++) {
			
			// Generate a random destination
			dest = distribution(engine);

			// Add it to config
			config << dest << " ";

			// Save it in currentDests list
			currentDests.push_back(dest);
		}
		// Go to the next line in config
		config << "\n";

		// Add the currentDests list to the dests list
		dests.push_back(currentDests);
	}

	config << "\n";

	return dests;
}

// Write random driver durations to config
void writeDriverDurs(int avgDemand, double utilRate, int totalCapacity, list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER DURATIONS:\n";
	config << "The amount of time that each driver will remain at its parking spot after arriving at the lot.\n";
	config << "Note that the simulation time is normalized from 0 to 1.\n";
	config << "A duration greater than 1 means that the driver will stay beyond the end of the simulation iteration.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;
	
	exponential_distribution<double> distribution(avgDemand/(utilRate*totalCapacity)); 

	int currentNumDrivers = 0;

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {

		// Get the number of drivers in the current simulation iteration
		currentNumDrivers = *numDriversIt;

		// Write durations to config
		for (int i = 0; i < currentNumDrivers; i++) {

			config << distribution(engine) << " ";
		}
		// Go to the next line in config
		config << "\n";
	}

	config << "\n";
}

// Write random driver max walking distances to config
void writeDriverMaxWalkDists(int gridSize, list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER MAX WALKING DISTANCES:\n";
	config << "The maximum distance that each driver is willing to walk from its assigned lot to its destination.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Define a continuous Uniform(0,gridSize) distribution 
	uniform_real_distribution<double> distribution(0, gridSize);

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {

		// Write max walking distances for current simulation iteration to config
		for (int i = 0; i < *numDriversIt; i++) {

			config << distribution(engine) << " ";
		}
		config << "\n";
	}
	config << "\n";
}

// Write random driver max prices to config
void writeDriverMaxPrices(list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER MAX PRICES:\n";
	config << "The maximum parking rate (price per unit time) that each driver is willing to pay.\n";
	config << "Note that parking rates are normalized from 0 to 1.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Define a continuous Uniform(0,1) distribution 
	uniform_real_distribution<double> distribution(0, 1);

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {

		// Write prices for current simulation iteration to config
		for (int i = 0; i < *numDriversIt; i++) {

			config << distribution(engine) << " ";
		}
		config << "\n";
	}
	config << "\n";
}

// Write random driver importance weight to config
void writeDriverImportWeights(list<int> numDrivers, ofstream& config, default_random_engine& engine) {

	config << asterisks;
	config << "DRIVER IMPORTANCE WEIGHTS:\n";
	config << "A value for each driver representing the relative importance of parking price vs. walking distance.\n";
	config << "These weights are real and normalized from 0 to 1.\n";
	config << "Each row corresponds to one simulation iteration.\n";
	config << asterisks;

	// Define a continuous Uniform(0,1) distribution 
	uniform_real_distribution<double> distribution(0, 1);

	// Iterate through each value in numDrivers list 
	for (list<int>::iterator numDriversIt = numDrivers.begin(); numDriversIt != numDrivers.end(); numDriversIt++) {
		
		// Write importance weights for current simulation iteration to config
		for (int i = 0; i < *numDriversIt; i++) {

			config << distribution(engine) << " ";
		}
		config << "\n";
	}
	config << "\n";
}