#ifndef PROFESSION_H
#define PROFESSION_H

#include "utils.h"

class Profession {
	private:
		std::string name;
		double monthly_salary;
	public:
		Profession(std::string name, double monthly_salary);
		Profession();

		std::string get_name();

		double get_salary();

		friend std::ostream& operator<<(std::ostream &out, const Profession &profession);
		friend std::istream& operator>>(std::istream &in, Profession &profession);
};

#endif