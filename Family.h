#ifndef FAMILY_H
#define FAMILY_H

#include "Names.h"
#include "Person.h"

class Family {
	private:
		std::vector<Person> parents;
		std::vector<Person> children;

		std::string family_name;
	public:
		Family(unsigned int n_parents = 0, unsigned int n_children = 0, std::string family_name = "Default");

		double predict_flow();
		double predict_one_time();
		std::string get_name();

		std::vector<Person> get_everyone();
		std::vector<Person> get_parents();
		std::vector<Person> get_children();

		friend std::ostream& operator<<(std::ostream &out, const Family &family);
		friend std::istream& operator>>(std::istream &in, Family &family);
};

#endif