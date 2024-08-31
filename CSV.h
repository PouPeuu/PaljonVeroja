#ifndef CSV_H
#define CSV_H

#include "Utils.h"

namespace CSV {
	std::vector<std::vector<std::string>> load_csv(fs::path filepath);
	void write_csv(fs::path filepath, std::vector<std::vector<std::string>> data);
}

#endif