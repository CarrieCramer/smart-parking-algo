// Event.cpp

#include "Event.h"

Event::Event() {
	this->time = 0;
	this->eventDriver = nullptr;
	this->type = 'z';
}

Event::Event(double timeIn, Driver * driver, char eventType) {
	this->time = timeIn;
	this->eventDriver = driver;
	this->type = eventType;
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