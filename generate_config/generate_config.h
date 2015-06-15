#ifndef GENERATE_CONFIG_H
#define GENERATE_CONFIG_H

#include <fstream>
#include <random>
#include <list>
#include <vector>
using namespace std;

// Obtain the number of simulation iterations. In each iteration, the grid, lot, and destination attributes will remain the same, but there will be a different set of drivers.   
int getNumIterations();

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

// Obtain lot pricing policy number
int getPricePolicy();

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

// Write the pricing policy to config
void writePricePolicy(int pricePolicy, ofstream& config);

// Write random parking lot prices to config
void writeLotPrices(int pricePolicy, double price, int numLots, ofstream& config, default_random_engine& engine);

// Get driver arrival times and return them in a matrix
list<list<double>> generateArrivals(int numIterations, int avgDemand, ofstream& config, default_random_engine& engine);

// Write number of drivers in each simulation iteration to config and return them in a list
list<int> writeNumDrivers(list<list<double>> arrivals, ofstream& config);

// Write driver arrival times to config
void writeDriverArrivals(list<list<double>> arrivals, ofstream& config);

// Write random driver arrival locations to config
void writeDriverLocs(int gridSize, list<int> numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver destinations to config and return list of destinations
list<list<int>> writeDriverDests(list<double> destProbs, list<int> numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver durations to config
void writeDriverDurs(vector<double> avgDurations, list<list<int>> dests, ofstream& config, default_random_engine& engine);

// Write random driver max walking distances to config
void writeDriverMaxWalkDists(int gridSize, list<int> numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver max prices to config
void writeDriverMaxPrices(list<int> numDrivers, ofstream& config, default_random_engine& engine);

// Write random driver importance weight to config
void writeDriverImportWeights(list<int> numDrivers, ofstream& config, default_random_engine& engine);

#endif