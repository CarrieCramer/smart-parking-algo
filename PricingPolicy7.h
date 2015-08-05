#ifndef PRICING_POLICY_7
#define PRICING_POLICY_7

// Pricing policy 7: Competitive pricing game
// **************************************************************ADD DESCRIPTION****************************************************

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <dlib/svm.h>
#include "Lot.h"
#include "Location.h"
using namespace std;


// Define the types of the training samples and their labels (required by dlib library) 
typedef dlib::matrix<double, 1, 1> sample_type;
typedef double scalar_type;




// HELPER FUNCTIONS 

// Returns the new Lot price 
// Called in updatePrices7
vector<double> getNewPrices(vector<sample_type>& samples, int& samplesIndex, vector<scalar_type>& closeLotLabels, vector<scalar_type>& farLotLabels, vector<double> closeLotInitPrices, vector<double> farLotInitPrices, double closeLotPrice, double farLotPrice, int& closeLotTotalRes, int& farLotTotalRes, double time, double& firstArrivalTime, double delta);
// Performs linear regression to estimate demand and returns estimate of optimal price
// Called in getNewLotPrice
double getOptPrice(bool isCloseLot, vector<sample_type> samples, vector<scalar_type> labels, double thisLotPrice, double otherLotPrice, double delta, double time);



// MAIN FUNCTION FOR PRICING POLICY 7

// Updates prices of both Lots
void updatePrices7(vector<Lot*> allLots, double time, Location destLoc, double gridSize) {

	// Calculate normalized distance from each Lot to the Destination
	double lot0Dist = dist((*allLots.begin())->getLocation(), destLoc) / (gridSize*sqrt(2));
	double lot1Dist = dist((*(allLots.begin() + 1))->getLocation(), destLoc) / (gridSize*sqrt(2));
	
	// Get ID of closer Lot and further Lot
	// Calculate delta = normalized distance of further lot - normalized distance of closer lot
	int closeLotID;
	int farLotID;
	double delta;

	if (lot0Dist < lot1Dist) {
		closeLotID = 0;
		farLotID = 1;
		delta = lot1Dist - lot0Dist;
	}
	else {
		closeLotID = 1;
		farLotID = 0;
		delta = lot0Dist - lot1Dist;
	}

	// Initialize samples vectors which hold the actual sample values used in training
	// The samples vector must be static so that its values are retained for multiple calls to this function
	//static vector<sample_type> closeLotSamples;
	//static vector<sample_type> farLotSamples;
	static vector<sample_type> samples;

	// Initialize the labels vector which will hold the responses to the samples in the form of arrival rates
	// The labels vector must be static so that its values are retained for multiple calls to this function
	static vector<scalar_type> closeLotLabels;
	static vector<scalar_type> farLotLabels;

	// Initialize counters for each Lot
	//static int closeLotSamplesIndex = 0;	// Index into samples vector
	//static int farLotSamplesIndex = 0;
	static int samplesIndex = 0;
	static int closeLotTotalRes = 0;		// Counts the number of reservations made during the current sample; used to calculate arrival rate for current sample		
	static int farLotTotalRes = 0;
	//static double closeLotLastArrTime = 0;	// Stores the last arrival time of the previous sample; used to calculate arrival rate for current sample
	//static double farLotLastArrTime = 0;
	static double firstArrivalTime = 0;
	
/*	vector<double> closeLotInitPrices;
	for (int i = 500; i <= 900; i += 50) {
		closeLotInitPrices.push_back(i / 1000.0);
	}

	vector<double> farLotInitPrices;
	for (int i = 500; i >= 100; i -= 50) {
		farLotInitPrices.push_back(i / 1000.0); 
	} */

	vector<double> closeLotInitPrices;
	for (int i = 500; i <= 700; i += 25) {
		closeLotInitPrices.push_back(i / 1000.0);
	}

	vector<double> farLotInitPrices;
	for (int i = 500; i >= 300; i -= 25) {
		farLotInitPrices.push_back(i / 1000.0);
	}

	// Get the current Lot prices
	double closeLotPrice = allLots[closeLotID]->getCost(1.0);
	double farLotPrice = allLots[farLotID]->getCost(1.0);
	
	// Initialize new lot prices
	double newCloseLotPrice;
	double newFarLotPrice;

	// If it is the first call of this function, set initial Lot prices to the first sample price (0.5)
	if (firstArrivalTime == 0) {
		
		newCloseLotPrice = *(closeLotInitPrices.begin());
		newFarLotPrice = *(farLotInitPrices.begin());
		
		// Add the first sample, which equals zero because the prices of both lots are equal 
		sample_type firstSample;
		firstSample(0) = (newCloseLotPrice - newFarLotPrice) / delta;
		//closeLotSamples.push_back(firstSample);
		//farLotSamples.push_back(firstSample);
		samples.push_back(firstSample);

		// Set last arrival times to the current time
		firstArrivalTime = time;
	}
	else { 

		// Count the number of reservations made for each Lot since the last event 
		closeLotTotalRes += allLots[closeLotID]->numNewReservations;
		farLotTotalRes += allLots[farLotID]->numNewReservations;

		vector<double> newPrices = getNewPrices(samples, samplesIndex, closeLotLabels, farLotLabels, closeLotInitPrices, farLotInitPrices, closeLotPrice, farLotPrice, closeLotTotalRes, farLotTotalRes, time, firstArrivalTime, delta);
		newCloseLotPrice = *(newPrices.begin());
		newFarLotPrice = *(newPrices.begin() + 1);
		//newCloseLotPrice = getNewLotPrice(samples, closeLotLabels, true, closeLotPrice, farLotPrice, samplesIndex, closeLotTotalRes, time, closeLotLastArrTime, delta);
		//newFarLotPrice = getNewLotPrice(samples, farLotLabels, false, farLotPrice, closeLotPrice, samplesIndex, farLotTotalRes, time, farLotLastArrTime, delta);
	}

	// Set new Lot prices
	(*(allLots.begin() + closeLotID))->setCost(newCloseLotPrice);
	(*(allLots.begin() + farLotID))->setCost(newFarLotPrice);
}


// Calculates new price for the Lot that is closer to the Destination
vector<double> getNewPrices(vector<sample_type>& samples, int& samplesIndex, vector<scalar_type>& closeLotLabels, vector<scalar_type>& farLotLabels, vector<double> closeLotInitPrices, vector<double> farLotInitPrices, double closeLotPrice, double farLotPrice, int& closeLotTotalRes, int& farLotTotalRes, double time, double& firstArrivalTime, double delta) {

	double newCloseLotPrice = closeLotPrice;
	double newFarLotPrice = farLotPrice; 

	// If the number of reservations made for the current sample price exceeds 50 or one hour has passed, the current sample is done
	if ((closeLotTotalRes >= 50) || (farLotTotalRes >= 50) || ((time - firstArrivalTime) > 1.0)) {

		// Add the new arrival rate to labels
		closeLotLabels.push_back(closeLotTotalRes / (time - firstArrivalTime));
		farLotLabels.push_back(farLotTotalRes / (time - firstArrivalTime)); 
		
		// Reset reservation counter to 0
		closeLotTotalRes = 0;
		farLotTotalRes = 0;

		// Set last arrival time to current time
		firstArrivalTime = time;

		// Increment samplesIndex
		++samplesIndex;

		// If only one sample has been taken, return the second sample price
		if (samplesIndex < closeLotInitPrices.size()) {
			
			// Return second sample price for the appropriate Lot
			newCloseLotPrice = *(closeLotInitPrices.begin() + samplesIndex);
			newFarLotPrice = *(farLotInitPrices.begin() + samplesIndex);
		}
		else {
			
			// Perform linear regression on the samples to get the optimal price  
			newCloseLotPrice = getOptPrice(true, samples, closeLotLabels, closeLotPrice, farLotPrice, delta, time);
			newFarLotPrice = getOptPrice(false, samples, farLotLabels, farLotPrice, closeLotPrice, delta, time);
			int dummy = 0;
		}
		
		// Add the new sample value to samples
		sample_type newSample;
		newSample(0) = (newCloseLotPrice - newFarLotPrice) / delta;
		samples.push_back(newSample);
	}
	
	vector<double> newPrices;
	newPrices.push_back(newCloseLotPrice);
	newPrices.push_back(newFarLotPrice);
	return newPrices;
}


double getOptPrice(bool isCloseLot, vector<sample_type> samples, vector<scalar_type> labels, double thisLotPrice, double otherLotPrice, double delta, double time) {

	// Declare an instance of the rr_trainer class, which will be used to do the linear regression
	typedef dlib::linear_kernel<sample_type> kernel_type;
	dlib::rr_trainer<kernel_type> trainer;

	// Train a decision function based on the samples and their labels
	dlib::decision_function<kernel_type> decisionFunc = trainer.train(samples, labels);

	// Get decision function coefficients
	double B0 = decisionFunc.b;
	double B1 = (decisionFunc.basis_vectors)(0)(0); 
	
	/*
	ofstream test;

	if (isCloseLot) {
		test.open("closeTest.csv");
	}
	else {
		test.open("farTest.csv");
	}

	test << "decisionFunc" << endl;
	for (int i = 0; i <= 10; i++)
	{
		sample_type y;
		y(0) = i/10.0;
		test << decisionFunc(y) << endl;
	}

	test.close();
	int dummy = 0;
	*/


	// If the estimated demand function increases as price increases, which cannot be true, so keep the current price and retrain
	sample_type m, n;
	double optPrice;
	if (isCloseLot) {
		m(0) = (0.0 - otherLotPrice) / delta;
		n(0) = (1.0 - otherLotPrice) / delta;
		if (decisionFunc(m) < decisionFunc(n)) {
			return thisLotPrice;
		}
	}
	else  {
		m(0) = (otherLotPrice - 0.0) / delta;
		n(0) = (otherLotPrice - 1.0) / delta;
		if (decisionFunc(m) < decisionFunc(n)) {
			return thisLotPrice;
		}
	}
	
	// Calculate optimal price
	if (isCloseLot) {
		optPrice = -0.5 * (-B0 / B1 * delta - otherLotPrice);
	}
	else {
		optPrice = 0.5 * (-B0 / B1 * delta + otherLotPrice);
	}


	if (optPrice < 0) {
		optPrice = 0.0; 
	}
	else if (optPrice > 1) {
		optPrice = 1.0;
	}

	if (isCloseLot) {
		if (optPrice < otherLotPrice) {
			optPrice = otherLotPrice;
		}
	}
	else {
		if (optPrice > otherLotPrice) {
			optPrice = otherLotPrice;
		}
	}

	/*
	ofstream test;

	if (isCloseLot) {
		test.open("closeTest.csv",ofstream::app);
	}
	else {
		test.open("farTest.csv",ofstream::app);
	}

	test << B0 << "," << B1 << endl;

	test.close();
	// WRITE TO TEST FILES**********************************************************************
	
		ofstream test;

		if (isCloseLot) {
			test.open("closeTest.csv");
		}
		else {
			test.open("farTest.csv");
		}

		test << "decisionFunc" << endl;
		for (int i = 10; i <= 95; i += 5)
		{
			sample_type y;

			double price = i / 100.0;

			if (isCloseLot) {
				y(0) = (i / 100.0 - otherLotPrice) / delta;
			}
			else  {
				y(0) = (otherLotPrice - i / 100.0) / delta;
			}

			test << "," << price << "," << decisionFunc(y) << endl;
		}

		test.close();
		int dummy = 0;
	*/
	//*****************************************************************************************

	return optPrice;
}

#endif


