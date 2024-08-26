#ifndef NAMES_H
#define NAMES_H

#include "Utils.h"
#include "ActivityDefinition.h"
#include "Municipality.h"

namespace Names {
	extern std::vector<ActivityDefinition> hobbies;
	extern std::vector<Municipality> municipalities;

	std::string create_name(bool uppercase_first = true);
	std::pair<std::string, double> create_profession();
	Activity create_hobby();
}

#endif
