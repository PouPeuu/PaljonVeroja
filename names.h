#ifndef NAMES_H
#define NAMES_H

#include "utils.h"

namespace Names {
	// TODO: load from csv
	std::vector<std::vector<std::string>> hobbies;

	std::string create_name(bool uppercase_first = true);
	std::pair<std::string, double> create_profession();
}

#endif
