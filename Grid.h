#ifndef GRID_H
#define GRID_H

#include <vector>
#include "User.h"
#include "Resource.h"
using namespace std;

class Grid {
	public:
		Grid();
		int getTime(); // return time
		vector<int> allocateParking(); // allocate parking for all waiting and reserved users
		bool update(); // update time and statuses
		voic showStatus();
		void addUser(User);
		void addResource(Resource);
		vector<Resource> getAllResources();
	private:
		double size; // length of one side of the square grid
		double time; // decision point
		vector<User> allUsers;
		vector<User> allWaiting;
		vector<User> allReserved;
		vector<Resource> allResources;
		vector<int> allSpacesLeft;
};

#endif