#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Driver.h"
#include "Lot.h"
#include "Destination.h"
using namespace std;

class Driver;
class Lot;

class Grid {
	public:
		Grid();
		Grid(double);
		double timeIncrement; // this should stay constant through the simulation
		
		double getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		void addDriver(Driver *); // add driver to allUsers
		void addLot(Lot *); // add lot to allLots
		void addDestination(Destination *);
		int getDestinationCount();
		vector<Lot *> getAllLots();
		Destination * findDestinationByID(int);
		
		bool update(double timing = 1); // updates the entire grid
		void show_status(); // shows status of all items
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		
		vector<Driver *> allUsers; // all drivers currently on the grid
		vector<Lot *> allLots;
		vector<Destination *> allDestinations;
		vector<int> allSpacesLeft; 

		// Will be used when queues are added
		vector<Driver> allWaiting; // all drivers currently waiting
		vector<Driver> allReserved; // all drivers reserved

};

#endif // defined GRID_H