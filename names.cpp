#include "names.h"

std::string Names::create_name(bool uppercase_first) {
	std::string name = "";
	for (int i = 0; i < std::rand() % 5 + 2; ++i) {
		name += Utils::random_choice(std::vector<std::string>{"rölli", "pölli", "mölli", "völli", "gölli", "jölli", "jälli", "pälli", "lälli", "lylli", "möntti", "löntti", "läntti", "lyntti", "mäntti", "könkäre"});
	}

	if (uppercase_first)
		name[0] = toupper(name[0]);
	return name;
}

std::string Names::create_profession() {
	std::string profession = "";

	std::vector<std::string> skill = {"ekspertti", "professionaalinen", "kamala", "epäilyttävä", "luotettava", "hyvätahtoinen", "pyhä", "epäpyhä"};
	std::vector<std::string> a = {"kenkien", "orpojen", "kalojen", "röllien", "puhelimien", "köntysten", "huumeiden"};
	std::vector<std::string> b = {"kaivuri", "kalastaja", "mätysteliä", "köntysteliä", "addikti", "CEO", "rapistelia", "rönklääjä", "häpisteliä", "taikuri", "valvoja", "kokeilija", "ahmija"};

	profession += Utils::random_choice(skill);
	profession += " ";
	profession += Utils::random_choice(a);
	profession += " ";
	profession += Utils::random_choice(b);

	return profession;
}