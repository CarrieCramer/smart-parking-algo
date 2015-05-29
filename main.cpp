// main.cpp
// Compiles with all other .cpp files
// Usable with the command-line interface

#include "Grid.cpp"
#include "Commands.h"
#include "InputHandling.h"
#include <iostream>
using namespace std;

int main() {
	bool quitLoop = false;
	cout << "Parking Simulator" << endl;
	Grid mainGrid(10); // initialize grid
	char command; // command asked to enter
	
	while (quitLoop = false) {
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
			cout << "Invalid input:" << except.msg_ptr << endl;
			command = ' ';
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}
	return 0;
}