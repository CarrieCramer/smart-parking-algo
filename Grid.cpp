// Grid.cpp

#include "Grid.h"
#include <vector>

Grid::Grid() {
	this->time = 0;
}

vector<int> Grid::allocateParking() {
	double minSum;
	for (int ii = 0; ii < allWaiting.size(); ii++) {
		for (int jj = 0; jj < allWaiting[ii].feasResources.size(); jj++) {
			
		}
	}
}

vector<Resource> getAllResources() {
	return allResources;
}