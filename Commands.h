// Commands.h

#ifndef __Commands__
#define __Commands__
#include "Grid.h"
// Processes user provided commands
// Usable with command-line interface

void do_commands(char, Grid &);

void do_new_driver_command(Grid &); // input u to create new driver
void do_new_lot_command(Grid &); // input l to create new lot
void do_new_destination_command(Grid &); // input d to create new destination
void display_status(Grid &); // input s to display status of all drivers and lots

void run_simulation(Grid &); // input r to start the simulation
void advance_by_simulation(Grid &); // input g and then a number to advance simulation to a specific time
// Also, input q to quit.
void display_help(); // input h to display help text

#endif