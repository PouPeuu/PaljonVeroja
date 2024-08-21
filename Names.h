#ifndef NAMES_H
#define NAMES_H

#include "Utils.h"
#include "HobbyDefinition.h"

namespace Names {
	// TODO: load from csv
	extern std::vector<HobbyDefinition> hobbies;

	std::string create_name(bool uppercase_first = true);
	std::pair<std::string, double> create_profession();
	Activity create_hobby();
}

#endif
