#include "Destination.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Destination::Destination() {
	this->location = Location(0,0);
}

Destination::Destination(int id, Location loc, double weight) {
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


bool Destination::update() { // Possibly used to change the demand of the destination over time
	return true;
}

string Destination::show_status() { // show destination location
	ostringstream output;
	output << "Destination " << id;
	output << " is located at " << location << "\r\n";
	return output.str();
}