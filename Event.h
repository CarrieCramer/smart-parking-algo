// Event.h
// Contains a list of time periods where a car
/*
 * 1. reserves a parking space
 * 2. parks at a parking space
 ** a. For this case, lists a time when car parks after reserve.
 ** Grid indicates the usage of lots by reservation vs occupancy.
 * 3. departs a parking space.
*/

#ifndef EVENT_H
#define EVENT_H

class Event {
	public:
		Event(double, char);
		double getTime();
		char getType();
	private:
		double time;
		char type;
};

#endif