#ifndef PROFESSION_H
#define PROFESSION_H

#include "utils.h"

class Profession {
	private:
		std::string name;
	public:
		Profession(std::string name);
		Profession();

		friend std::ostream& operator<<(std::ostream &out, const Profession &profession);
		friend std::istream& operator>>(std::istream &in, Profession &profession);
};

#endif