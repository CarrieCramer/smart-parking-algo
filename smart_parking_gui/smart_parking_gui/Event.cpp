// Event.cpp

#include "Event.h"
#include "Driver.h"
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
	cout << "Event at time " << time << " for Driver " << driver->getID() << " of event type " << type << endl;
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

std::ostream& operator << (std::ostream &os, const Event& event) {
	if (event.eventDriver != nullptr) {
		os << "Event " << event.getTime() << ": Driver " << event.eventDriver->getID();
		switch (event.type) {
		case 'n':
			os << " has appeared at point " << event.eventDriver->getLocation() << ".";
			break;
		case 's':
			os << " has found parking lot " << event.eventDriver->reserved->getID() << ".";
			break;
		case 'p':
			os << " has parked at Lot " << event.eventDriver->reserved->getID() << ".";
			break;
		case 'd':
			os << " has left the map.";
			break;
		default:
			os << " has done an undefined event.";
		}
	}
	else {
		os << "Event 0: Start\n";
	}
	os << "\r\n";
	return os;
}

// Solution: Once they arrive at their destination before getting a reservation,
// then they can try to set their max distance and max cost to absolute max