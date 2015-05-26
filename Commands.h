// Commands.h
// PA3

#ifndef __Commands__
#define __Commands__
#include "Grid.h"
// Processes user provided commands
// Usable with command-line interface

void do_commands(char, Grid &);

void do_new_driver_command(Grid &); // creates new driver
void do_new_lot_command(Grid &);
void do_new_destination_command(Grid &);
void show_status(Grid &); // displays status of all drivers and lots

#endif // defined Commands
