// Driver.cpp

#include "Driver.h"
#include "Location.h"
#include "Lot.h"
#include "DriveVector.h"
#include "Event.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <limits> // for maximum double value
using namespace std;

Driver::Driver(int ID, double arrivalTime, double weightScale, 
				double maxDist, double maxPay, Location loc, 
				double timeAtPark, Destination * toReach, Grid * as) {
	this->id = ID;
	try {
		if (weightScale < 0 || weightScale > 1) {
			throw weightScale;
		} else {
			this->importanceWeight = weightScale; // between 0 and 1
		}
	} catch (double e) {
		cout << "Scale value" << e << "must be between 0 and 1 inclusive" << endl;
	}
	this->timeOfArrival = arrivalTime;
	this->timeAtPark = timeAtPark;
	this->maxWalkDist = maxDist;
	this->maxCharge = maxPay;
	this->initmaxWalk = maxDist;
	this->initmaxCharge = maxPay;
	this->location = loc;
	this->startLocation = loc;
	this->dest = toReach;
	this->world = as;
	this->state = 'z';
	this->reservingLot = false; // not reserving lot until finished
	this->speed = (world->getGridSize()) / 0.25; // set speed so that it takes a time of 0.25 to drive across the grid
	world->addEvent(Event(this->timeOfArrival, this, 'n'), world->getCurrentIteration());
}

int Driver::getID() { // Function returns the ID value of driver
	return this->id;
}

Location Driver::getLocation() { // Returns driver's exact location
	return location;
}

Location Driver::getInitialLocation() {
	return startLocation;
}

bool Driver::accept(Lot) { // returns true if accepted, false if refused
	return true; // returns true by default, may be changed
}

bool Driver::isInIA() {
	if (this->getDistToDest() <= world->timeIncrement*speed) { 
		return true;
	} else return false;
}

bool Driver::departLot() { // return true if parked, else return false
	// when returns true, Grid will remove this parker from the list of parked people.
	if (this->state = 'p') {
		// send request to lot to stop parking
		reserved->releaseDriver(); // allot more space
		this->state = 'g'; // leave parking
		return true;
	} else {
		return false;
	}
}

double Driver::getDistToLot() {
	return dist(this->getLocation(), reserved->getLocation());
}

double Driver::getArrivalTime() { // find when the car appeared on the grid
	return timeOfArrival;
}

double Driver::getTimeArrivedAtPark() {
	timeArrivedAtPark = world->getTime() + getDistToLot()/speed;
	return timeArrivedAtPark;
}

double Driver::getTimeAtPark() { // find how long the car is at the park
	return timeAtPark;
}

void Driver::resetLocation() { // reset location and state
	this->location = startLocation;
	this->state = 'z';
	this->maxWalkDist = initmaxWalk;
	this->maxCharge = initmaxCharge;
	this->reservingLot = false;
	reserved = nullptr;
}

void Driver::goToPark() {
	this->state = 'd'; // set to head towards parking lot
	double expectedParkingTime = this->getTimeArrivedAtPark();
	world->addEvent(Event(world->getTime(), this, 's'));
	world->addEvent(Event(expectedParkingTime, this, 'p'));
	sendData();
	setup_destination(reserved->getLocation()); // setup destination
}

Lot* Driver::makeReservation(double timeParking) { // finds potential lots
	// Currently based on the best option given at the time.
	// Later we plan to utilize it better.
	
	feasLots.empty();
	lotDist.empty();
	lotCharge.empty();
	lotCost.empty();
	
	feasLots = findLots(timeParking); // find parking lots
	
	int lotVectSize = feasLots.size();
	int bestLotAt;
	Lot* bestLot = nullptr;
	double minCost = 10000; // arbitrarily large number. All costs are less than 10.
	for (int ii = 0; ii < lotVectSize; ii++) {
		if (lotCost[ii] < minCost) {
			bestLotAt = ii;
			minCost = lotCost[bestLotAt];
			bestLot = feasLots[bestLotAt];
			switch (feasLots[bestLotAt]->getLotType()) {
			case 'r':
				reservingLot = true;
				break;
			case 'e':
				if (feasLots[ii]->getReservedRate() < world->occupationRate) { // placeholder 		
					reservingLot = false;
				}
				else {
					reservingLot = true;
				}
				break;
			default:
				reservingLot = false;
			}
		}
	}
	if (lotVectSize != 0) {
		reservedPayoff = lotCost[bestLotAt];
		return bestLot;
	} else {
		return nullptr; // no lots are available
	}
}

vector<Lot *> Driver::findLots(double timeParking) {
	// initialize vars
	vector<Lot *> lotsAvailable; 
	double distance;
	double charge;
	double cost;
	
	vector<Lot *> allLots = world->getAllLots();
	for (int ii = 0; ii < allLots.size(); ii++) {
		if (allLots[ii]->isFull() == false) { // won't add lot that has no spaces available
			distance = dist(allLots[ii]->getLocation(), dest->getLocation()); // calculate distance
			if (distance <= this->maxWalkDist) { // if destination within walking distance
				switch (allLots[ii]->getLotType()) {
				case 'r':
					charge = allLots[ii]->getCost(timeParking + dist(this->location, allLots[ii]->getLocation()) / this->speed); // calculate cost
					if (charge/timeParking <= this->maxCharge) { // if cost within specified range
						lotsAvailable.push_back(allLots[ii]); // add lot to lots available
						lotDist.push_back(distance);
						lotCharge.push_back(charge);
						cost = (importanceWeight*(charge)+(1 - importanceWeight)*(distance / world->getGridSize()));
						lotCost.push_back(cost);
						reservingLot = true;
					}
					break;
				case 'e':
					if (allLots[ii]->getReservedRate() < world->occupationRate) { // placeholder 
						charge = allLots[ii]->getCost(timeParking); // calculate cost
						reservingLot = false;
					}
					else {
						charge = allLots[ii]->getCost(timeParking + dist(this->location, allLots[ii]->getLocation()) / this->speed); // calculate cost
						reservingLot = true;
					}
					if (charge / timeParking <= this->maxCharge) { // if cost within specified range
						lotsAvailable.push_back(allLots[ii]); // add lot to lots available
						lotDist.push_back(distance);
						lotCharge.push_back(charge);
						cost = (importanceWeight*(charge)+(1 - importanceWeight)*(distance / world->getGridSize()));
						lotCost.push_back(cost);
					}
					break;
				default:
					charge = allLots[ii]->getCost(timeParking); // calculate cost
					reservingLot = false;
					if (charge / timeParking <= this->maxCharge) { // if cost within specified range
						lotsAvailable.push_back(allLots[ii]); // add lot to lots available
						lotDist.push_back(distance);
						lotCharge.push_back(charge);
						cost = (importanceWeight*(charge)+(1 - importanceWeight)*(distance / world->getGridSize()));
						lotCost.push_back(cost);
					}
				}
			}
		}
	}
	return lotsAvailable;
}

bool Driver::update() { // update driver parking, returns true on state change
	/*
	*	Updates what the driver does.
	*  State 'z': Driver has not yet appeared on the grid as it's not his time.
	*  State 'n': Driver has nowhere to park. Will drive towards destination.
	*  State 'd': Driver is driving to parking lot. When reached, will park.
	*  State 'p': Driver is parked and will stay parked until time is up.
	*  State 'g': Driver has finished parking and will leave list of people
	*  in the next state.
	*/
	switch (this->state) {
	case 'z':
		if (world->getTime() >= timeOfArrival) { // if car should arrive at this time
			reserved = makeReservation(timeAtPark); // reserving spot
			if (reserved != nullptr) { // if found reservation
				if (reservingLot == true) { // lot is reserved
					reserved->addToQueue(this);
				}
				goToPark();
			}
			else {
				setup_destination(dest->getLocation()); // go to destination
				this->state = 'n';
			}
			return true;
		}
		else {
			return false;
		}
		break;
	case 'n': // drive towards destination, but waiting for lots
		if (update_location() == true){ // Move the car. If lot not reached:
			this->maxWalkDist = world->getGridSize();
			this->maxCharge = 1.0;
			// set max walk distance and cost to maximum value
		}
		reserved = makeReservation(timeAtPark); // try reserving a spot again
		if (reserved != nullptr) { // if reservation exists
			if (reservingLot == true) { // lot is reserved
				reserved->addToQueue(this);
			}
			else { // send no message to the lot
				goToPark();
			}
			return true;
		}
		return false;
		break;
	case 'd': // drive towards parking lot
		if (update_location() == true) { // move car and check if arrived at parking lot
			if (reserved->isFull()) {
				this->state = 'n'; // still searching for lots
				return true; // end update here
			}
			if (reservingLot == false) {
				reserved->driverHasParked(false);
			}
			else {
				reserved->driverHasParked(true); // show the driver has parked
			}
			timeArrivedAtPark = world->getTime(); // store time of lot arrival
			world->addEvent(Event(timeArrivedAtPark + timeAtPark, this, 'd'));
			this->state = 'p'; // state is now parking
			return true;
		}
		else { // driver hasn't reached parking lot
			return false;
		}
		break;
	case 'p': // parking
		if ((timeArrivedAtPark + timeAtPark) - world->getTime() < 0.00000001) { // floating-point error handling
			departLot(); // leave the lot
			return true;
		}
		else {
			return false;
		}
		break;
	case 'g': // leaving parking
		return false;
	}
}

bool Driver::update_location() { // Moves towards destination. Return true if reached.
	DriveVector distDiff = travelPoint-location;
	double totalDistance = dist(travelPoint,location);
    if (totalDistance != 0) { // check if destination is the same place or not
      this->driveDirection = (travelPoint - location) * ((this->speed/totalDistance)*world->timeIncrement); // delta equation
    }
	if (fabs(distDiff.x) <= fabs(driveDirection.x) && fabs(distDiff.y) <= fabs(driveDirection.y)) { // if driver can reach
		location = travelPoint; // set location to destination
		return true;
	} else {
		location = location + driveDirection; // move driver closer
		return false; 
	}
}

void Driver::setup_destination(Location dest) { // setup where to go
  this->travelPoint = dest; // Destination is set to value
  double totalDistance = dist(travelPoint,location);
  if (totalDistance != 0) { // check if destination is the same place or not
    this->driveDirection = (travelPoint - location) * ((this->speed/totalDistance)*world->timeIncrement); // delta equation
  } else {
    this->driveDirection = DriveVector(0,0);
  }
}

double Driver::getDistToDest() {
	return dist(this->location, dest->getLocation());
}

char Driver::getState() {
	return this->state;
}

string Driver::show_status() { // output driver ID, location, destination, and lot if applicable
	ostringstream output;
	output << "Driver " << this->id;
	switch (this->state) {
		case 'n': // seeking lots
			output << " located at " << this->location << " is seeking lots and heading for Destination " << dest->getID();
			break;
		case 'd': // heading to lot
			output << " located at " << this->location << " is heading to Lot " << reserved->getID();
			break;
		case 'p': // parking
			output << " located at " << this->location << " is parked at Lot " << reserved->getID();
			break;
		case 'g':
			output << " has left the map.";
			break;
		default:
			output.str(std::string()); // empty string
			break; // do nothing
	}
	output << "\r\n"; // newline
	return output.str();
}

// Adds data regarding reserved parking spot to the Driver's data attribute
void Driver::sendData() {
	// Send payoff of parking in reserved Lot 
	((world->data)->driverPayoffs).push_back(reservedPayoff);
	// Send cost of parking in reserved Lot
	((world->data)->driverCosts).push_back(reserved->getCost(1.0));

	// Send waiting time (to make a reservation)
	((world->data)->driverWaitTimes).push_back(world->getTime() - timeOfArrival);

	// Send driving time from arrival location to reserved Lot
	timeArrivedAtPark = this->getTimeArrivedAtPark();
	((world->data)->driverDriveTimes).push_back(timeArrivedAtPark - timeOfArrival);

	// Send walking distance from reserved Lot to destination
	((world->data)->driverWalkDists).push_back(dist(reserved->getLocation(), dest->getLocation()));
}