#ifndef PRICING_POLICY_4
#define PRICING_POLICY_4

//Dynamic Pricing Policy similar to LA Express Park 

#include <iostream>
#include <vector>
#include "Lot.h"
using namespace std;


// Helper function for updatePrices4 that calculates the congestion-underuse balance and updates lot's price accordingly
void updatePrice(Lot* lot, double timeCongested, double timeUnderused, double totalTime, double priceStep);

// This function should be called after every Event, but it will only update Lot prices after every numEvents events. 
// Any reserved rate below underuseRate is considered underused. Default (used by LA Express Park) is 0.70
// Any reserved rate above congestionRate is considered congested. Default (used by LA Express Park) is 0.90
// priceStep is the amount by which price is adjusted up or down. Default  is 0.0909090909 (normalized version of LA Express Park's $0.50 steps btwn $0.50 and $6.00)
void updatePrices4(vector<vector<double>> lotReservedRates, vector<double> lotUpdateTimes, vector<Lot*> allLots, int numEvents, double underuseRate = 0.70, double congestionRate = 0.90, double priceStep = 0.0909090909) {

	// This static variable will be incremented each time the function is called in order to count up to numEvents
	// Once it reaches numEvents, the rest of the code in this function will be executed (updating the Lot prices) and the counter will be reset to 0
	static int numEventsCount = 0; 

	// Increment the Events counter
	numEventsCount++;

	if (numEventsCount == numEvents) {

		double timeUnderused; // Amount of time that the parking lot had reserved rate < undueruseRate during the review period
		double timeCongested; // Amount of time that the parking lot had reserved rate > congestionRate during the review period
		double totalTime;	  // Total amount of time in the review period

		// Iterator into allLots
		vector<Lot*>::iterator allLotsIt = allLots.begin();

		// Iterate through each Lot, updating the prices. lotReservedRatesIt1 is an iterator into first dimension of lotReservedRates
		for (vector<vector<double>>::iterator lotReservedRatesIt1 = lotReservedRates.begin(); lotReservedRatesIt1 != lotReservedRates.end(); lotReservedRatesIt1++) {

			timeUnderused = 0;
			timeCongested = 0;
			totalTime = 0;

			// Flag that will be -1 if Lot was underused during previous Event, 1 if it was congested, or 0 if it was neither
			int flag = 0;

			// Iterator into the second dimension of lotReservedRates placed at the first Event of the review period
			vector<double>::iterator lotReservedRatesIt2 = (*lotReservedRatesIt1).end() - numEvents;

			// Set flag for first Event
			if (*lotReservedRatesIt2 < underuseRate) { 
				flag = -1;
			}
			else if (*lotReservedRatesIt2 > congestionRate) {
				flag = 1;
			}

			// prevTime Will keep track of time that previous Event occurred
			vector<double>::iterator lotUpdateTimesIt = lotUpdateTimes.end() - numEvents;
			double prevTime = *lotUpdateTimesIt;

			lotReservedRatesIt2++;
			lotUpdateTimesIt++;

			double timeDiff;

			// Iterate through the rest of the reservation rates in the review period
			for (lotReservedRatesIt2; lotReservedRatesIt2 != (*lotReservedRatesIt1).end(); lotReservedRatesIt2++) {

				// Amount of time between previous Event and and current Event
				timeDiff = *lotUpdateTimesIt - prevTime;

				if (flag == -1) {

					// Add amount of time between previous Event and and current Event to timeUnderused
					timeUnderused += timeDiff;

				}
				else if (flag == 1) {

					// Add amount of time between previous Event and and current Event to timeCongested
					timeCongested += timeDiff;

				}

				// Set flag for current Event
				if (*lotReservedRatesIt2 < underuseRate) {
					flag = -1;
				}
				else if (*lotReservedRatesIt2 > congestionRate) {
					flag = 1;
				}
				else {
					flag = 0;
				}

				// Increase totalTime by timeDiff
				totalTime += timeDiff;

				// Update prevTime to current Event time 
				prevTime = *lotUpdateTimesIt;

				//Update currentEvent to next Event
				lotUpdateTimesIt++;
			}

			// Update Lot price
			updatePrice(*allLotsIt, timeCongested, timeUnderused, totalTime, priceStep);
			allLotsIt++;
		}

		// Reset Event counter to 0
		numEventsCount = 0;
	}
}

// Helper function for updatePrices4 that calculates the congestion-underuse balance and updates lot's price accordingly
void updatePrice(Lot* lot, double timeCongested, double timeUnderused, double totalTime, double priceStep) {

	// Calculate congestion index (fraction of time lot was congested), underuse index (fraction of time lot was underused), and congestion-underuse balance
	double congestionIndex = timeCongested / totalTime;
	double underuseIndex = timeUnderused / totalTime;
	double congestionUnderuseBalance = congestionIndex - underuseIndex;

	// Change the Lot cost if congestion or underuse was the dominant problem

	// Initialize updatedPrice to the Lot's latest cost
	double updatedPrice = lot->getCost(1.0);

	if (congestionUnderuseBalance > 1 / 3) { // Congestion is the dominant problem

		// Add the price step to the current price
		updatedPrice += priceStep;

		// Ensure that the price does not exceed 1
		if (updatedPrice > 1) updatedPrice = 1;
	}
	else if (congestionUnderuseBalance < -1 / 3) { // Underuse is the dominant problem

		// Subtract the price step from the current price
		updatedPrice -= priceStep;

		// Ensure that the price does not go below 0
		if (updatedPrice < 0) updatedPrice = 0;
	}
	
	// Set the Lot's cost variable to updatedPrice
	lot->setCost(updatedPrice);

}


#endif 