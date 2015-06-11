// Event.h
// Contains a list of time periods where a car
/*
 * 1. 's' marks the event when a spot is successfully reserved. This generates 2 more events.
 * 2. 'p' is then added for the exact time when a parking lot is reached.
     a. This is placed at a time that is the distance to the lot divided by the speed, rounded up.
 ** a. For this case, lists a time when car parks after reserve.
 ** Grid indicates the usage of lots by reservation vs occupancy.
 * 3. 'd' is added at the time when a car leaves a parking lot.
     a. This is placed at the time listed after the parking event.
*/

#ifndef EVENT_H
#define EVENT_H

class Driver;

class Event {
	public:
		Event();
		Event(double, Driver *, char);
		double getTime() const;
		char getType() const;
		
	private:
		double time;
		Driver * eventDriver; // driver that caused the event
		char type;
};

bool operator < (const Event&, const Event&);

#endif