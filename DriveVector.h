//
//  DriveVector.h
//  Used to indicate which direction a car goes on a map

#ifndef __DriveVector__
#define __DriveVector__

#include <iostream>

class DriveVector // determines the direction a car drives
{
public:
	double x;
	double y;
	
	double getLength(); // gets length of vector
    
	DriveVector();
	DriveVector(double, double);
};

DriveVector operator * (const DriveVector &, const double &); // multiplies vector by amount
DriveVector operator / (const DriveVector &, const double &); // divides vector by amount

#endif // defined __DriveVector__