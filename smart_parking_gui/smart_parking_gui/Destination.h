// Destination.h

#ifndef DESTINATION_H
#define DESTINATION_H

#include "Location.h"
#include <string>

class Destination {
	public:
		Destination();
		Destination(int, Location, double weight = 10);
		int atDest; // number of people at destination
		
		int getID(); // get id of destination
		Location getLocation();
		double getRate(); // get rate of people entering to calculate costs
		
		bool update();
		std::string show_status(); // show status of destination
	private:
		int id;
		Location location;
		double areaReadius; // radius of major parking destination
		double arrivalRate; // rate of entrance to destination
		double avgDuration; // average duration at destination
};

#endif