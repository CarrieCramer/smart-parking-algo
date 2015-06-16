// Data.cpp

#include <iostream>
#include <fstream>
#include "Data.h"
using namespace std;

Data::Data() {

}

Data::Data(int numLots) {

	vector<double> l;

	// Push back numLots vectors to each of the Lot data vectors
	for (int i = 0; i < numLots; i++) {
		lotOccupancyRates.push_back(l);
		lotReservedRates.push_back(l);
		lotCosts.push_back(l);
	}
}

void Data::writeToExcel() {

	writeDriverData();
	writeLotData();
}

// Writes current data to a CSV file, which can be viewed in Excel
void Data::writeDriverData() {
	
	// Iterators into all of the driver data vectors that will keep track of which element to write to the file
	// Static iterators are used so that we can append new data to the end of the file, rather than overwriting the file with all data each time this function is called
	static vector<double>::iterator driverPayoffsIt = driverPayoffs.begin();
	static vector<double>::iterator driverCostsIt = driverCosts.begin();
	static vector<double>::iterator driverWaitTimesIt = driverWaitTimes.begin();
	static vector<double>::iterator driverDriveTimesIt = driverDriveTimes.begin();
	static vector<double>::iterator driverWalkDistsIt = driverWalkDists.begin();

	// Declare output stream that will be used to write to the CSV file
	ofstream excelFile;

	// Open "driver_data.csv" in append mode - whatever is written will be appended to the end of the file
	excelFile.open("driver_data.csv", ofstream::app);

	// If this is the first time that the file is being written to, write the titles to the file
	if (driverPayoffsIt == driverPayoffs.begin()) {
	
		excelFile << "Driver Data" << endl;
		excelFile << "Payoff of Reserved Spot, Cost of Reserved Spot, Waiting Time, Driving Time, Walking Distance" << endl;
	}
	
	// Loop until the end of the driver data vectors is reached
	while ((driverPayoffsIt != driverPayoffs.end()) && (driverCostsIt != driverCosts.end()) && (driverWaitTimesIt != driverWaitTimes.end()) && (driverDriveTimesIt != driverDriveTimes.end()) && (driverWalkDistsIt != driverWalkDists.end())) {
		
		// Write a new row of data for one driver
		// Commas separate columns
		excelFile << *driverPayoffsIt << "," << *driverCostsIt << "," << *driverWaitTimesIt << "," << *driverDriveTimesIt << "," << *driverWalkDistsIt << endl;
	
		// Increment all iterators
		driverPayoffsIt++;
		driverCostsIt++;
		driverWaitTimesIt++;
		driverDriveTimesIt++;
		driverWalkDistsIt++;
	}

	excelFile.close();
}

void Data::writeLotData() {

	// Declare output stream that will be used to write to the CSV file
	ofstream excelFile;

	// Open "driver_data.csv" in append mode - whatever is written will be appended to the end of the file
	excelFile.open("lot_data.csv", ofstream::app);

	// If this is the first time the file is being written to, write titles
	static bool firstWrite = 1;

	if (firstWrite) {
		excelFile << "Lot Data" << endl;
		excelFile << "Occupancy Rates,,Reserved Rates,,Costs" << endl;
	}


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
	
	// Go to the next row in the excel file
	excelFile << endl;

	excelFile.close();
		
}
