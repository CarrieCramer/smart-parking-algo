// Lot.h

#ifndef LOT_H
#define LOT_H

#include "Location.h"
#include "Grid.h"
#include "Driver.h"
#include <vector>
using namespace std;

class Grid;
class Driver;

class Lot { // the ID of a location 
	public:
		Lot();
		Lot(int, Location, int, Grid *);
		Lot(int, Location, int, double, Grid *); // for prices
		
		// numNotReserved is always less than or equal to numFree
		int getID(); // return ID
		double getOccupancyRate(); // ratio of taken spots to capacity
		double getReservedRate(); // ratio of reserved spots to capacity
		bool isFull(); // detects if lot is full
		
		void releaseDriver(); // releases driver
		void driverHasParked(); // the driver has parked
		
		Location getLocation(); // return location
		int getOpenSpots(); // get total number of open spots
		int getCapacity(); // get capacity of parking
		double getCost(double); // get cost to use parking lot
		void setCost(double); // set cost to use parking lot
		double getBaseCost(); // get the BASE value of the cost to use
		void resetLot(); // Reset lot's empty spaces
		void addToQueue(Driver *); // add driver to queue of parkers
		bool update(); // update number of spots
		void show_status(); // shows status of parking lot
		void sendData(); // sends current occupancy rate, reserved rate, and cost to data attribute

	private:
		int id;
		int peopleLeaving; // counts how many people are leaving
		int numOfReservers; // number of people reserving a lot at the point in time
		vector<Driver*> driversToPark;
		int numFree; // spots not visually taken. Once car parks, this decreases.
		int numNotReserved; // spots not reserved. Once driver reserves, this decreases.
		Location location; // location of lot
		int capacity; // can be 1 for individual or total for parking lots
		double cost;
		Grid * world; // full allocation system
};

#endif