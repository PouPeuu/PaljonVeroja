#include "names.h"

std::vector<std::string> consonants = {"d", "f", "h", "j", "k", "l", "m", "n", "p", "r", "s", "t", "v"};
std::vector<std::string> sonorants = {"m", "n", "ng", "r", "l"};
std::vector<std::string> dentals = {"s", "t", "n", "r", "l"};

std::vector<std::string> back_vowels = {"a", "o", "u"};
std::vector<std::string> neutral_vowels = {"e", "i"};
std::vector<std::string> front_vowels = {"ä", "ö", "y"};

std::vector<std::string> back_diphthongs = {"ai", "oi", "ui", "au", "ou", "eu", "iu", "uo"};
std::vector<std::string> neutral_diphthongs = {"ei", "ie"};
std::vector<std::string> front_diphthongs = {"äi", "öi", "yi", "äy", "öy", "yö", "ey"};

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

std::string create_vowel(bool front_mode) {
	std::string vowel;
	std::vector<std::string> possible_vowels;
	VowelType vowel_type;

	int dide_nesi = std::rand() % 4;

	if (dide_nesi >= 2) {
		vowel_type = SINGLE;
	} else if (dide_nesi == 1) {
		vowel_type = DIPHTHONG;
	} else {
		vowel_type = DOUBLE;
	}

	possible_vowels = Utils::merge(possible_vowels, neutrals[vowel_type]);

	if (front_mode) {
		possible_vowels = Utils::merge(possible_vowels, fronts[vowel_type]);
	} else {
		possible_vowels = Utils::merge(possible_vowels, backs[vowel_type]);
	}

	return possible_vowels[std::rand() % possible_vowels.size()];
}

std::string create_syllable(WordPos word_pos, bool firstc, bool mids, bool endk, bool endd, bool front_mode) {
	std::string syllable = "";

	switch(word_pos) {
		case MEDIAL:
			if (firstc)
				syllable += consonants[std::rand() % consonants.size()];
			syllable += create_vowel(front_mode);
			if (mids)
				syllable += sonorants[std::rand() % sonorants.size()];
			if (endk)
				syllable += consonants[std::rand() % consonants.size()];
		case FINAL:
			if (firstc)
				syllable += consonants[std::rand() % consonants.size()];
			syllable += create_vowel(front_mode);
			if (endd)
				syllable += dentals[std::rand() % dentals.size()];
	}

	return syllable;
}

std::string Names::create_name(bool uppercase_first) {
	std::string name = "";

	bool front_mode = Utils::randbool();

	name += create_syllable(MEDIAL, true, Utils::randbool(), Utils::randbool(), Utils::randbool(), front_mode);
	for (int i = 0; i < std::rand() % 1; ++i) {
		name += create_syllable(MEDIAL, true, Utils::randbool(), Utils::randbool(), Utils::randbool(), front_mode);
	}
	name += create_syllable(FINAL, true, false, false, Utils::randbool(), front_mode);

	name[0] = toupper(name[0]);
	return name;
}
