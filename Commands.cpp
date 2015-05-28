#include "Commands.h"
#include "Grid.h"

#include <iostream>
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
		case 's':
			display_status(world);
			break;
		default:
			display_help();
	}
	return;
}

void do_new_driver_command(Grid & world) { 
	cout << "Enter the ID of the driver."; // asks for input on driver
	
}

void do_new_lot_command(Grid & world) {
	cout << "Enter the ID of the lot." << endl;
	
} 
void do_new_destination_command(Grid & world) {
	
} // input d to create new destination

void display_status(Grid & world) {
	
} // input s to display status of all drivers and lots
void display_help() {
	cout << "Enter u to create a new driver." << endl;
	
}
