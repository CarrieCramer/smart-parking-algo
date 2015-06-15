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
	this->timeIncrement = 1;
	this->size = 10;
	this->addEvent(Event()); // base event
	this->eventIt = allEvents.begin();
	this->simulationOver = false;
}

Grid::Grid(double boardSize) {
	this->time = 0;
	this->timeIncrement = 1;
	this->size = boardSize;
	this->addEvent(Event()); // base event
	this->eventIt = allEvents.begin();
	this->simulationOver = false;
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

void Grid::addEvent(Event toAdd) {
	allEvents.insert(toAdd); // inserts and sorts event by time
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
	cout << eventIt->getTime() << endl;
	while (eventIt->getTime() <= this->time) { // while event has lower time than current time
		++eventIt; // go to next event
		if (eventIt == allEvents.end()) {
			cout << "Simulation over." << endl;
			this->simulationOver = true;
			return 0; // return 0
		}
	}
		// event with a different time reached, return difference
	if (eventIt == allEvents.end()) {
		cout << "Simulation over." << endl;
		this->simulationOver = true;
	}
	return (eventIt->getTime()-this->time);
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
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		writeFile << 1; // write code for this later
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Destination Average Durations:" << endl;
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		writeFile << 1; // write code for this later
		writeFile << " "; // add space
	}
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
	writeFile << "Driver Arrival Times:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->getArrivalTime(); // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
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
	writeFile << "Driver Max Prices:" << endl;
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
	// First, reset the entire grid.
	this->reset();
	// Each destination, lot, and driver has IDs starting with 0 and counting.
	string currentlyRead; // reads current word
	string variableToSet; // finds variable
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
	vector<double> dArrTimes;
	vector<Location> dLocs;
	vector<int> dDest;
	vector<double> dDurations;
	vector<double> dMaxWalkDist;
	vector<double> dMaxCost;
	vector<double> dImportanceWeight;
	
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
				switch(state) {
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
						for (int ii = 0; ii < lotCount; ii++) {
							iss >> doubleRead;
							lotPrices.push_back(doubleRead); // add to vector
						}						
						state = 0;
						readVal = false;
						break; // to be added
					case 12: // lot prices
						state = 0;
						readVal = false;
						break; // to be added
					case 13: // average demand
						state = 0;
						readVal = false;
						break; // to be added
					case 14: // driver count
						iss >> intRead;
						driverCount = intRead;
						state = 0;
						readVal = false;
						break; // support for multiple iterations to be done later
					case 15: // driver arrival times
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> doubleRead;
							dArrTimes.push_back(doubleRead);
						}
						state = 0;
						readVal = false;
						break;
					case 16: // driver arrival locations (starting points)
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> locationRead;
							dLocs.push_back(locationRead);
						}
						state = 0;
						readVal = false;
						break;
					case 17: // driver destinations
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> intRead;
							dDest.push_back(intRead);
						}
						state = 0;
						readVal = false;
						break;
					case 18: // duration of parking drivers
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> doubleRead;
							dDurations.push_back(doubleRead);
						}
						state = 0;
						readVal = false;
						break;
					case 19: // max walking distance
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> doubleRead;
							dMaxWalkDist.push_back(doubleRead);
						}
						state = 0;
						readVal = false;
						break;
					case 20: // max allowed prices
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> doubleRead;
							dMaxCost.push_back(doubleRead);
						}
						state = 0;
						readVal = false;
						break;
					case 21: // importance weights
						for (int ii = 0; ii < driverCount; ii++) {
							iss >> doubleRead;
							dImportanceWeight.push_back(doubleRead);
						}
						state = 0;
						readVal = false;
						break;
					default:
						throw InvalidInput("File reading state corrupted");
				} // end of switch statement
			} // end of else statement
		} // end of getline while loop
	} catch (InvalidInput& except) {
		cout << except.msg_ptr << endl; // exception found, ask to try again
		cout << "Please reconfigure your file and try again." << endl;
		return;
	}
	// now we set up almost all of the variables
	// set up destinations
	for (int ii = 0; ii < destCount; ii++) {
		addDestination(new Destination(ii, destLocs[ii]));
	}
	// set up lots
	for (int jj = 0; jj < lotCount; jj++) {
		Lot * newLot = new Lot(jj, lotLocs[jj], lotCapacities[jj], this);
		newLot->setCost(lotPrices[jj]);
		addLot(newLot);
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

void Grid::reset() { // reset everything back to original state
	this->time = 0;
	this->timeIncrement = 1;
	this->size = 10;
	allUsers.clear();
	allLots.clear();
	allDestinations.clear();
	allSpacesLeft.clear();
	allWaiting.clear();
	allReserved.clear();
	allEvents.clear();
	this->addEvent(Event()); // base event
	this->eventIt = allEvents.begin();
	this->simulationOver = false;
}

bool Grid::update(double timing) { // Updates all elements of the grid.
	this->timeIncrement = timing; // change time increment based on time it takes
	bool stateChanged = false;
	this->time += timeIncrement; // increments time
	for (int ii = 0; ii < allUsers.size(); ii++) {
		if (allUsers[ii]->update()) { // update each and every user
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