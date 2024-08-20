#include "CSV.h"


std::vector<std::vector<std::string>> CSV::load_csv(fs::path filepath) {
	std::vector<std::vector<std::string>> result;

	std::string line;
	std::ifstream file(filepath);

	assert(file.is_open());

	while (std::getline(file, line)) {
		std::vector<std::string> line_result;

		std::string current = "";
		bool inside_quotes = false;
		bool escape = false;

		for (size_t i = 0; i < line.size(); ++i) {
			char c = line[i];

			if ((!inside_quotes && c == ',')) {
				line_result.push_back(current);
				current.clear();
			} else if (!escape) {
				if (c == '"') {
					inside_quotes = !inside_quotes;
				} else if (c == '\\') {
					escape = true;
				} else {
					current += c;
				}
			} else {
				current += c;
				escape = false;
			}

			if(i == line.size() - 1) {
				line_result.push_back(current);
			}
		}

		result.push_back(line_result);
	}

	file.close();

	return result;
}