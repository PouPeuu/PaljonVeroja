#ifndef CSV_H
#define CSV_H

#include "utils.h"

namespace CSV {
	std::vector<std::vector<std::string>> load_csv(fs::path filepath);
}

#endif