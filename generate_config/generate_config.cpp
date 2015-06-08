#include <iostream>
#include <limits>
#include "generate_config.h"

// Obtain grid size from user input
int getGridSize() {

	// Prompt user to enter the grid size (length of one side of the square grid)
	cout << "Enter grid size: ";

	// Read in grid size
	int gridSize = 0;
	cin >> gridSize;

	return gridSize;
}

// Obtain average demand from user input
int getAvgDemand() {

	// Prompt user to enter the average demand (average number of drivers per simulation)
	cout << endl << "Enter average demand: ";

	// Read in the average demand
	int avgDemand = 0;
	cin >> avgDemand;

	return avgDemand;
}

// Obtain number of parking lots from user input
int getNumLots() {

	// Prompt user to enter the number of parking lots 
	cout << endl << "Enter number of parking lots: ";

	// Read in the number of parking lots
	int numLots = 0;
	cin >> numLots;

	return numLots;
}

// Obtain whether lot capacities are equal or random from user input
bool randCapac() {

	// Prompt user to enter 0 for equal lot capacities or 1 for random
	cout << endl << "Enter 0 for equal lot capacities or 1 for random: ";

	// Read in user response
	bool randCapacIn = 0;
	cin >> randCapacIn;

	return randCapacIn;
}

// Obtain lot capacity if user chooses to use equal lot capacities
int getLotCapac() {

	// Prompt user to enter lot capacity
	cout << endl << "Enter lot capacity: ";

	// Read in lot capacity
	int capac = 0;
	cin >> capac;

	return capac;
}

// Obtain whether lot prices are equal or random from user input
bool randPrice() {

	// Prompt user to enter 0 for equal lot prices or 1 for random
	cout << endl << "Enter 0 for equal lot prices or 1 for random: ";

	// Read in user response
	bool randPriceIn = 0;
	cin >> randPriceIn;

	return randPriceIn;
}

// Obtain lot price if user chooses to use equal lot prices
double getLotPrice() {

	// Prompt user to enter lot price
	cout << endl << "Enter lot price (real number normalized from 0 to 1): ";

	// Read in lot price
	double price = 0.0;
	cin >> price;

	return price;
}

// Obtain number of destinations from user input
int getNumDests() {

	// Prompt user to enter the number of destinations
	cout << endl << "Enter number of destinations: ";

	// Read in the number of destinations
	int numDests = 0;
	cin >> numDests;

	return numDests;
}

// Obtain whether destination probabilities are equal or random from user input
bool randDestProbs() {

	// Prompt user to enter 0 for equal destination probabilities, or 1 for random destination probabilities
	cout << endl << "Enter 0 for equal destination probabilities or 1 for random destination probabilities: ";

	// Read in 0 or 1
	bool destProbs = 0;
	cin >> destProbs;

	return destProbs;
}

// Write random destination locations to output stream
void writeDestLocs(int gridSize, int numDests, ofstream& config, default_random_engine& engine) {

	config << "Destination Locations:\n";

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

	config << "Destination Probabilities: \n";

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

	config << "Destination Average Durations: \n";

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

//Write random lot locations to config
void writeLotLocs(int gridSize, int numLots, ofstream& config, default_random_engine& engine) {

	config << "Lot Locations:\n";

	// Define a continuous Uniform(0,gridSize) distribution
	uniform_real_distribution<double> distribution(0, gridSize);

	// Write locations to config in the format: (x1,y1) (x2,y2) ...
	for (int i = 0; i < numLots; i++) {

		config << "(" << distribution(engine) << "," << distribution(engine) << ") ";
	}

	config << "\n\n";
}

// Write random parking lot capacities to config
void writeLotCapacities(bool randCapacIn, int capac, int avgDemand, int numLots, ofstream& config, default_random_engine& engine) {

	config << "Lot Capacities:\n";

	if (randCapacIn) {
		// Define a discrete Uniform(1,avgDemand) distribution
		uniform_int_distribution<int> distribution(1, avgDemand);

		// Write random capacities to config
		for (int i = 0; i < numLots; i++) {

			config << distribution(engine) << " ";
		}
	}
	else {
		// Write equal capacities to config
		for (int i = 0; i < numLots; i++) {

			config << capac << " ";
		}
	}

	config << "\n\n";
}

// Write random parking lot prices to config
void writeLotPrices(bool randPriceIn, double price, int numLots, ofstream& config, default_random_engine& engine) {

	config << "Lot Prices:\n";

	if (randPriceIn) {
		// Define a continuous Uniform(0,1) distribution 
		uniform_real_distribution<double> distribution(0, 1);

		// Write random prices to config
		for (int i = 0; i < numLots; i++) {

			config << distribution(engine) << " ";
		}
	}
	else {
		// Write equap prices to config
		for (int i = 0; i < numLots; i++) {

			config << price << " ";
		}
	}

	config << "\n\n";
}

// Write driver arrival times to config and return demand (total number of drivers)
int writeDriverArrivals(int avgDemand, ofstream& config, default_random_engine& engine) {

	config << "Driver Arrival Times:\n";

	//Define exponential distribution with arrival rate parameter 
	exponential_distribution<double> distribution(avgDemand);

	// t will store current arrival time
	double t = 0;

	// numDrivers will store the total number of drivers
	int numDrivers = 0;

	while (t <= 1) {

		// Generate next arrival interval and add it to t
		t += distribution(engine);

		// Write arrival time to config
		if (t <= 1) {
			config << t << " ";
			numDrivers++;
		}
	}

	config << "\n\n";

	return numDrivers;
}

// Write random driver arrival locations to config
void writeDriverLocs(int gridSize, int numDrivers, ofstream& config, default_random_engine& engine) {

	config << "Driver Arrival Locations:\n";

	// Define a continuous Uniform(0,gridSize) distribution
	uniform_real_distribution<double> distribution(0, gridSize);

	// Write locations to config in the format: (x1,y1) (x2,y2) ...
	for (int i = 0; i < numDrivers; i++) {

		config << "(" << distribution(engine) << "," << distribution(engine) << ") ";
	}

	config << "\n\n";
}

// Write random driver destinations to config and return list of destinations
list<int> writeDriverDests(list<double> destProbs, int numDrivers, ofstream& config, default_random_engine& engine) {

	config << "Driver Destinations:\n";

	// Define a discrete distribution over the destination IDs based on the destination probabilities
	list<double>::iterator it = destProbs.begin();
	discrete_distribution<int> distribution(destProbs.size(), 0, 1,
		[&destProbs, &it](double){
		auto w = *it;
		it++;
		return w;
	}
	);

	// Write destination IDs to config and save in dests
	int dest;
	list<int> dests;
	for (int i = 0; i < numDrivers; i++) {
		dest = distribution(engine);
		config << dest << " ";
		dests.push_back(dest);
	}

	config << "\n\n";

	return dests;
}

// Write random driver durations to config
void writeDriverDurs(vector<double> avgDurations, list<int> dests, ofstream& config, default_random_engine& engine) {

	config << "Driver Durations:\n";

	// Iterate through the list of driver destinations
	for (list<int>::iterator it = dests.begin(); it != dests.end(); it++) {

		// Define an exponential distribution with parameter avg duration of the current destination
		exponential_distribution<double> distribution(1 / (*(avgDurations.begin() + *it)));

		// Write the random duration to config
		config << distribution(engine) << " ";
	}

	config << "\n\n";
}

// Write random driver max walking distances to config
void writeDriverMaxWalkDists(int gridSize, int numDrivers, ofstream& config, default_random_engine& engine) {

	config << "Driver Max Walking Distances:\n";

	// Define a continuous Uniform(0,gridSize) distribution 
	uniform_real_distribution<double> distribution(0, gridSize);

	// Write prices to config
	for (int i = 0; i < numDrivers; i++) {

		config << distribution(engine) << " ";
	}

	config << "\n\n";
}

// Write random driver max prices to config
void writeDriverMaxPrices(int numDrivers, ofstream& config, default_random_engine& engine) {

	config << "Driver Max Prices:\n";

	// Define a continuous Uniform(0,1) distribution 
	uniform_real_distribution<double> distribution(0, 1);

	// Write prices to config
	for (int i = 0; i < numDrivers; i++) {

		config << distribution(engine) << " ";
	}

	config << "\n\n";

}

// Write random driver importance weight to config
void writeDriverImportWeights(int numDrivers, ofstream& config, default_random_engine& engine) {

	config << "Driver Importance Weight:\n";

	// Define a continuous Uniform(0,1) distribution 
	uniform_real_distribution<double> distribution(0, 1);

	// Write prices to config
	for (int i = 0; i < numDrivers; i++) {

		config << distribution(engine) << " ";
	}

	config << "\n\n";
}