#ifndef GENERATE_CONFIG_H
#define GENERATE_CONFIG_H

#include <fstream>
#include <random>
#include <list>
#include <vector>
using namespace std;

// Obtain grid size from user input
int getGridSize();

// Obtain average demand from user input
int getAvgDemand();

// Obtain number of lots from user input
int getNumLots();

// Obtain whether lot capacities are equal or random from user input
bool randCapac();

// Obtain lot capacity if user chooses to use equal lot capacities
int getLotCapac();

// Obtain whether lot prices are equal or random from user input
bool randPrice();

// Obtain lot price if user chooses to use equal lot prices
double getLotPrice();

// Obtain number of destinations from user input
int getNumDests();

// Obtain whether destination probabilities are equal or random from user input
bool randDestProbs();

// Write random destination locations to config
void writeDestLocs(int gridSize, int numDests, ofstream& config, default_random_engine& engine);

// Write destination probabilities (probability that a driver will choose that destination) to config and return the probabilities in a list
list<double> writeDestProbs(bool randDestProbsIn, int numDests, ofstream& config, default_random_engine& engine);

// Write random destination average durations to config
vector<double> writeDestAvgDurs(int numDests, ofstream& config, default_random_engine& engine);

// Write random parking lot locations to config
void writeLotLocs(int gridSize, int numLots, ofstream& config, default_random_engine& engine);

// Write random parking lot capacities to config
void writeLotCapacities(bool randCapacIn, int capac, int avgDemand, int numLots, ofstream& config, default_random_engine& engine);

// Write random parking lot prices to config
void writeLotPrices(bool randPriceIn, double price, int numLots, ofstream& config, default_random_engine& engine);

// Write driver arrival times to config and return demand (total number of drivers)
int writeDriverArrivals(int avgDemand, ofstream& config, default_random_engine& engine);

// Write random driver arrival locations to config
void writeDriverLocs(int gridSize, int numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver destinations to config and return list of destinations
list<int> writeDriverDests(list<double> destProbs, int numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver durations to config
void writeDriverDurs(vector<double> avgDurations, list<int> dests, ofstream& config, default_random_engine& engine);

// Write random driver max walking distances to config
void writeDriverMaxWalkDists(int gridSize, int numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver max prices to config
void writeDriverMaxPrices(int numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver importance weight to config
void writeDriverImportWeights(int numDrivers, ofstream& config, default_random_engine& engine);

#endif