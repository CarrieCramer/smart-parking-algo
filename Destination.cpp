#include "Destination.h"
#include <iostream>
using namespace std;

Destination::Destination() {
	this->location = Location(0,0);
}

Destination::Destination(int id, double weight, Location loc) {
	this->id = id;
	this->arrivalRate = weight; // rate is determined by weight
	this->location = loc;
}

int Destination::getID() {
	return this->id;
}

Location Destination::getLocation() {
	return this->location;
}

void Destination::show_status() { // show destination location
	cout << "Destination " << id;
	cout << " is located at " << location << endl;
	return;
}