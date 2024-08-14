#ifndef FAMILY_H
#define FAMILY_H

#include "person.h"

class Family {
	private:
		std::vector<Adult> parents;
		std::vector<Child> children;
	public:
		Family();
};

#endif