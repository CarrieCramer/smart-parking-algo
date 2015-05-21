// Grid.cpp

#include "Grid.h"
#include <vector>

Grid::Grid() {
	this->time = 0;
	this->size = 10;
}

Grid::Grid(double boardSize) {
	this->time = 0;
	this->size = boardSize;
}

int Grid::getTime() {
	return this->time;
}

vector<int> Grid::allocateParking() { // Called once each driver has a list of potential parking spaces.
	double minSum;
	for (int ii = 0; ii < allWaiting.size(); ii++) {
		for (int jj = 0; jj < allWaiting[ii].feasLots.size(); jj++) {
			
		}
	}
}

vector<Lot> Grid::getAllLots() {
	return this->allLots;
}