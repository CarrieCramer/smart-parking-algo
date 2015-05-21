// Lot.cpp

#include "Lot.h"
#include "Location.h"

Lot::Lot() { // default constructor
	this->id = 0;
	this->location = Location(0,0);
	this->capacity = 0;
	this->numFree = 0;
	this->world = NULL;
}

Lot::Lot(int ID, Location loc, int totalSpots, Grid * as) {
	this->id = ID;
	this->location = loc;
	this->capacity = totalSpots;
	this->numFree = capacity;
	this->world = as;
}

int Lot::getID() {
	return this->id;
}

Location Lot::getLocation() {
	return this->location;
}