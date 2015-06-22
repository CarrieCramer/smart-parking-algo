#include "Commands.h"
#include "Grid.h"
#include "Lot.h"
#include "Driver.h"
#include "Destination.h"
#include "Location.h"
#include "InputHandling.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void do_commands(char input, Grid & world) {
	switch(input) {
		case 'u': // press u to input info about new driver
			do_new_driver_command(world);
			break;
		case 'l': // press l to input info about new lot
			do_new_lot_command(world);
			break;
		case 'd': // press d to input info about new destination
			do_new_destination_command(world);
			break;
		case 's': // input s to show world status
			display_status(world);
			break;
		case 'w': // input w to save file
			write_file(world);
			break;
		case 'o': // input o to open file
			open_file(world);
			break;
		case 'i':
			set_iteration_modification(world);
			break;
		case 'r':
			run_simulation(world); // run simulation
			break;
		case 'j':
			jump_to_end(world);
			break;
		case 'g':
			advance_by_simulation(world); // g to advance simulation to a point
			break;
		case 'x':
			reset_simulation(world); // reset simulation
			break;
		case 'q':
			break; // do nothing, exit function done in main.cpp
		default:
			display_help();
	}
	return;
}

void do_new_driver_command(Grid & world) { 
	// first check whether there are any destinations to go to
	if (world.getDestinationCount() == 0) throw InvalidInput("Need more destinations to make a driver (type d to create one)");
	int id;
	int destID;
	double arrivalTime;
	double weight;
	double maxCharge;
	double maxDistance;
	double x, y;
	double timeAtPark;
	cout << "Enter the ID of the driver. "; // asks for input on driver
	cin >> id;
	if (id < 0) throw InvalidInput("ID is too small");
	cout << "What is the ID of the destination the driver going to? ";
	cin >> destID;
	Destination * goal = world.findDestinationByID(destID);
	if (goal == NULL) throw InvalidInput("ID does not exist");
	cout << "Input the time when the driver is arriving. ";
	cin >> arrivalTime;
	cout << "How much are you willing to pay? ";
	cin >> maxCharge;
	cout << "How far are you willing to walk? ";
	cin >> maxDistance;
	cout << "Prefer closer parking or lower cost? If equal, set to 0.5." << endl;
	cout << "Otherwise, set it closer to 0 for closer parking" << endl;
	cout << "and closer to 1 for lower cost: ";
	cin >> weight;
	cout << "Enter the location of the driver (ex. 3 2): ";
	cin >> x >> y;
	cout << "How long will you be parking? ";
	cin >> timeAtPark;
	world.addDriver(new Driver(id, arrivalTime, weight, maxDistance, maxCharge, Location(x,y), timeAtPark, goal, &world));
}

void do_new_lot_command(Grid & world) {
	int id;
	double x, y; // coordinates of grid
	int totalSpots;
	cout << "Enter the ID of the lot." << endl;
	cin >> id;
	cout << "Enter the lot location (ex. 1.6 9): ";
	cin >> x >> y;
	cout << "Enter the total number of spots in the lot: ";
	cin >> totalSpots;
	world.addLot(new Lot(id, Location(x,y), totalSpots, &world));
} 
void do_new_destination_command(Grid & world) {
	int id;
	double x;
	double y;
	cout << "Enter the ID of the destination." << endl;
	cin >> id;
	cout << "Enter the destination location (ex. 4 2.3): ";
	cin >> x >> y;
	world.addDestination(new Destination(id, Location(x,y)));
	return;
} // input d to create new destination

void display_status(Grid & world) {
	world.show_status();
} // input s to display status of all drivers and lots

void run_simulation(Grid & world) { // run simulation to end
	cout << "Advancing to next event in simulation" << endl;
	world.update(world.toNextEvent());
	world.show_status();
}

void write_file(Grid & world) { // write data to file
	string fileName;
	ofstream writeFile;
	cout << "Enter the name of the file that you want to write to: " << endl;
	cin.ignore();
	getline(cin, fileName); // type your file name to get it
	writeFile.open(fileName); // works in c++11 only
	world.write_file(writeFile);
	writeFile.close(); // close file
	cout << "File has been written." << endl;
	return;
}

void open_file(Grid & world) { // read data from written file
	// Recommended to do at start of simulation
	string fileName;
	ifstream readFile;
	cout << "Enter the name of the file that you want to open: " << endl;
	cin.ignore();
	getline(cin, fileName); // type your file name to get it
	world.reset(); // reset in the case that there is no error
	readFile.open(fileName); // works in c++11 only	
	if (readFile.is_open()) { // if file exists
		world.read_file(readFile);
	} else {
		throw InvalidInput("File does not exist.");
	}
	readFile.close();
	cout << "File has been read. Press 's' to show status." << endl;
	return;
}

void save_driver_status(Grid & world) {
	
}

void advance_by_simulation(Grid & world) { // input g
	const double timeIncrement = 0.01; // change this to change rate of update
	double passTime;
	double timePassed = 0;
	cout << "Enter the amount of time you wish to pass: ";
	cin >> passTime;
	while (timePassed < passTime) { // updates until the correct time reached
		world.update(timeIncrement);
		timePassed += timeIncrement;
	}
	world.show_status();
}

void jump_to_end(Grid & world) {
	// Continues updating until the end of the simulation.
	while (!world.simulationOver[world.getCurrentIteration()]) {
		world.update(world.toNextEvent());
	}
	world.show_status();
	return;
}

void reset_simulation(Grid & world) {
	world.reset();
	cout << "File has been reset" << endl;
}

void set_iteration_modification(Grid & world) {
	int newIteration;
	cout << "Please select which iteration you want to choose." << endl;
	cin >> newIteration;
	if (world.switchIteration(newIteration) == -1) {
		cout << "Invalid iteration. Please enter a correct number" << endl;
	} 
	return;
}

void display_help() {
	cout << "Enter d to create a new destination for drivers." << endl;
	cout << "Enter l to create a new lot." << endl;
	cout << "Enter u to create a driver to park at these destinations and lots." << endl;
	cout << "Enter r to advance the simulation to the next event." << endl;
	cout << "Enter g to choose how long to advance a simulation." << endl;
	cout << "Enter j to skip to the end of the simulation." << endl;
	cout << "Enter w to save data to a file." << endl;
	cout << "Enter o to read data from a file." << endl;
	cout << "Enter q to quit." << endl;
}
