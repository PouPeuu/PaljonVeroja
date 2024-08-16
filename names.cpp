#include "names.h"

std::string Names::create_name(bool uppercase_first) {
	bool front = Utils::random_bool();

	std::string name = "";
	for (int i = 0; i < std::rand() % 5 + 2; ++i) {
		if (front) {
			name += Utils::random_choice(std::vector<std::string>{"rolli", "polli", "molli", "volli", "golli", "jolli", "jalli", "lalli", "lulli", "montti", "lontti", "lantti", "lyntti", "mantti", "konkare", "kontti"});
		} else {
			name += Utils::random_choice(std::vector<std::string>{"rölli", "pölli", "mölli", "völli", "gölli", "jölli", "jälli", "pälli", "lälli", "lylli", "möntti", "löntti", "läntti", "lyntti", "mäntti", "könkäre", "köntti"});
		}
	}

	if (uppercase_first)
		name[0] = toupper(name[0]);
	return name;
}

std::pair<std::string, double> Names::create_profession() {
	std::string profession = "";

	std::vector<std::pair<std::string, double>> skills = {
		std::pair<std::string, double>("ekspertti", 100),
		std::pair<std::string, double>("professionaalinen", 200),
		std::pair<std::string, double>("kamala", 10),
		std::pair<std::string, double>("epäilyttävä", 0),
		std::pair<std::string, double>("luotettava", 50),
		std::pair<std::string, double>("hyvätahtoinen", 15),
		std::pair<std::string, double>("pyhä", 500),
		std::pair<std::string, double>("epäpyhä", 0),
		std::pair<std::string, double>("urhea", 250),
		std::pair<std::string, double>("omituinen", 20),
		std::pair<std::string, double>("mystinen", 30),
		std::pair<std::string, double>("legendaarinen", 750),
		std::pair<std::string, double>("vihattu", 5),
		std::pair<std::string, double>("normaali", 50),
		std::pair<std::string, double>("hirmuinen", 2)
	};

	std::vector<std::pair<std::string, double>> as = {
		std::pair<std::string, double>("kenkien", 10),
		std::pair<std::string, double>("orpojen", 10),
		std::pair<std::string, double>("kalojen", 20),
		std::pair<std::string, double>("röllien", 15),
		std::pair<std::string, double>("puhelimien", 100),
		std::pair<std::string, double>("köntysten", 50),
		std::pair<std::string, double>("huumeiden", 5000),
		std::pair<std::string, double>("mutavellin", 5),
		std::pair<std::string, double>("kuran", 7),
		std::pair<std::string, double>("verojen", 3500),
		std::pair<std::string, double>("rahan", 500),
		std::pair<std::string, double>("ympäristön", 250),
		std::pair<std::string, double>("ruuan", 100),
		std::pair<std::string, double>("örkki-ukkelin", 25),
		std::pair<std::string, double>("raudan", 60),
		std::pair<std::string, double>("IKEAn pöytien", 45)
	};

	std::vector<std::pair<std::string, double>> bs = {
		std::pair<std::string, double>("kaivuri", 125),
		std::pair<std::string, double>("kalastaja", 75),
		std::pair<std::string, double>("mätysteliä", 10),
		std::pair<std::string, double>("köntysteliä", 2),
		std::pair<std::string, double>("addikti", 1250),
		std::pair<std::string, double>("toimitusjohtaja", 1000),
		std::pair<std::string, double>("rapistelia", 15),
		std::pair<std::string, double>("rönklääjä", 17),
		std::pair<std::string, double>("lutkuttaja", 67),
		std::pair<std::string, double>("häpisteliä", 16),
		std::pair<std::string, double>("taikuri", 250),
		std::pair<std::string, double>("valvoja", 275),
		std::pair<std::string, double>("kokeilija", 225),
		std::pair<std::string, double>("ahmija", 505),
		std::pair<std::string, double>("sulattaja", 85),
		std::pair<std::string, double>("röpöstelijä", -500),
		std::pair<std::string, double>("kokkaaja", 160)
	};

	// skill, a, b

	std::pair<std::string, double> skill = skills[std::rand() % skills.size()];
	std::pair<std::string, double> a = as[std::rand() % as.size()];
	std::pair<std::string, double> b = bs[std::rand() % bs.size()];

	profession += skill.first;
	profession += " ";
	profession += a.first;
	profession += " ";
	profession += b.first;

	double cost = skill.second + a.second + b.second;

	return std::pair<std::string, double>(profession, cost);
}