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
	writeFile << "Destination Locations:" << endl;
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		writeFile << allDestinations[ii]->getLocation();
		writeFile << " "; // add space
	}
	writeFile << endl;
	writeFile << "Destination Probabilities: " << endl;
	// writeFile << ; // Need to write code for these probabilities
	writeFile << endl;
	writeFile << "Destination Average Durations: " << endl;
	// writeFile << ; // Write code for this
	writeFile << endl;
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
	writeFile << "Driver Speeds:" << endl;
	for (int ii = 0; ii < allUsers.size(); ii++) {
		writeFile << allUsers[ii]->speed; // cost of 1 unit of time
		writeFile << " "; // add space
	}
	writeFile << endl;
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