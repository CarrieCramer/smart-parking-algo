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
	this->peopleLeaving = 0;
	this->world = NULL;
}

Lot::Lot(int ID, Location loc, int totalSpots, Grid * as) {
	this->id = ID;
	this->location = loc;
	this->capacity = totalSpots;
	this->numFree = capacity;
	this->numNotReserved = capacity;
	this->peopleLeaving = 0;
	this->world = as;
}

double Lot::getCost(double timeParked) {
	// SAMPLE COST FUNCTION
	return cost*timeParked;
}

void Lot::setCost(double newCost) {
	this->cost = newCost;
}

int Lot::getID() {
	return this->id;
}

int Lot::getCapacity() {
	return this->capacity;
}

bool Lot::isFull() {
	if (numNotReserved <= 0) {
		return true;
	} else {
		return false;
	}
}

double Lot::getOccupancyRate() {
	return ((capacity-numFree)/capacity);
}

double Lot::getReservedRate() {
	return ((capacity-numNotReserved)/capacity);
}

void Lot::addToQueue(Driver * reserving) {
	driversToPark.push_back(reserving);
	return;
}

void Lot::releaseDriver() {
	peopleLeaving++; // increment the number of people leaving
	return;
}

void Lot::driverHasParked() { // note that a driver has parked
	this->numFree--;
}

bool Lot::update() { // Updates lot information
	/*
	 *	If spots are available, the driver is added to reserve
	 *  on its own update function.
	 *  Once the Lot is being updated,
	 *  each driver is accepted if there are enough spaces.
	 *  In the case of multiple trying to get in, the closest
	 *  to the destination gets it.
	 *  If spot total changes, return true.
	 *  Also, takes a function that counts the number of people 
	 *  exiting the lot.
	*/
	
	// First, check how many people are leaving.
	numFree += peopleLeaving;
	numNotReserved += peopleLeaving;
	// Next, check the drivers and see if they are fit.
	if (numNotReserved >= driversToPark.size()) {
		for (int ii = 0; ii < driversToPark.size(); ii++) {
			driversToPark[ii]->goToPark(); // head to parking
		}
		numNotReserved -= driversToPark.size(); // reduce size of reserve queue
	} else { // reserve as many as possible
		for (int ii = 0; ii < numNotReserved; ii++) {
			driversToPark[ii]->goToPark(); // head to parking
		}
		numNotReserved = 0;
	}
	driversToPark.clear(); // reset driver count
	numOfReservers = 0; // reset reserving at update
	peopleLeaving = 0; // reset number of leaving
	return true;
	
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