#ifndef GRID_H
#define GRID_H

#include <vector>
#include <set> // Used in order to find the order of events.
#include "Event.h"
#include "Driver.h"
#include "Lot.h"
#include "Destination.h"
#include <iostream>
#include <fstream>
using namespace std;

class Driver;
class Lot;
class Event;

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
		double toNextEvent(); // Moves iterator to next event. Returns time to the next event
		int getDestinationCount();
		vector<Lot *> getAllLots();
		Destination * findDestinationByID(int);
		
		void write_file(ofstream&); // Write file in grid
		void read_file(ifstream&); // Read file to grid
		void reset(); // Reset the entire grid
		void addEvent(Event *); // adds a new event to the set
		
		bool update(double timing = 1); // updates the entire grid
		void show_status(); // shows status of all items
		
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		
		vector<Driver *> allUsers; // all drivers currently on the grid
		vector<Lot *> allLots;
		vector<Destination *> allDestinations;
		vector<int> allSpacesLeft;  // currently unused
		set<Event *> allEvents; // set of all events.
		set<Event *>::iterator eventIt; // position of current set iterator
		
		// Will be used when queues are added
		vector<Driver> allWaiting; // all drivers currently waiting
		vector<Driver> allReserved; // all drivers reserved

};

#endif // defined GRID_H