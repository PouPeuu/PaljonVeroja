#ifndef NAMES_H
#define NAMES_H

#include "Utils.h"
#include "ActivityDefinition.h"

namespace Names {
	extern std::vector<ActivityDefinition> hobbies;

	std::string create_name(bool uppercase_first = true);
	std::pair<std::string, double> create_profession();
	Activity create_hobby();
}

#endif
