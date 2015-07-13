#include "Location.h"
#include <iostream>
#include <cmath>

Location::Location() {
	this->x = 0;
	this->y = 0;
}

Location::Location(double lat, double lon) {
	this->x = lat;
	this->y = lon;
}

std::ostream &operator << (std::ostream &os, const Location &point) {
  os << "(";
  os << point.x;
  os << ",";
  os << point.y;
  os << ")";
  return os;
}

std::istream &operator >> (std::istream &is, Location &point) {
	double ix, iy;
	char par1, comma, par2; // parentheses and comma
	is >> par1 >> ix >> comma >> iy >> par2;
	point.x = ix;
	point.y = iy;
	return is;
}

double dist(Location point1, Location point2) {
    return sqrt(pow((point2.x-point1.x), 2)+pow((point2.y-point1.y), 2));
}

Location operator + (const Location & p1, const DriveVector & v1) {
	double sumX = p1.x+v1.x;
	double sumY = p1.y+v1.y;
	Location addResult = Location(sumX, sumY);
	return addResult;
}

DriveVector operator - (const Location & p1, const Location & p2) {
	double diffX = p1.x-p2.x;
	double diffY = p1.y-p2.y;
	DriveVector diffVector = DriveVector(diffX, diffY); // initializes the difference
	return diffVector;
}