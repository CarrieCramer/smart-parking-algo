#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Driver.h"
#include "Lot.h"
using namespace std;

class Driver;
class Lot;

class Grid {
	public:
		Grid();
		Grid(double);
		double timeIncrement;
		
		
		int getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		void addDriver(Driver); // add driver to allUsers
		void addLot(Lot); // add lot to allLots
		vector<Lot> getAllLots();
		
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		
		vector<Driver> allUsers; // all drivers currently on the grid
		vector<Driver> allWaiting; // all drivers currently waiting
		vector<Driver> allReserved; // all drivers reserved
		vector<Lot> allLots;
		vector<int> allSpacesLeft; 
};

#endif