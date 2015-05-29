// Grid.cpp

#include "Grid.h"
#include <vector>

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
void Grid::addDriver(Driver toAdd) {
	allUsers.push_back(toAdd);
	return;
}

void Grid::addLot(Lot toAdd) {
	allLots.push_back(toAdd);
	return;
}

int Grid::getDestinationCount() {
	return allDestinations.size();
}

void Grid::addDestination (Destination toAdd) {
	allDestinations.push_back(toAdd);
}

vector<Lot> Grid::getAllLots() {
	return this->allLots;
}

Destination * Grid::findDestinationByID(int correctID) {
	for (int ii = 0; ii < allDestinations.size(); ii++) {
		if (allDestinations[ii].getID() == correctID) { // correct destination found
			return &(allDestinations[ii]);
		}
	}
	return NULL; // if none are found then return null pointer
}

bool Grid::update() { // Updates all elements of the grid.
	bool stateChanged = false;
	this->time += timeIncrement; // increments time
	for (int ii = 0; ii < allUsers.size(); ii++) {
		if (allUsers[ii].update()) { // update each and every user
			stateChanged = true;
		} // keep updating after that
	}
	// possibly update lots and destinations later, but there really isn't much to update about them now
	if (stateChanged) return true;
	else return false;	
}

void Grid::show_status() {
	for (int ii = 0; ii < allUsers.size(); ii++) {
		allUsers[ii].show_status();
	}
	for (int jj = 0; jj < allLots.size(); jj++) {
		allUsers[jj].show_status();
	}
	for (int hh = 0; hh < allDestinations.size(); hh++) {
		allDestinations[hh].show_status();
	}
	return;
}