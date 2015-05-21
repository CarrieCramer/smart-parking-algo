#include "Destination.h"

Destination::Destination() {
	this->location = Location(0,0);
}

Location Destination::getLocation() {
	return this->location;
}