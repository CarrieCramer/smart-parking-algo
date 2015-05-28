#include "Destination.h"

Destination::Destination() {
	this->location = Location(0,0);
}

Destination::Destination(int i, Location loc) {
	this->id = id;
	this->location = loc;
}

Location Destination::getLocation() {
	return this->location;
}