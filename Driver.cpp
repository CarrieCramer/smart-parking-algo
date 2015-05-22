// Driver.cpp

#include "Driver.h"
#include <iostream>
using namespace std;

Driver::Driver(int ID, double weightScale, Location loc, Grid * as) {
	this->id = ID;
	try {
		if (weightScale < 0 || weightScale > 1) {
			throw weightScale;
		} else {
			this->importanceWeight = weightScale; // between 0 and 1
		}
	} catch (double e) {
		cout << "Weight" << e << "must be between 0 and 1 inclusive" << endl;
	}
	this->location = loc;
	this->reserveSpot = -1;
	this->world = as;
}

int Driver::getID() {
	return this->id;
}

Location Driver::getLocation() {
	return location;
}

bool Driver::accept(Lot) { // returns true if accepted, false if refused
	return true; // returns true by default, may be changed
}

bool Driver::isInIA() {
	if (this->getDistToDest() <= world->timeIncrement*speed) {
		return true;
	} else return false;
}

Lot * Driver::makeReservation(double timeAtPark) { // finds potential lots
	// Currently based on the best option given at the time.
	// Later we plan to utilize it better.
	feasLots = findLots(double timeAtPark); // time taken to park
	int lotVectSize = feasLots.size();
	int bestLotAt;
	Lot * bestLot;
	double minCost = 10000; // arbitrarily large number. All costs are less than this.
	for (int ii = 0; ii < lotVectSize; ii++) {
		if (lotCost[ii] < minCost) {
			minCost = lotCost[ii];
			bestLot = feasLots[ii];
			bestLotAt = ii;
		}
	}
	cout << "Minimum lot at ID " << bestLot->getID() << "." << endl;
	cout << "Distance: " << lotDist[bestLotAt] << ". Charge: " << lotCharge[bestLotAt] << endl;
	return bestLot;
}

vector<Lot *> Driver::findLots(double timeAtPark) {
	vector<Lot *> lotsAvailable;
	double distance;
	double charge;
	double cost;
	vector<Lot> allLots = world->getAllLots();
	for (int ii = 0; ii < allLots.size(); ii++) {
		if (allLots[ii].numFree != 0) { // won't add lot that has no spaces available
			distance = dist(allLots[ii].getLocation(), dest->getLocation());
			if (distance <= this->maxWalkDist) {
				charge = allLots[ii].getCost(timeToPark);
				if (charge <= this->maxCharge) {
					lotsAvailable.push_back(&allLots[ii]);
					lotDist.push_back(dist);
					lotCharge.push_back(charge);
					cost = importanceWeight*(charge/maxCharge) + (1-importanceWeight)*(distance/maxWalkDist);
					lotCost.push_back(cost);
				}
			}
		}
	}
	return lotsAvailable;
}

double Driver::getDistToDest() {
	return dist(this->location, dest->location);
}