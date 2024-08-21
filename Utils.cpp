#include "Utils.h"

bool Utils::random_bool() {
	return std::rand() % 2 == 0;
}

int Utils::random_int(int min, int max) {
	int diff = max - min;
	return (std::rand() % diff) + min;
}

double Utils::random_double(double min, double max) {
	double diff = max - min;
	return (double) std::rand() / RAND_MAX * diff + min;
}