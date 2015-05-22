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

int Grid::getTime() {
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
vector<Lot> Grid::getAllLots() {
	return this->allLots;
}