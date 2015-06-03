// Lot.cpp

#include "Lot.h"
#include "Location.h"
#include <iostream>
using namespace std;

Lot::Lot() { // default constructor
	this->id = 0;
	this->location = Location(0,0);
	this->capacity = 0;
	this->numFree = 0;
	this->numNotReserved = 0;
	this->world = NULL;
}

Lot::Lot(int ID, Location loc, int totalSpots, Grid * as) {
	this->id = ID;
	this->location = loc;
	this->capacity = totalSpots;
	this->numFree = capacity;
	this->numNotReserved = capacity;
	this->world = as;
}

double Lot::getCost(double timeParked) {
	// SAMPLE COST FUNCTION
	if (timeParked < 4) {
		return 14.0;
	} else if (timeParked < 5) {
		return 20.0;
	} else {
		return 4*timeParked;
	}
}

int Lot::getID() {
	return this->id;
}

bool Lot::update() { // Updates lot information
	
}

Location Lot::getLocation() {
	return this->location;
}

void Lot::show_status() {
	cout << "Lot " << this->getID();
	cout << " located at " << this->getLocation();
	cout << " has " << numFree << " out of " << capacity;
	cout << " spaces free." << endl;
	return;
}