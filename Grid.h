#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Driver.h"
#include "Lot.h"
using namespace std;

class Grid {
	public:
		Grid();
		int getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		bool update(); // update time and statuses
		voic showStatus();
		void addUser(Driver);
		void addResource(Lot);
		vector<Lot> getAllResources();
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		vector<Driver> allUsers;
		vector<Driver> allWaiting;
		vector<Driver> allReserved;
		vector<Lot> allResources;
		vector<int> allSpacesLeft;
};

#endif