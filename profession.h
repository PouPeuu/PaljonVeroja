#ifndef PROFESSION_H
#define PROFESSION_H

#include "utils.h"

class Profession {
	private:
		std::string name;
	public:
		Profession(std::string name);
		Profession();

		std::string get_name();

		friend std::ostream& operator<<(std::ostream &out, const Profession &profession);
		friend std::istream& operator>>(std::istream &in, Profession &profession);
};

#endif