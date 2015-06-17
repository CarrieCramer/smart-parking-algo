// main.cpp
// Compiles with all other .cpp files
// Usable with the command-line interface

#include "Grid.h"
#include "Commands.h"
#include "InputHandling.h"
#include <iostream>
using namespace std;

int main() {
	bool quitLoop = false;
	cout << "Parking Simulator" << endl;
	Grid mainGrid(10, 5); // initialize grid with 5 iterations initalized
	char command; // command asked to enter
	
	while (quitLoop == false) {
		cout << "Enter command: ";
		cin >> command;
		try {
			do_commands(command, mainGrid);
			switch (command) {
				case 'q':
					cout << "Program has ended." << endl;
					quitLoop = true;
					break;
			}
		} catch (InvalidInput& except) {
			cout << "Invalid input: " << except.msg_ptr << endl; // display error message
			command = ' '; // set command to blank space
			cin.clear(); // reset input
			cin.ignore(1000, '\n'); // reset input
		}
	}
	return 0; // end program
}