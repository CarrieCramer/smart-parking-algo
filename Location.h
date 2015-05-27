#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include "DriveVector.h"

class Location{
	public:
		Location();
		Location(double, double);
		double x; // latitude, "x" component
		double y;// longitude, "y" component
};

std::ostream &operator << (std::ostream &, const Location &);

double dist(Location, Location);
Location operator + (const Location &, const DriveVector &); // adds vector to location
DriveVector operator - (const Location &, const Location &);

#endif