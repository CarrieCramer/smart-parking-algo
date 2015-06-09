// Event.cpp

#include "Event.h"

Event::Event(double timeIn, char eventType) {
	this->time = timeIn;
	this->type = eventType;
}

double Event::getTime() {
	return this->time;
}

char Event::getType() {
	return this->type;
}