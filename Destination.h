// Destination.h

#ifndef DESTINATION_H
#define DESTINATION_H

#include "Location.h"

class Destination {
	public:
		Destination();
		Destination(int, Location, double weight = 0.5);
		int atDest; // number of people at destination
		
		int getID(); // get id of destination
		Location getLocation();
		double getArrivalWeight(); // get weighted probability of destination
		
		bool update();
		std::string show_status(); // show status of destination
	private:
		int id;
		Location location;
		double areaReadius; // radius of major parking destination
		double arrivalWeight; // rate of entrance to destination
		double avgDuration; // average duration at destination
};

#endif