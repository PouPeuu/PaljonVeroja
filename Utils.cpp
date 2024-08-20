#include "Utils.h"

bool Utils::random_bool() {
	return std::rand() % 2 == 0;
}