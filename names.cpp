#include "names.h"

std::vector<std::string> non_nasal_consonants = {"p", "t", "k", "r", "l", "s", "v", "h", "j"};

std::vector<std::string> final_consonants = {"s", "l", "n"};

std::vector<std::string> nasal_pairs = {"mp", "nt", "ns", "nk"};

// Vowels

std::vector<std::string> front_vowels = {"ä", "ö", "y"};
std::vector<std::string> neutral_vowels = {"e", "i"};
std::vector<std::string> back_vowels = {"a", "o", "u"};

std::vector<std::string> front_diphthongs = {"äi", "öi", "yi", "äy", "öy", "ey", "iy", "yö"};
std::vector<std::string> neutral_diphthongs = {"ei", "ie"};
std::vector<std::string> back_diphthongs = {"ai", "oi", "ui", "au", "ou", "eu", "iu", "uo"};

std::vector<std::string> front_doubles = {"ää", "öö", "yy"};
std::vector<std::string> neutral_doubles = {"ee", "ii"};
std::vector<std::string> back_doubles = {"aa", "oo", "uu"};


std::string Names::create_name(bool uppercase_first) {
	bool front = Utils::random_bool();
	std::vector<std::string> vowels = {};

	if (front) {
		vowels.insert(vowels.end(), front_vowels.begin(), front_vowels.end());
		vowels.insert(vowels.end(), front_diphthongs.begin(), front_diphthongs.end());
		vowels.insert(vowels.end(), front_doubles.begin(), front_doubles.end());
	} else {
		vowels.insert(vowels.end(), back_vowels.begin(), back_vowels.end());
		vowels.insert(vowels.end(), back_diphthongs.begin(), back_diphthongs.end());
		vowels.insert(vowels.end(), back_doubles.begin(), back_doubles.end());
	}
	vowels.insert(vowels.end(), neutral_vowels.begin(), neutral_vowels.end());
	vowels.insert(vowels.end(), neutral_diphthongs.begin(), neutral_diphthongs.end());
	vowels.insert(vowels.end(), neutral_doubles.begin(), neutral_doubles.end());

	std::string structure = "";
	
	//														  {"vv", "vk", "kv"}
	structure += Utils::random_choice(std::vector<std::string>{"vk", "kv"});
	for (int i = 0; i < std::rand() % 15; ++i) {
		std::string last_two = structure.substr(structure.size() - 2, 2);
				
		if (last_two == "vv")
			structure += "k";
		if (last_two == "vk")
			structure += Utils::random_choice(std::vector<std::string>{"k", "v"});
		if (last_two == "kv")
			//structure += Utils::random_choice(std::vector<std::string>{"k", "v"});
			structure += "k";
		if (last_two == "kk")
			structure += "v";
	}

	std::string word = "";

	for (unsigned int i = 0; i < structure.size(); ++i) {
		char current = structure[i];

		if (current == 'k') {
			if (i == structure.size() - 1) {
				word += Utils::random_choice(final_consonants);
			} else {
				word += Utils::random_choice(non_nasal_consonants);
			}
		}
		if (current == 'v') {
			word += Utils::random_choice(vowels);
		}
	}

	return word;
}