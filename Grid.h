#ifndef GRID_H
#define GRID_H

#include <vector>
#include <set> // Used in order to find the order of events.
#include "Event.h"
#include "Driver.h"
#include "Lot.h"
#include "Destination.h"
#include "Data.h"
#include <iostream>
#include <fstream>
using namespace std;

class Driver;
class Lot;
class Event;


// BUGS:
// Run it event by event, causes error.
// Run all events together, occasionally too many people park.

class Grid {
	public:
		Grid();
		Grid(double);
		Grid(double, int);
		double timeIncrement; // this should stay constant through the simulation
		
		double getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		void addDriver(Driver *, int iteration = -1); // add driver to allUsers for the current iteration
		// Default value adds driver to the current iteration
		void addLot(Lot *); // add lot to allLots
		void addDestination(Destination *); // add destination
		void setGridSize(double); // set grid size to different amount
		double getGridSize();
		double toNextEvent(); // Moves iterator to next event. Returns time to the next event
		int getCurrentIteration();
		int getDriverCount(); // get driver count for current iteration
		int getLotCount(); // get lot count
		int getDestinationCount(); // get number of destinations
		vector<Lot *> getAllLots();
		Destination * findDestinationByID(int);
		
		void write_file(ofstream&); // Write file in grid
		void read_file(ifstream&); // Read file to grid
		void reset(); // Reset the entire grid
		void addEvent(Event, int iteration = -1); // adds a new event to the set
		
		int switchIteration(int); // switches iteration. If valid, returns current iteration.
		// If not valid, returns -1.
		
		vector<bool> simulationOver; // checks the finished state of iteration
		
		bool update(double timing = 1); // updates the entire grid
		void show_status(); // shows status of all items

		Data* data; // Data object that Drivers and Lots will send data to
		
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		int numOfIterations; // number of iterations
		int currentIteration;
		
		vector<vector<Driver *> > allUsers; // all drivers currently on the grid
		vector<Lot *> allLots;
		vector<Destination *> allDestinations;
		vector<int> allSpacesLeft;  // currently unused
		vector<set<Event> > allEvents; // set of all events.
		set<Event>::iterator eventIt; // position of current set iterator
		set<Event> baseSet; // base set inserted into every grid. DO NOT CHANGE
		
		// Will be used when queues are added
		vector<Driver> allWaiting; // all drivers currently waiting
		vector<Driver> allReserved; // all drivers reserved

		int pricingPolicy; // pricing policy

};

#endif // defined GRID_H