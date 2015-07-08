#ifndef PRICING_POLICY_6
#define PRICING_POLICY_6

// Pricing policy 6: Uber-like proportional dynamic pricing

#include <iostream>
#include <vector>
#include "Lot.h"
using namespace std;

void updatePrices6(vector<Lot*> allLots, double targetResRate = 0.85, double basePrice = 0.5) {

	// Iterate through each Lot
	for (vector<Lot*>::iterator currentLot = allLots.begin(); currentLot != allLots.end(); currentLot++) {

		// Get the Lot's current occupancy rate
		double currentResRate = (*currentLot)->getReservedRate();

		double newPrice = basePrice;

		// Update the Lot's cost if its current occupancy rate is above the desired occupancy rate
		if (currentResRate > targetResRate) {

			// Calculate the new cost
			newPrice = basePrice + basePrice*(currentResRate - targetResRate);

			// If the new cost is greater than 1, set it to 1. 
			if (newPrice > 1) {
				newPrice = 1.0;
			}
		}

		// Update the Lot's cost
		(*currentLot)->setCost(newPrice);
	}
}


#endif