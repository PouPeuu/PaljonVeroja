#ifndef FAMILY_H
#define FAMILY_H

#include "Names.h"
#include "Person.h"
#include "TaxTable.h"

class Family {
	private:
		std::vector<Person> parents;
		std::vector<Person> children;

		std::string family_name;

		TaxTable tax_table;
	public:
		Family(unsigned int n_parents = 0, unsigned int n_children = 0, std::string family_name = "Default");

		double get_child_benefits();
		double get_one_time();
		double get_income();

		std::string get_name();

		std::vector<Person> get_everyone();
		std::vector<Person> get_parents();
		std::vector<Person> get_children();

		void set_tax_table(TaxTable tax_table);

		friend std::ostream& operator<<(std::ostream &out, const Family &family);
		friend std::istream& operator>>(std::istream &in, Family &family);
};

#endif