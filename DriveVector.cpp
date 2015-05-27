// DriveVector.cpp

#include "DriveVector.h"
#include <cmath>

DriveVector::DriveVector()
{
	this->x = 0.0;
	this->y = 0.0;
}

DriveVector::DriveVector(double x, double y) // initialize direction
{
	this->x = x;
	this->y = y;
}

double DriveVector::getLength() {
	return sqrt(pow(this->x, 2)+pow(this->y, 2));
}

DriveVector operator * (const DriveVector &v1, const double &d) {
  double prodX = v1.x*d;
  double prodY = v1.y*d;
  DriveVector prodVector = DriveVector(prodX, prodY);
  return prodVector;
}
DriveVector operator / (const DriveVector &v1, const double &d) {
  double quotX = v1.x/d;
  double quotY = v1.y/d;
  DriveVector quotVector = DriveVector(quotX, quotY);
  return quotVector;
}
