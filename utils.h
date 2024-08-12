#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <unordered_map>

namespace Utils {
	bool randbool();

	template <typename T>
	std::vector<T> merge(std::vector<T> v1, std::vector<T> v2) {
		std::vector<T> result = v1;
		for (T& value : v2) {
			result.push_back(value);
		}
		return result;
	};
}

#endif
