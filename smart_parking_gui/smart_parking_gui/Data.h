// Data.h

#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>
using namespace std;

class Data {

public:
	
	Data();
	Data(int numLots); // Constructor that should be used - initializes the Lot data vectors

	// Writes current data to CSV files, which can be viewed in Excel 
	void writeToExcel();
	void writeDriverData();
	void writeLotData();
	
	// Adds lots if new lots are initialized
	void addLot();
	
	// Driver Data
	// Index corresponds to Driver id

	vector<double> driverPayoffs;		// Payoff of each Driver's reserved spot 
	vector<double> driverCosts;			// Cost of each Driver's reserved spot 
	vector<double> driverWaitTimes;		// Amount of time from arrival until the Driver's reservation is made 
	vector<double> driverDriveTimes;	// Amount of time from arrival until the Driver arrives at its parking spot 
	vector<double> driverWalkDists;		// Walking distance between Driver's assigned Lot and Destination 
	
	// Lot Data
	// First dimension index corresponds to Lot id
	// Second dimension index corresponds to Event number at which the data was collected 
	
	vector<vector<double>> lotOccupancyRates;	// Lot utilization rate by occupancy (fraction of spots physically occupied)
	vector<vector<double>> lotReservedRates;	// Lot utilization rate by reservation (fraction of spots reserved but not necessarily occupied)	
	vector<vector<double>> lotCosts;			// Lot cost

	vector<double> lotUpdateTimes;

	// Variables used for naming the CSV files 

	int driverFileNum; 
	string driverFileName;
	int lotFileNum;
	string lotFileName;
};

// Returns true if file exists, false if not
bool fileExists(string& fileName);

#endif
