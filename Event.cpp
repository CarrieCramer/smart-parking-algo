// Event.cpp

#include "Event.h"
#include <iostream>
using namespace std;

Event::Event() {
	this->time = 0;
	this->eventDriver = nullptr;
	this->type = 'z';
}

Event::Event(double timeIn, Driver * driver, char eventType) {
	this->time = timeIn;
	this->eventDriver = driver;
	this->type = eventType;
	cout << "Event at time " << time << " of event type " << type << endl;
}

double Event::getTime() const {
	return this->time;
}

char Event::getType() const {
	return this->type;
}

bool operator< (const Event& e1, const Event& e2)
{
	return (e1.getTime() < e2.getTime());
} // Used in order to use with sets.

// Solution: Once they arrive at their destination before getting a reservation,
// then they can try to set their max distance and max cost to absolute max