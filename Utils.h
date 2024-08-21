#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <iterator>
#include <fstream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

namespace Utils {
	template <typename Container>
	typename Container::value_type random_choice(const Container& container) {
		if (container.empty()) {
			throw std::out_of_range("Container is empty");
		}

		std::size_t random_index = std::rand() % container.size();

		return container[random_index];
	}

	template <typename T>
	std::vector<T> merge(std::vector<T> v1, std::vector<T> v2) {
		std::vector<T> result = v1;
		for (T& value : v2) {
			result.push_back(value);
		}
		return result;
	};

	bool random_bool();
	int random_int(int min, int max);
	double random_double(double min, double max);
}

#endif
