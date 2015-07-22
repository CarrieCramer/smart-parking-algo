// Lot.cpp

#include "Lot.h"
#include "Location.h"
#include <iostream>
#include <sstream>
using namespace std;

Lot::Lot() { // default constructor
	this->id = 0;
	this->location = Location(0,0);
	this->capacity = 0;
	this->numFree = 0;
	this->numNotReserved = 0;
	this->peopleLeaving = 0;
	this->cost = 3; // arbitrary value
	this->world = NULL;
}

Lot::Lot(int ID, Location loc, int totalSpots, Grid * as) {
	this->id = ID;
	this->location = loc;
	this->capacity = totalSpots;
	this->numFree = capacity;
	this->numNotReserved = capacity;
	this->peopleLeaving = 0;
	this->cost = 3; // arbitrary value
	this->world = as;
}

Lot::Lot(int ID, Location loc, int totalSpots, double costPerUnit, Grid * as) {
	this->id = ID;
	this->location = loc;
	this->capacity = totalSpots;
	this->numFree = capacity;
	this->numNotReserved = capacity;
	this->peopleLeaving = 0;
	this->cost = costPerUnit; // arbitrary value
	this->world = as;
}

double Lot::getCost(double timeParked) {
	// SAMPLE COST FUNCTION
	return cost*timeParked;
}

double Lot::getBaseCost() {
	return cost;
}

void Lot::setCost(double newCost) {
	this->cost = newCost;
}

void Lot::resetLot() { // Reset number of people at lot
	this->numFree = capacity;
	this->numNotReserved = capacity; 
	peopleLeaving = 0;
	numOfReservers = 0;
	driversToPark.clear(); // clears vector if necessary
	return;
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

int Lot::getOpenSpots() {
	return numFree;
}

double Lot::getOccupancyRate() {
	return ((capacity-numFree)/double(capacity));
}

double Lot::getReservedRate() {
	return ((capacity-numNotReserved)/double(capacity));
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
	double expectedParkingTime;
	if (numNotReserved >= driversToPark.size()) {
		for (int ii = 0; ii < driversToPark.size(); ii++) {
			driversToPark[ii]->goToPark(); // head to parking
			expectedParkingTime = driversToPark[ii]->getTimeArrivedAtPark();
			world->addEvent(Event(world->getTime(), driversToPark[ii], 's'));
			world->addEvent(Event(expectedParkingTime, driversToPark[ii], 'p'));
			driversToPark[ii]->sendData();
		}
		numNotReserved -= driversToPark.size(); // reduce size of reserve queue
	} else { // reserve as many as possible
		for (int ii = 0; ii < numNotReserved; ii++) {
			driversToPark[ii]->goToPark(); // head to parking
			expectedParkingTime = driversToPark[ii]->getTimeArrivedAtPark();
			world->addEvent(Event(world->getTime(), driversToPark[ii], 's'));
			world->addEvent(Event(expectedParkingTime, driversToPark[ii], 'p'));
			driversToPark[ii]->sendData();
		}
		numNotReserved = 0;
	}
	// Send data 
	sendData();
	driversToPark.clear(); // reset driver count
	numOfReservers = 0; // reset reserving at update
	peopleLeaving = 0; // reset number of leaving
	return true;
	
}

Location Lot::getLocation() {
	return this->location;
}

std::string Lot::show_status() {
	std::ostringstream output;
	output << "Lot " << this->getID();
	output << " located at " << this->getLocation();
	output << " has " << numFree << " out of " << capacity;
	output << " spaces free.\r\n";
	return output.str();
}

// Sends current occupancy rate, reserved rate, and cost to data attribute
void Lot::sendData() {

	// If Lot 0, sent time (only Lot 0 does this so that the time is only sent once for all Lots)
	if (id == 0) ((world->data)->lotUpdateTimes).push_back(world->getTime());

	// Send occupancy rate
	(((world->data)->lotOccupancyRates)[id]).push_back(getOccupancyRate());

	// Send reserved rate
	(((world->data)->lotReservedRates)[id]).push_back(getReservedRate());

	// Send cost
	(((world->data)->lotCosts)[id]).push_back(cost);
}