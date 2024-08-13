#include "names.h"

std::vector<std::string> non_nasal_consonants = {"p", "t", "k", "r", "l", "s", "v", "h", "j"};

std::vector<std::string> front_vocals = {"ä", "ö", "y"};
std::vector<std::string> neutral_vocals = {"e", "i"};
std::vector<std::string> back_vocals = {"a", "o", "u"};

Names::create_name(bool uppercase_first) {
	bool front = Utils::randbool();

	
}