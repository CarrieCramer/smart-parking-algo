// Driver.cpp

#include "Driver.h"

Driver::Driver(int ID, double weightScale, LatLng loc, AllocationSystem * as) {
	this->id = ID;
	this->importanceWeight = weightScale; // between 0 and 1
	this->location = loc;
	this->reserveSpot = -1;
	this->world = as;
}

int Driver::getID() {
	return this->id;
}

Location Driver::getLocation() {
	return location;
}

bool Driver::accept(Lot) { // returns true if accepted, false if refused
	return true; // returns true by default, may be changed
}

void Driver::findLots() {
	// locates resources in a specific radius
	// then gets their specific weights
	/*
	vector<Resource> allLots = world->getAllResources();
	for (int ii = 0; ii < allLots.size(); ii++) {
		getDistance(allLots.getLocation(), this->location);
	}
	*/
}