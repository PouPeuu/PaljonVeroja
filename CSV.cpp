#include "CSV.h"

std::vector<std::string> process_line(std::string line) {
	std::vector<std::string> line_result;
	std::string current = "";

	bool inside_quotes = false;
	bool escape = false;

	for (size_t i = 0; i < line.size(); ++i) {
		char c = line[i];

		if (escape) {
			current += c;
			escape = false;
			continue;
		}

		if (!inside_quotes && c == ',') {
			line_result.push_back(current);
			current.clear();
			continue;
		}

		if (c == '\\') {
			escape = true;
			continue;
		}

		if (c == '"') {
			inside_quotes = !inside_quotes;
			continue;
		}

		current += c;
	}

	if (!current.empty()) {
		line_result.push_back(current);
	}
	
	return line_result;
}

std::vector<std::vector<std::string>> CSV::load_csv(fs::path filepath) {
	std::vector<std::vector<std::string>> result;

	std::string line;
	std::ifstream file(filepath);

	assert(file.is_open());

	while (std::getline(file, line)) {
		result.push_back(process_line(line));
	}

	file.close();

	return result;
}