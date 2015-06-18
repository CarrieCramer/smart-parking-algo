// Grid.cpp

#include "Grid.h"
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "InputHandling.h"
using namespace std;

Grid::Grid() {
	this->time = 0;
	this->numOfIterations = 1;
	this->currentIteration = 0;
	this->timeIncrement = 1;
	this->size = 10;
	this->baseSet.insert(Event());
	allEvents.push_back(baseSet);
	this->eventIt = allEvents[0].begin();
	this->simulationOver[0] = false;
}

Grid::Grid(double boardSize, int iterations) {
	this->time = 0;
	this->timeIncrement = 1;
	cout << "Version 2015 June 17" << endl;
	this->size = boardSize;
	this->numOfIterations = iterations; // how did this get deleted
	this->currentIteration = 0; // also this was deleted
	this->baseSet.insert(Event()); // DOES NOT CHANGE

	vector<Driver *> emptyDriverVector;
	for (int ii = 0; ii < iterations; ii++) { // Add based on iterations
		allUsers.push_back(emptyDriverVector);
		allEvents.push_back(baseSet);
		simulationOver.push_back(false);
	}
	this->eventIt = allEvents[0].begin(); // start at 1st event of 0th iter
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
		iterationNumber = iteration;
	} else iterationNumber = this->currentIteration;
	allUsers[iterationNumber].push_back(toAdd);
	return;
}

void Grid::addLot(Lot * toAdd) {
	allLots.push_back(toAdd);
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

int Grid::getDestinationCount() {
	return allDestinations.size();
}

void Grid::setGridSize(double edgeLength) {
	this->size = edgeLength;
}

double Grid::getGridSize() {
	return this->size;
}

double Grid::toNextEvent() { // Moves set iterator to next event
	while (eventIt->getTime() <= this->time && !simulationOver[currentIteration]) { // while event has lower time than current time
		++eventIt; // go to next event
		if (eventIt == allEvents[currentIteration].end()) {
			cout << "Simulation over." << endl;
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

/* STILL BEING REMADE
void Grid::write_file(ofstream& writeFile) {
writeFile << "****************************************************************************************************" << endl;
writeFile << "NUMBER OF ITERATIONS:" << endl;
writeFile <<
return;
}
*/

void Grid::read_file(ifstream& readFile) {
	// First, reset the entire grid.
	this->reset();
	// Each destination, lot, and driver has IDs starting with 0 and counting.
	string currentlyRead; // reads current word
	// initial count set to 1 in order to prevent compilation errors
	int destCount = 1;
	int lotCount = 1;
	int driverCount = 1;
	Location locationRead;
	int intRead;
	double doubleRead;
	vector<Location> destLocs;
	vector<double> destProbs;
	vector<double> destAvgDur;
	vector<Location> lotLocs;
	vector<int> lotCapacities;
	vector<double> lotPrices;

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
				if (currentlyRead == "****************************************************************************************************") {
					readVal = true;
				} // go to the next line and read it
			}
			else { // otherwise 
				switch (state) {
				case 0:
					if (currentlyRead == "****************************************************************************************************") {
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
		Lot * newLot = new Lot(jj, lotLocs[jj], lotCapacities[jj], this);
		newLot->setCost(lotPrices[jj]);
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
	// set up data
	Data * d = new Data(lotCount);
	this->data = d;

	switchIteration(0);
	return;
}

int Grid::switchIteration(int newIt) { // switches iteration. Resets time. Returns iteration number.
	if (newIt >= numOfIterations || newIt < 0) { // not an iteration
		return -1; // doesn't count
	} else {
		this->time = 0;
		this->eventIt = allEvents[newIt].begin(); // change event iterator
		currentIteration = newIt; // set current iteration
		return newIt;
	}
}

void Grid::reset() { // reset everything back to original state
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
	}
	return stateChanged;
}

void Grid::show_status() {
	for (int ii = 0; ii < allUsers[currentIteration].size(); ii++) {
		allUsers[currentIteration][ii]->show_status();
	}
	for (int jj = 0; jj < allLots.size(); jj++) {
		allLots[jj]->show_status();
	}
	for (int hh = 0; hh < allDestinations.size(); hh++) {
		allDestinations[hh]->show_status();
	}
	cout << "Iteration " << currentIteration << endl;
	cout << "Total iterations: " << numOfIterations << endl;
	cout << "Time: " << time << endl;
	return;
}