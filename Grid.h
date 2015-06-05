#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Driver.h"
#include "Lot.h"
#include "Destination.h"
#include <iostream>
#include <fstream>
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
		void setGridSize(double); // set grid size to larger
		double getGridSize();
		int getDestinationCount();
		vector<Lot *> getAllLots();
		Destination * findDestinationByID(int);
		
		void write_file(ofstream&); // Write file in grid
		void read_file(ifstream&); // Read file to grid
		
		bool update(double timing = 1); // updates the entire grid
		void show_status(); // shows status of all items
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		
		vector<Driver *> allUsers; // all drivers currently on the grid
		vector<Lot *> allLots;
		vector<Destination *> allDestinations;
		vector<int> allSpacesLeft;  // currently unused

		// Will be used when queues are added
		vector<Driver> allWaiting; // all drivers currently waiting
		vector<Driver> allReserved; // all drivers reserved

};

#endif // defined GRID_H