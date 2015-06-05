// Grid.cpp

#include "Grid.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

Grid::Grid() {
	this->time = 0;
	this->timeIncrement = 1;
	this->size = 10;
	
}

Grid::Grid(double boardSize) {
	this->time = 0;
	this->timeIncrement = 1;
	this->size = boardSize;
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
void Grid::addDriver(Driver * toAdd) {
	allUsers.push_back(toAdd);
	return;
}

void Grid::addLot(Lot * toAdd) {
	allLots.push_back(toAdd);
	return;
}

void Grid::addDestination (Destination * toAdd) {
	allDestinations.push_back(toAdd); // add pointer to destination
	return;
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

void Grid::write_file(ofstream& writeFile) {
	writeFile << "Grid Size:" << endl;
	writeFile << this->size << endl;
	writeFile << "Destination Count:" << endl;
	writeFile << allDestinations.size() << endl;
	writeFile << "Destination Locations:" << endl;
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		writeFile << allDestinations[ii]->getLocation();
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Destination Probabilities: " << endl;
	// writeFile << ; // Need to write code for these probabilities
	writeFile << endl;
	writeFile << "Destination Average Durations:" << endl;
	// writeFile << ; // Write code for this
	writeFile << endl;
	writeFile << "Lot Count:" << endl;
	writeFile << allLots.size() << endl;
	writeFile << "Lot Locations:" << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getLocation();
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Lot Capacities:" << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getCapacity();
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Lot Prices:" << endl;
	for (int ii = 0; ii < allLots.size(); ii++) {
		writeFile << allLots[ii]->getCost(1); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Driver Count:" << endl;
	writeFile << allUsers.size() << endl;
	writeFile << "Driver Arrival Locations: " << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->getLocation(); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Driver Destinations:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->dest->getID(); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Driver Arrival Times:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->getArrivalTime(); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Driver Durations:" << endl; // Add time it take for driver to arrive
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->getTimeAtPark(); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Driver Max Walking Distances:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->maxWalkDist; // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;	
	writeFile << "Driver Max Costs:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->maxCharge; // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;		
	writeFile << "Driver Importance Weight:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->importanceWeight; // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;	
	return;
}

void Grid::read_file(ifstream& readFile) {
	// Each destination, lot, and driver has IDs starting with 0 and counting.
	string currentlyRead; // reads current word
	string variableToSet; // finds variable
	// initial count set to 1 in order to prevent compilation errors
	int destCount = 1;
	int lotCount = 1;
	int driverCount = 1;
	double gridSize;
	Location locationRead;
	int intRead;
	double doubleRead;
	vector<Location> destLocs;
	vector<double> destProbs;
	vector<double> destAvgDur;
	vector<Location> lotLocs;
	vector<int> lotCapacities;
	vector<double> lotPrices;
	vector<double> dArrTimes;
	vector<Location> dLocs;
	vector<int> dDest;
	vector<double> dDurations;
	vector<double> dMaxWalkDist;
	vector<double> dMaxCost;
	vector<double> dImportanceWeight;
	
	while (!readfile.eof()) { // while file hasn't ended yet
		readFile >> currentlyRead; // read words from file
		if (currentlyRead == "Grid") {
			readFile >> variableToSet; // read next word
			if (variableToSet == "Size:") { // read size of grid
				readFile >> gridSize;
			}
		} else if (currentlyRead == "Destination") {
			readFile >> variableToSet;
			if (variableToSet == "Count:") {
				readFile >> destCount; // sets count
			}	
			if (variableToSet == "Locations:") { // location
				for (int ii = 0; ii < destCount; ii++) {
					readFile >> locationRead;
					destLocs.push_back(locationRead);
				}
			}
			if (variableToSet == "Probabilities:") { // double
				for (int ii = 0; ii < destCount; ii++) {
					readFile >> doubleRead;
					destProbs.push_back(doubleRead);
				}			
			}
			if (variableToSet == "Average") { // double
				readFile >> variableToSet; // read third word
				if (variableToSet == "Durations:") {
					for (int ii = 0; ii < destCount; ii++) {
						readFile >> doubleRead;
						destAvgDur.push_back(doubleRead);
					}	
				}
			}
		} else if (currentlyRead == "Lot") {
			readFile >> variableToSet;
			if (variableToSet == "Count:") { // int
				readFile >> lotCount; // sets count
			}
			if (variableToSet == "Locations:") { // location
				for (int ii = 0; ii < lotCount; ii++) {
					readFile >> locationRead;
					lotLocs.push_back(locationRead);
				}
			}
			if (variableToSet == "Capacities:") { // int
				for (int ii = 0; ii < lotCount; ii++) {
					readFile >> intRead;
					lotCapacities.push_back(intRead);
				}
			}
			if (variableToSet == "Prices:") { // double
				for (int ii = 0; ii < lotCount; ii++) {
					readFile >> doubleRead;
					lotPrices.push_back(doubleRead);
				}			
			}
		} else if (currentlyRead == "Driver") {
			readFile >> variableToSet;
			if (variableToSet == "Count:") {
				readFile >> driverCount; // sets count
			}
			if (variableToSet == "Arrival") {
				readFile >> variableToSet; // read next word
				if (variableToSet == "Times:") {
					for (int ii = 0; ii < driverCount; ii++) {
						readFile >> doubleRead;
						dArrTimes.push_back(doubleRead);
					}
				} else if (variableToSet == "Locations:") {
					for (int ii = 0; ii < driverCount; ii++) {
						readFile >> locationRead;
						dLocs.push_back(locationRead);
					}
				}
			}
			if (variableToSet == "Destinations:") {
				for (int ii = 0; ii < driverCount; ii++) {
					readFile >> intRead;
					dDest.push_back(intRead);
				}
			}
			if (variableToSet == "Durations:") {
				for (int ii = 0; ii < driverCount; ii++) {
					readFile >> doubleRead;
					dDurations.push_back(doubleRead);
				}
			}
			if (variableToSet == "Max") {
				readFile >> variableToSet;
				if (variableToSet == "Walking") {
					readFile >> variableToSet;
					if (variableToSet == "Distances:") {
						for (int ii = 0; ii < driverCount; ii++) {
							readFile >> doubleRead;
							dMaxWalkDist.push_back(doubleRead);
						}
					}
				}
				if (variableToSet == "Prices:") {
					for (int ii = 0; ii < driverCount; ii++) {
						readFile >> doubleRead;
						dMaxCost.push_back(doubleRead);
					}
				}
			}
			if (variableToSet == "Importance") {
				readFile >> variableToSet;
				if (variableToSet == "Weight:") {
					for (int ii = 0; ii < driverCount; ii++) {
						readFile >> doubleRead;
						dImportanceWeight.push_back(doubleRead);
					}
				}
			}
		} // If it is otherwise then ignore it completely
	}
	// now we set up almost all of the variables
	/*
			vector<Location> destLocs;
			vector<double> destProbs;
			vector<double> destAvgDur;
			vector<Location> lotLocs;
			vector<int> lotCapacities;
			vector<double> lotPrices;
			vector<double> dArrTimes;
			vector<Location> dLocs;
			vector<int> dDest;
			vector<double> dDurations;
			vector<double> dMaxWalkDist;
			vector<double> dMaxCost;
			vector<double> dImportanceWeight;
	*/
	// set up destinations
	for (int ii = 0; ii < destCount; ii++) {
		addDestination(new Destination(ii, destLocs[ii]));
	}
	// set up lots
	for (int jj = 0; jj < lotCount; jj++) {
		addLot(new Lot(jj, lotLocs[jj], lotCapacities[jj],this));
	}
	// set up drivers
	for (int kk = 0; kk < driverCount; kk++) {
		Destination * destPoint = findDestinationByID(dDest[kk]); // first find the destination
		addDriver(new Driver(kk, dArrTimes[kk], dImportanceWeight[kk], 
		                     dMaxWalkDist[kk], dMaxCost[kk], 
				             dLocs[kk], dDurations[kk], destPoint, this));
	}
	return;
}

bool Grid::update(double timing) { // Updates all elements of the grid.
	this->timeIncrement = timing;
	bool stateChanged = false;
	this->time += timeIncrement; // increments time
	for (int ii = 0; ii < allUsers.size(); ii++) {
		if (allUsers[ii]->update()) { // update each and every user
			stateChanged = true;
			if (allUsers[ii]->getState() == 'g') { // if set to leave map
				delete allUsers[ii]; // delete pointer
			}
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
	if (stateChanged) return true;
	else return false;	
}

void Grid::show_status() {
	for (int ii = 0; ii < allUsers.size(); ii++) {
		allUsers[ii]->show_status();
	}
	for (int jj = 0; jj < allLots.size(); jj++) {
		allLots[jj]->show_status();
	}
	for (int hh = 0; hh < allDestinations.size(); hh++) {
		allDestinations[hh]->show_status();
	}
	cout << "Time: " << time << endl;
	return;
}