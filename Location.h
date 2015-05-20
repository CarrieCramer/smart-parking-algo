#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

class Location{
	public:
		Location();
		Location(double, double);
		double x; // latitude, "x" component
		double y;// longitude, "y" component
};

std::ostream &operator << (std::ostream &, const Location &);

double dist(Location, Location);

#endif