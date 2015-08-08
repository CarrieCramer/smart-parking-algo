#ifndef PRICING_POLICY_5
#define PRICING_POLICY_5

// Pricing policy 5: Proportional-Derivative Dynamic Pricing

#include <iostream>
#include <vector>
#include "Lot.h"
using namespace std;

void updatePrices5(vector<Lot*> allLots, vector<vector<double>> lotReservedRates, double targetResRate = 0.85, double limit = 0) {

	// Static variable to count the total number of events that have occured
	static int eventCount = 0;

	int interval = 10;

	// Do not update prices for the first interval events
	if (eventCount >= interval) {

		// Iterator for lotReservedRates 
		vector<vector<double>>::iterator currentLotRR = lotReservedRates.begin();

		// Iterate through each Lot
		for (vector<Lot*>::iterator currentLot = allLots.begin(); currentLot != allLots.end(); currentLot++) {

			// Get the Lot's current reserved rate
			double currentResRate = (*currentLot)->getReservedRate();

			// Update the Lot's cost if its current reserved rate is outside of the desired range
			if ((currentResRate < (targetResRate - limit)) || (currentResRate >(targetResRate + limit))) {

				// Get the Lot's current cost
				double currentCost = (*currentLot)->getCost(1.0);

				// Get the Lot's reservation rate from interval events ago
				double prevResRate = *((*currentLotRR).begin() + eventCount - interval);

				// Calculate the new cost = current cost - proportional term + derivative term
				// Proportionality and derivative constants can be changed to improve results
				double newCost = currentCost - (targetResRate - currentResRate)*1.0 + (currentResRate - prevResRate) / interval * 1.0;

				// If the new cost is less than 0, set it to 0. If it is greater than 1, set it to 1. 
				if (newCost < 0.0) {
					newCost = 0.0;
				}
				else if (newCost > 1) {
					newCost = 1.0;
				}

				// Update the Lot's cost
				(*currentLot)->setCost(newCost);
			}

			// Increment lotReservedRates iterator
			currentLotRR++;
		}
	}
	eventCount++;
}

	/* OLD METHOD: UPDATE EVERY 0.1 (TIME)

	// Static variable to count the total number of events that have occured
	static int eventCount = 0;

	// Static variable that stores the event number of the previous update
	static int prevUpdateEventCount = 0;

	// Time interval between price updates. This can be modified to improve results.
	double interval = 0.1;

	// Get the current time and the time that the previous price update occurred
	double currentTime = *(lotUpdateTimes.end() - 1);
	double prevUpdateTime = *(lotUpdateTimes.begin() + prevUpdateEventCount);

	// If the current time >= time of previous update + time interval, do a price update
	if (currentTime >= prevUpdateTime + interval) {
		
		// Iterator for lotReservedRates 
		vector<vector<double>>::iterator currentLotRR = lotReservedRates.begin();

		// Iterate through each Lot
		for (vector<Lot*>::iterator currentLot = allLots.begin(); currentLot != allLots.end(); currentLot++) {

			// Get the Lot's current reserved rate
			double currentResRate = (*currentLot)->getReservedRate();

			// Update the Lot's cost if its current reserved rate is outside of the desired range
			if ((currentResRate < (targetResRate - limit)) || (currentResRate > (targetResRate + limit))) {

				// Get the Lot's current cost
				double currentCost = (*currentLot)->getCost(1.0);

				// Get the Lot's reservation rate during the previous update
				double prevResRate = *((*currentLotRR).begin() + prevUpdateEventCount);

				// Calculate the new cost = current cost - proportional term + derivative term
				// Proportionality and derivative constants can be changed to improve results
				double newCost = currentCost - (targetResRate - currentResRate)*1.0 + (currentResRate - prevResRate)/(currentTime - prevUpdateTime)*1.0;

				// If the new cost is less than 0, set it to 0. If it is greater than 1, set it to 1. 
				if (newCost < 0.0) {
					newCost = 0.0;
				}
				else if (newCost > 1) {
					newCost = 1.0;
				}

				// Update the Lot's cost
				(*currentLot)->setCost(newCost);
			}

			// Increment lotReservedRates iterator
			currentLotRR++;
		}
	
		// Set previous update time to current time and the previous update event count to the current event count
		prevUpdateTime = currentTime;
		prevUpdateEventCount = eventCount;
	}

	// Increment the event counter
	eventCount++;
	*/

#endif