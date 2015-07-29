// Grid.cpp

#include "Grid.h"
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "InputHandling.h"
#include "PricingPolicy3.h"
#include "PricingPolicy4.h"
#include "PricingPolicy5.h"
#include "PricingPolicy6.h"
using namespace std;

Grid::Grid() { // not used at this time
	this->time = 0;
	this->numOfIterations = 1;
	this->currentIteration = 0;
	this->timeIncrement = 1;
	this->pricingPolicy = 2;
	this->size = 10;
	this->occupationRate = 0.7;
	this->baseSet.insert(Event());
	allEvents.push_back(baseSet);
	this->eventIt = allEvents[0].begin();
	this->simulationOver[0] = false;
	this->data = new Data(0);

}

Grid::Grid(double boardSize, int iterations) { 
	this->time = 0;
	this->timeIncrement = 1;
	this->pricingPolicy = 2;
	cout << "Version 2015 July 10" << endl; // update this date whenever new update
	this->size = boardSize;
	this->occupationRate = 0.7;
	this->numOfIterations = iterations; // how did this get deleted
	this->currentIteration = 0; // also this was deleted
	this->baseSet.insert(Event()); // DOES NOT CHANGE
	
	vector<Driver *> emptyDriverVector;
	for (int ii = 0; ii < numOfIterations; ii++) { // Add based on iterations
		allUsers.push_back(emptyDriverVector);
		allEvents.push_back(baseSet);
		simulationOver.push_back(false);
	}
	this->eventIt = allEvents[0].begin(); // start at 1st event of 0th iter
	this->data = new Data(0);
}

double Grid::getTime() {
	return this->time;
}

/*
vector<int> Grid::allocateParking() { // Called once each driver has a list of potential parking spaces.
	bool minFound = false;
	vector<Driver *> newReserved;
	while (!minFound) {
		double minSum = 0;
		for (int ii = 0; ii < allWaiting.size(); ii++) {
			if (allWaiting[ii].isInIA()) { // more priority
				for (int jj = 0; jj < allWaiting[ii].feasLots.size(); jj++) {

				}
			}
		}
	}
}
*/
void Grid::addDriver(Driver * toAdd, int iteration) {
	int iterationNumber;
	if (iteration != -1) {
		iterationNumber = iteration; // set to current iteration if not set
	} else iterationNumber = this->currentIteration;
	allUsers[iterationNumber].push_back(toAdd);
	return;
}

void Grid::addLot(Lot * toAdd) {
	allLots.push_back(toAdd);
	data->addLot();
	return;
}

void Grid::addDestination(Destination * toAdd) {
	allDestinations.push_back(toAdd); // add pointer to destination
	return;
}

void Grid::addEvent(Event toAdd, int iteration) {
	int iterationNumber;
	if (iteration != -1) {
		iterationNumber = iteration;
	}
	else iterationNumber = this->currentIteration;
	allEvents[iterationNumber].insert(toAdd); // inserts and sorts event by time
}

void Grid::setGridSize(double edgeLength) {
	this->size = edgeLength;
}

double Grid::getGridSize() {
	return this->size;
}

Event Grid::getCurrentEvent() {
	return *eventIt; // returns current event
}

double Grid::toNextEvent() { // Moves set iterator to next event
	while (eventIt->getTime() <= this->time && !simulationOver[currentIteration]) { // while event has lower time than current time
		++eventIt; // go to next event
		if (eventIt == allEvents[currentIteration].end()) {
			simulationOver[currentIteration] = true;
			return 0; // return 0
		}
	}

	// event with a different time reached, return difference
	if (simulationOver[currentIteration] || eventIt == allEvents[currentIteration].end()) {
		cout << "Simulation over." << endl;
		simulationOver[currentIteration] = true;
	}
	return (eventIt->getTime() - this->time);
}

vector<Lot *> Grid::getAllLots() {
	return this->allLots;
}

vector<Location> Grid::getDestLocations() {
	vector<Location> allLocs;
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		allLocs.push_back(allDestinations[ii]->getLocation());
	}
	return allLocs;
}

vector<Location> Grid::getLotLocations() {
	vector<Location> allLocs;
	for (int ii = 0; ii < allLots.size(); ii++) {
		allLocs.push_back(allLots[ii]->getLocation());
	}
	return allLocs;
}

vector<Location> Grid::getDriverLocations() {
	vector<Location> allLocs;
	Driver * toCheck;
	for (int ii = 0; ii < allUsers[currentIteration].size(); ii++) {
		toCheck = allUsers[currentIteration][ii];
		if (toCheck->getState() != 'z') {
		allLocs.push_back(toCheck->getLocation());
		}
	}
	return allLocs;
}
vector<Location> Grid::getDriverLocations(int iteration) {
	vector<Location> allLocs;
	Driver * toCheck;
	for (int ii = 0; ii < allUsers[iteration].size(); ii++) {
		toCheck = allUsers[iteration][ii];
		if (toCheck->getState() != 'z') {
		allLocs.push_back(toCheck->getLocation());
		}
	}
	return allLocs;
}

Destination * Grid::findDestinationByID(int correctID) {
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		if (allDestinations[ii]->getID() == correctID) { // correct destination found
			return allDestinations[ii];
		}
	}
	return NULL; // if none are found then return null pointer
}

int Grid::getCurrentIteration() {
	return this->currentIteration;
}

int Grid::getIterationCount() { // returns number of iterations
	return this->numOfIterations;
}

void Grid::write_file(ofstream& writeFile) {
	string asterisks = "****************************************************************************************************";
	string simItNotice = "Each row corresponds to one simulation iteration.";
	writeFile << asterisks << endl;
	writeFile << "NUMBER OF ITERATIONS:" << endl;
	writeFile << "During each iteration, a new set of drivers with random attributes will be generated." << endl;
	writeFile << "The grid, lot, and destination attributes will remain the same throughout all iterations." << endl;
	writeFile << asterisks << endl;
	writeFile << numOfIterations << endl;
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "GRID SIZE:" << endl;
	writeFile << "The grid represents a 2-D, square, Cartesian space, with its lower left corner at (0, 0)." << endl;
	writeFile << "The grid size is a positive integer value representing the maximum x and y-coordinates." << endl;
	writeFile << asterisks << endl;
	writeFile << size << endl;
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DESTINATION COUNT:" << endl;
	writeFile << "Total number of destinations on the grid." << endl;
	writeFile << asterisks << endl;
	writeFile << allDestinations.size() << endl;
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DESTINATION LOCATIONS:" << endl;
	writeFile << "Coordinates of each destination in the format: (x1,y1) (x2,y2) (x3,y3) ..." << endl;
	writeFile << "The coordinates are real numbers that do not exceed the grid size." << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		writeFile << allDestinations[ii]->getLocation() << ' ';
	}
	writeFile << endl; // end writeFile line
	writeFile << endl; // newline
	writeFile << asterisks << endl; // skip destination probabilities and average durations for now
	writeFile << "LOT COUNT:" << endl;
	writeFile << "Total number of parking lots on the grid." << endl;
	writeFile << asterisks << endl;
	writeFile << allLots.size() << endl;
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "LOT LOCATIONS:" << endl;
	writeFile << "Coordinates of each lot in the format: (x1,y1) (x2,y2) (x3,y3) ..." << endl;
	writeFile << "The coordinates are real numbers that do not exceed the grid size." << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getLocation() << ' ';
	}
	writeFile << endl; // end line
	writeFile << endl; // blank line
	writeFile << asterisks << endl;
	writeFile << "LOT CAPACITIES:" << endl;
	writeFile << "Number of parking spots in each parking lot." << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getCapacity() << ' ';
	}
	writeFile << endl; // end line
	writeFile << endl; // blank line
	writeFile << asterisks << endl;
	writeFile << "LOT PRICING POLICY:" << endl;
	writeFile << "Options:" << endl;
	writeFile << "1 | Equal Static Pricing: all lots have the same price, which remains the same throughout the simulation" << endl;
	writeFile << "2 | Random Static Pricing: lots have randomized prices, which remain the same throughout the simulation" << endl;
	writeFile << "3 | Real-time, proportional dynamic pricing" << endl;
	writeFile << asterisks << endl;
	writeFile << pricingPolicy << endl;
	writeFile << endl;	
	writeFile << asterisks << endl;
	writeFile << "LOT PRICES:" << endl;
	writeFile << "Parking rate (price per unit of time) for each lot." << endl;
	writeFile << "Note that parking rates are normalized from 0 to 1." << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getBaseCost() << ' ';
	}
	writeFile << endl;
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER COUNT:" << endl;
	writeFile << "Number of drivers that arrives during each simulation iteration." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		writeFile << allUsers[ii].size() << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER ARRIVAL TIMES:" << endl;
	writeFile << "Arrival times of each driver in ascending order." << endl;
	writeFile << "Note that the simulation time is normalized from 0 to 1." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->getArrivalTime() << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER ARRIVAL LOCATIONS:" << endl;
	writeFile << "Coordinates of the location of each driver at its arrival time in the format: (x1,y1) (x2,y2) (x3,y3) ..." << endl;
	writeFile << "The coordinates are real numbers that do not exceed the grid size." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->getInitialLocation() << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER DESTINATIONS:" << endl;
	writeFile << "ID number of each driver's destination." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->dest->getID() << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER DURATIONS:" << endl;
	writeFile << "The amount of time that each driver will remain at its parking spot after arriving at the lot." << endl;
	writeFile << "Note that the simulation time is normalized from 0 to 1." << endl;
	writeFile << "A duration greater than 1 means that the driver will stay beyond the end of the simulation iteration." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->getTimeAtPark() << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER MAX WALKING DISTANCES:" << endl;
	writeFile << "The maximum distance that each driver is willing to walk from its assigned lot to its destination." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->initmaxWalk << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER MAX PRICES:" << endl;
	writeFile << "The maximum parking rate (price per unit time) that each driver is willing to pay." << endl;
	writeFile << "Note that parking rates are normalized from 0 to 1." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->initmaxCharge << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	writeFile << asterisks << endl;
	writeFile << "DRIVER IMPORTANCE WEIGHTS:" << endl;
	writeFile << "A value for each driver representing the relative importance of parking price vs. walking distance." << endl;
	writeFile << "These weights are real and normalized from 0 to 1." << endl;
	writeFile << simItNotice << endl;
	writeFile << asterisks << endl;
	for (int ii = 0; ii < numOfIterations; ii++) {
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			writeFile << allUsers[ii][jj]->importanceWeight << " ";
		}
		writeFile << endl;
	}
	writeFile << endl;
	return;
}


void Grid::read_file(ifstream& readFile) {
	// First, reset the entire grid.
	this->reset();
	// Each destination, lot, and driver has IDs starting with 0 and counting.
	string asterisks = "****************************************************************************************************";
	string currentlyRead; // reads current word
	// initial count set to 1 in order to prevent compilation errors
	int destCount = 1;
	int lotCount = 1;
	int driverCount = 1;
	Location locationRead;
	int intRead;
	double doubleRead;
	char charRead;
	vector<Location> destLocs;
	vector<double> destProbs;
	vector<double> destAvgDur;
	vector<Location> lotLocs;
	vector<int> lotCapacities;
	vector<double> lotPrices;
	vector<char> lotTypes;

	vector<int> emptyInt;
	vector<double> emptyDouble;
	vector<Location> emptyLocation;
	vector<Driver *> emptyDriverVector;

	vector<int> dCounts; // driver counts
	vector<vector<double> > dArrTimes;
	vector<vector<Location> > dLocs;
	vector<vector<int> > dDest;
	vector<vector<double> > dDurations;
	vector<vector<double> > dMaxWalkDist;
	vector<vector<double> > dMaxCost;
	vector<vector<double> > dImportanceWeight;

	/*
	Read file state:
	0. Read file line by line
	1. Check for string of asterisks.
	2. Check for specific variable to set.
	3. Check for next string of asterisks.
	4. Immediately after, check for the numbers to set the variables to.
	5. Also, figure out how to set iterations.
	*/

	bool readVal = false; // if ready to read values, set to true
	int iterationToAdd = 0;
	int state = 0; // determines which variable to set. 0 indicates that we need to see asterisks. Other values meant to set values.
	try {
		while (getline(readFile, currentlyRead) && !readFile.eof()) { // read line each time
			istringstream iss(currentlyRead); // for cases of multiple variables to set on line
			if (state != 0 && state != 1 && !readVal) {
				if (currentlyRead == asterisks) {
					readVal = true;
				} // go to the next line and read it
			}
			else { // otherwise 
				switch (state) {
				case 0:
					if (currentlyRead == asterisks) {
						// if reading a long line of asterisks
						state = 1; // State 1 means we have to check for a variable to set
					}
					break;
				case 1: // Since switch files don't work on strings if-statements are used.
					if (currentlyRead == "NUMBER OF ITERATIONS:") state = 2;
					else if (currentlyRead == "GRID SIZE:") state = 3;
					else if (currentlyRead == "DESTINATION COUNT:") state = 4;
					else if (currentlyRead == "DESTINATION LOCATIONS:") state = 5;
					else if (currentlyRead == "DESTINATION PROBABILITIES:") state = 6;
					else if (currentlyRead == "DESTINATION AVERAGE DURATIONS:") state = 7;
					else if (currentlyRead == "LOT COUNT:") state = 8;
					else if (currentlyRead == "LOT LOCATIONS:") state = 9;
					else if (currentlyRead == "LOT CAPACITIES:") state = 10;
					else if (currentlyRead == "LOT PRICING POLICY:") state = 11;
					else if (currentlyRead == "LOT PRICES:") state = 12;
					else if (currentlyRead == "AVERAGE DEMAND:") state = 13;
					else if (currentlyRead == "DRIVER COUNT:") state = 14;
					else if (currentlyRead == "DRIVER ARRIVAL TIMES:") state = 15;
					else if (currentlyRead == "DRIVER ARRIVAL LOCATIONS:") state = 16;
					else if (currentlyRead == "DRIVER DESTINATIONS:") state = 17;
					else if (currentlyRead == "DRIVER DURATIONS:") state = 18;
					else if (currentlyRead == "DRIVER MAX WALKING DISTANCES:") state = 19;
					else if (currentlyRead == "DRIVER MAX PRICES:") state = 20;
					else if (currentlyRead == "DRIVER IMPORTANCE WEIGHTS:") state = 21;
					else if (currentlyRead == "LOT TYPES:") state = 22;
					else if (currentlyRead == "MAX OCCUPATION RATE:") state = 23;
					else {
						throw InvalidInput("Error: File variable read incorrectly.");
					}
					break; // end of file reading
				case 2: // iteration count
					iss >> intRead;
					this->numOfIterations = intRead; // set number of iterations
					allUsers.clear();
					allEvents.clear();
					for (int ii = 0; ii < numOfIterations; ii++) {
						allUsers.push_back(emptyDriverVector);
						allEvents.push_back(baseSet);
						dArrTimes.push_back(emptyDouble);
						simulationOver.push_back(false);
						dLocs.push_back(emptyLocation);
						dDest.push_back(emptyInt);
						dDurations.push_back(emptyDouble);
						dMaxWalkDist.push_back(emptyDouble);
						dMaxCost.push_back(emptyDouble);
						dImportanceWeight.push_back(emptyDouble);
					}
					state = 0;
					readVal = false; // not reading values
					break; // to be implemented
				case 3: // grid size
					iss >> doubleRead;
					this->size = doubleRead; // set size
					readVal = false;
					state = 0;
					break;
				case 4: // destination count
					iss >> intRead;
					destCount = intRead;
					readVal = false;
					state = 0;
					break;
				case 5: // destination locations (same for each iteration)
					for (int ii = 0; ii < destCount; ii++) { // iterate over previously read destination count
						iss >> locationRead;
						destLocs.push_back(locationRead); // add location to vector
					}
					state = 0;
					readVal = false;
					break;
				case 6: // destination probabilities (config file statistic)
					state = 0;
					readVal = false;
					break; // to be used
				case 7: // average duration at destination (config stat)
					state = 0;
					readVal = false;
					break; // to be used
				case 8: // lot count
					iss >> intRead;
					lotCount = intRead;
					state = 0;
					readVal = false;
					break;
				case 9: // location of lots (same per iteration)
					for (int ii = 0; ii < lotCount; ii++) { // iterate over previously read destination count
						iss >> locationRead;
						lotLocs.push_back(locationRead); // add location to vector
					}
					state = 0;
					readVal = false;
					break;
				case 10: // capacities of lot
					for (int ii = 0; ii < lotCount; ii++) {
						iss >> intRead;
						lotCapacities.push_back(intRead); // add int to vector
					}
					state = 0;
					readVal = false;
					break;
				case 11: // policy of lot pricing
					iss >> intRead;
					this->pricingPolicy = intRead;
					state = 0;
					readVal = false;
					break; // to be added
				case 12: // lot prices
					for (int ii = 0; ii < lotCount; ii++) {
						iss >> doubleRead;
						lotPrices.push_back(doubleRead); // add to vector
					}
					state = 0;
					readVal = false;
					break; // to be added
				case 22: // lot type
					for (int ii = 0; ii < lotCount; ii++) {
						iss >> charRead;
						lotTypes.push_back(charRead);
					}
					state = 0;
					readVal = false;
					break;
				case 13: // average demand
					state = 0;
					readVal = false;
					break; // to be added
				case 14: // driver count
					iss >> intRead;
					dCounts.push_back(intRead);
					iterationToAdd++;
					break; // support for multiple iterations to be done later
				case 15: // driver arrival times
					for (int jj = 0; jj < dCounts[iterationToAdd]; jj++) {
						iss >> doubleRead;
						dArrTimes[iterationToAdd].push_back(doubleRead);
					}
					iterationToAdd++;
					break;
				case 16: // driver arrival locations (starting points)
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> locationRead;
						dLocs[iterationToAdd].push_back(locationRead);
					}
					iterationToAdd++;
					break;
				case 17: // driver destinations
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> intRead;
						dDest[iterationToAdd].push_back(intRead);
					}
					iterationToAdd++;
					break;
				case 18: // duration of parking drivers
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> doubleRead;
						dDurations[iterationToAdd].push_back(doubleRead);
					}
					iterationToAdd++;
					break;
				case 19: // max walking distance
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> doubleRead;
						dMaxWalkDist[iterationToAdd].push_back(doubleRead);
					}
					iterationToAdd++;
					break;
				case 20: // max allowed prices
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> doubleRead;
						dMaxCost[iterationToAdd].push_back(doubleRead);
					}
					iterationToAdd++;
					break;
				case 21: // importance weights
					for (int ii = 0; ii < dCounts[iterationToAdd]; ii++) {
						iss >> doubleRead;
						dImportanceWeight[iterationToAdd].push_back(doubleRead);
					}
					iterationToAdd++;
					break;
				case 23:
					iss >> doubleRead;
					occupationRate = doubleRead;
					state = 0;
					readVal = false;
					break;
				default:
					throw InvalidInput("File reading state corrupted");
				} // end of switch statement
				if (iterationToAdd >= numOfIterations) {
					iterationToAdd = 0;
					state = 0;
					readVal = false;
				}
			} // end of else statement
		} // end of getline while loop
	}
	catch (InvalidInput& except) {
		cout << except.msg_ptr << endl; // exception found, ask to try again
		cout << "Please reconfigure your file and try again." << endl;
		return;
	}
	// now we set up almost all of the variables
	// set up destinations
	for (int ii = 0; ii < destCount; ii++) {
		addDestination(new Destination(ii, destLocs[ii]));
	}
	destLocs.clear();
	destProbs.clear();
	destAvgDur.clear();

	// set up lots
	for (int jj = 0; jj < lotCount; jj++) {
		Lot * newLot = new Lot(jj, lotLocs[jj], lotCapacities[jj], lotPrices[jj], lotTypes[jj], this);
		addLot(newLot);
	}
	lotLocs.clear();
	lotCapacities.clear();
	lotPrices.clear(); // clear up space in memory

	// set up drivers
	for (int ii = 0; ii < numOfIterations; ii++) {
		currentIteration = ii;
		for (int kk = 0; kk < dCounts[ii]; kk++) {
			Destination * destPoint = findDestinationByID(dDest[ii][kk]); // first find the destination
			addDriver(new Driver(kk, dArrTimes[ii][kk], dImportanceWeight[ii][kk],
				dMaxWalkDist[ii][kk], dMaxCost[ii][kk],
				dLocs[ii][kk], dDurations[ii][kk], destPoint, this), ii);
		}
	}
	delete this->data;
	// set up data
	Data * d = new Data(lotCount);
	this->data = d;

	switchIteration(0);
	return;
}

int Grid::getDriverCount() {
	return allUsers[currentIteration].size();
}
int Grid::getDriverCount(int iteration) {
	return allUsers[iteration].size();
}

int Grid::getLotCount() {
	return allLots.size();
}

int Grid::getDestinationCount() {
	return allDestinations.size();
}

int Grid::switchIteration(int newIt) { // switches iteration. Resets time. Returns iteration number.
	if (newIt >= numOfIterations || newIt < 0) { // not an iteration
		return -1; // doesn't count
	} else {
		this->time = 0;
		this->eventIt = allEvents[newIt].begin(); // change event iterator
		for (int ii = 0; ii < allLots.size(); ii++) {
			allLots[ii]->resetLot(); // reset lot info
		}
		for (int ii = 0; ii < allUsers.size(); ii++) {
			allUsers[currentIteration][ii]->resetLocation();
		}
		currentIteration = newIt; // set current iteration
		this->simulationOver[newIt] = false; // set simulation to not over
		return newIt;
	}
}

void Grid::reset() { // reset everything back to original state
	delete this->data;
	this->time = 0;
	this->timeIncrement = 1;
	this->size = 10;
	for (int ii = 0; ii < numOfIterations; ii++) { // Add based on iterations
		for (int jj = 0; jj < allUsers[ii].size(); jj++) {
			delete allUsers[ii][jj]; // remove user from memory
		}
	}
	allUsers.clear();
	for (int ii = 0; ii < allLots.size(); ii++) {
		delete allLots[ii];
	}
	allLots.clear();
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		delete allDestinations[ii];
	}
	allDestinations.clear();
	allEvents.clear();
	allSpacesLeft.clear();
	allWaiting.clear();
	allReserved.clear();
	simulationOver.clear();
	vector<Driver *> emptyDriverVector;
	for (int ii = 0; ii < numOfIterations; ii++) { // Add based on iterations
		allUsers.push_back(emptyDriverVector);
		allEvents.push_back(baseSet);
		simulationOver.push_back(false);
	}
	this->addEvent(Event()); // base event
	this->eventIt = allEvents[0].begin();
	this->data = new Data(0);
}

bool Grid::update(double timing) { // Updates all elements of the grid.
	this->timeIncrement = timing; // change time increment based on time it takes
	bool stateChanged = false;
	this->time += timeIncrement; // increments time
	if (timing > 0) {
		for (int ii = 0; ii < allUsers[currentIteration].size(); ii++) {
			if (allUsers[currentIteration][ii]->update()) { // update each and every user
				stateChanged = true;
				// deleting the pointer was causing trouble, not deleting
			} // keep updating after that
		}
		for (int jj = 0; jj < allLots.size(); jj++) {
			if (allLots[jj]->update()) { // update all lots
				stateChanged = true;
			} // keep updating after that
		}
		for (int hh = 0; hh < allDestinations.size(); hh++) {
			if (allDestinations[hh]->update()) { // update all destinations
				stateChanged = true;
			} // keep updating after that
		}
		data->writeToExcel();
		switch (pricingPolicy) {
		case 3:
			updatePrices3(allLots);
			break;
		case 4:
			updatePrices4(data->lotReservedRates, data->lotUpdateTimes, allLots, this->time, 0.1);
			break;
		case 5:
			updatePrices5(data->lotUpdateTimes, allLots, data->lotReservedRates);
			break;
		case 6:
			updatePrices6(allLots);
			break;
		}
	}
	return stateChanged;
}

string Grid::show_status() {
	ostringstream output;
	for (int ii = 0; ii < allUsers[currentIteration].size(); ii++) {
		output << allUsers[currentIteration][ii]->show_status() << endl;
	}
	for (int jj = 0; jj < allLots.size(); jj++) {
		output << allLots[jj]->show_status() << endl;
	}
	for (int hh = 0; hh < allDestinations.size(); hh++) {
		output << allDestinations[hh]->show_status() << endl;
	}
	return output.str();
}