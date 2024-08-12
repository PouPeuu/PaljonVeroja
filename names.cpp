#include "names.h"

std::vector<std::string> consonants = {"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "w", "x", "z", "ng"};

std::vector<std::string> back_vowels = {"a", "o", "u"};
std::vector<std::string> neutral_vowels = {"e", "i"};
std::vector<std::string> front_vowels = {"ä", "ö", "y"};

std::vector<std::string> back_diphthongs = {"ai", "oi", "ui", "au", "ou", "eu", "iu", "uo", "ey"};
std::vector<std::string> neutral_diphthongs = {"ei", "ie"};
std::vector<std::string> front_diphthongs = {"äi", "öi", "yi", "äy", "öy", "yö"};

std::vector<std::string> back_doubled = {"aa", "oo", "uu"};
std::vector<std::string> neutral_doubled = {"ee", "ii"};
std::vector<std::string> front_doubled = {"ää", "öö", "yy"};

std::vector<std::string> obstruents = {"p", "t", "k", "d", "s", "h", "v", "ts"};
std::vector<std::string> liquids = {"l", "r"};
std::vector<std::string> coronals = {"t", "d", "s", "l", "r"};

std::vector<std::string> word_initial_consonants = {"h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "v"};
std::vector<std::string> word_final_consonants = {"t", "s", "n", "r", "l"};

typedef enum {
	INITIAL,
	MEDIAL,
	FINAL
} WordPos;

typedef enum {
	SINGLE,
	DIPHTHONG,
	DOUBLE
} VowelType;

std::unordered_map<VowelType, std::vector<std::string>> fronts = {
	{SINGLE, front_vowels},
	{DIPHTHONG, front_diphthongs},
	{DOUBLE, front_doubled}
};
std::unordered_map<VowelType, std::vector<std::string>> neutrals = {
	{SINGLE, neutral_vowels},
	{DIPHTHONG, neutral_diphthongs},
	{DOUBLE, neutral_doubled}
};
std::unordered_map<VowelType, std::vector<std::string>> backs = {
	{SINGLE, back_vowels},
	{DIPHTHONG, back_diphthongs},
	{DOUBLE, back_doubled}
};

std::string create_syllable(WordPos word_pos, bool firstk, bool endk, bool front_mode) {
	std::vector<std::string> initial_consonants;
	std::vector<std::string> final_consonants;
	switch(word_pos) {
		case INITIAL:
			initial_consonants = word_initial_consonants;
			final_consonants = Utils::merge(obstruents, liquids);
			break;
		case MEDIAL:
			initial_consonants = Utils::merge(obstruents, liquids);
			final_consonants = Utils::merge(obstruents, liquids);
			break;
		case FINAL:
			initial_consonants = Utils::merge(obstruents, liquids);
			final_consonants = coronals;
			break;
	}

	std::string syllable = "";

	if (firstk) {
		syllable += initial_consonants[std::rand() % initial_consonants.size()];
	}


	VowelType vowel_type;
	int random_number = std::rand() % 4;

	if (random_number >= 2) {
		vowel_type = SINGLE;
	} else if (random_number == 1) {
		vowel_type = DIPHTHONG;
	} else {
		vowel_type = DOUBLE;
	}

	std::vector<std::string> vowel_sequences;
	
	vowel_sequences = Utils::merge(vowel_sequences, neutrals[vowel_type]);

	if (front_mode) {
		vowel_sequences = Utils::merge(vowel_sequences, fronts[vowel_type]);
	} else {
		vowel_sequences = Utils::merge(vowel_sequences, backs[vowel_type]);
	}

	syllable += vowel_sequences[std::rand() % vowel_sequences.size()];

	if (endk) {
		syllable += final_consonants[std::rand() % final_consonants.size()];
	}

	return syllable;
}

std::string Names::create_name(bool uppercase_first) {
	std::string name = "";

	bool front_mode = Utils::randbool();

	name += create_syllable(INITIAL, true, Utils::randbool(), front_mode);
	for (int i = 0; i < std::rand() % 2; ++i) {
		name += create_syllable(MEDIAL, true, Utils::randbool(), front_mode);
	}
	name += create_syllable(FINAL, true, Utils::randbool(), front_mode);

	name[0] = toupper(name[0]);
	return name;
}
