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
		int getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		void addUser(Driver);
		void addResource(Lot);
		vector<Lot> getAllLots();
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		vector<Driver> allUsers;
		vector<Driver> allWaiting;
		vector<Driver> allReserved;
		vector<Lot> allLots;
		vector<int> allSpacesLeft; 
};

#endif