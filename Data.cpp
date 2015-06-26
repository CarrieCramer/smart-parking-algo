// Data.cpp

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include "Data.h"
using namespace std;

Data::Data() {

}

Data::Data(int numLots) {

	lotOccupancyRates.resize(numLots);
	lotReservedRates.resize(numLots);
	lotCosts.resize(numLots);
}

void Data::writeToExcel() {

	writeDriverData();
	writeLotData();
}

// Writes current data to a CSV file, which can be viewed in Excel
void Data::writeDriverData() {

	// Keeps track of how many drivers' data have already been collected so that this data can be skipped
	static int lastDriverCount = 0;

	// Iterators into all of the driver data vectors that will point to the elements that need to be written
	vector<double>::iterator driverPayoffsIt = driverPayoffs.begin() + lastDriverCount;
	vector<double>::iterator driverCostsIt = driverCosts.begin() + lastDriverCount;
	vector<double>::iterator driverWaitTimesIt = driverWaitTimes.begin() + lastDriverCount;
	vector<double>::iterator driverDriveTimesIt = driverDriveTimes.begin() + lastDriverCount;
	vector<double>::iterator driverWalkDistsIt = driverWalkDists.begin() + lastDriverCount;
	vector<double>::iterator driverArrivalTimesIt = driverArrivalTimes.begin() + lastDriverCount;
	vector<double>::iterator driverDepartureTimesIt = driverDepartureTimes.begin() + lastDriverCount;

	// Declare output stream that will be used to write to the CSV file
	ofstream excelFile;

	// Open "driver_data.csv" in append mode - whatever is written will be appended to the end of the file
	excelFile.open("driver_data.csv", ofstream::app);

	// If this is the first time the file is being written to, write titles
	static bool firstWrite = 1;
	if (firstWrite) {
		excelFile << "Driver Data" << endl;
		excelFile << "Payoff of Reserved Spot, Cost of Reserved Spot, Waiting Time, Driving Time, Walking Distance, Arrival Time, Departure Time" << endl;
		firstWrite = 0;
	}

	// Loop until the end of the driver data vectors is reached
	while ((driverPayoffsIt != driverPayoffs.end()) && (driverCostsIt != driverCosts.end()) && (driverWaitTimesIt != driverWaitTimes.end()) && (driverDriveTimesIt != driverDriveTimes.end()) && (driverWalkDistsIt != driverWalkDists.end())) {

		// Write a new row of data for one driver
		// Commas separate columns
		excelFile << *driverPayoffsIt << "," << *driverCostsIt << "," << *driverWaitTimesIt << "," << *driverDriveTimesIt << "," << *driverWalkDistsIt << "," << *driverArrivalTimesIt << "," << *driverDepartureTimesIt << "," << 0 << endl;

		// Increment all iterators and the counter
		driverPayoffsIt++;
		driverCostsIt++;
		driverWaitTimesIt++;
		driverDriveTimesIt++;
		driverWalkDistsIt++;
		driverArrivalTimesIt++;
		driverDepartureTimesIt++;
		lastDriverCount++;
	}

	excelFile.close();
}

void Data::writeLotData() {

	// Declare output stream that will be used to write to the CSV file
	ofstream excelFile;

	// Open "lot_data.csv" in append mode - whatever is written will be appended to the end of the file
	excelFile.open("lot_data.csv", ofstream::app);

	if (excelFile.is_open()) {
		// If this is the first time the file is being written to, write titles
		static bool firstWrite = 1;

		if (firstWrite) {
			excelFile << "Lot Data" << endl;
			excelFile << "Time, Occupancy Rates, Reserved Rates, Costs" << endl;
			firstWrite = 0;
		}

		// Write the current time
		excelFile << *(lotUpdateTimes.end() - 1) << ",,";

		// Iterate lot-by-lot through the occupancy rates matrix
		for (vector<vector<double>>::iterator currentLot = lotOccupancyRates.begin(); currentLot != lotOccupancyRates.end(); currentLot++) {

			// Write the last entry in the current Lot's occupancy rates vector
			excelFile << *((*currentLot).end() - 1) << ",";
		}

		// Skip a cell in the excel file
		excelFile << ",";

		// Iterate lot-by-lot through the reserved rates matrix
		for (vector<vector<double>>::iterator currentLot = lotReservedRates.begin(); currentLot != lotReservedRates.end(); currentLot++) {

			// Write the last entry in the current Lot's reserved rates vector
			excelFile << *((*currentLot).end() - 1) << ",";
		}

		// Skip a cell in the excel file
		excelFile << ",";

		// Iterate lot-by-lot through the costs matrix
		for (vector<vector<double>>::iterator currentLot = lotCosts.begin(); currentLot != lotCosts.end(); currentLot++) {

			// Write the last entry in the current Lot's costs vector
			excelFile << *((*currentLot).end() - 1) << ",";
		}

		excelFile << endl;

		excelFile.close();
	}
	else {

	}
}

void Data::addLot() { // Adds lot
	lotOccupancyRates.resize(lotOccupancyRates.size()+1);
	lotReservedRates.resize(lotReservedRates.size()+1);
	lotCosts.resize(lotCosts.size()+1);
}

// Returns true if file exists, false if not
bool fileExists(string& fileName) {
	struct stat buffer;
	cout << fileName << " exists" << endl;
	return (stat(fileName.c_str(), &buffer) == 0);
}

