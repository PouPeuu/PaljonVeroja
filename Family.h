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

		double predict_flow(bool do_taxes = true);
		double predict_salary(bool do_taxes = true);
		double predict_child_benefits();
		double predict_one_time();
		std::string get_name();

		std::vector<Person> get_everyone();
		std::vector<Person> get_parents();
		std::vector<Person> get_children();

		void set_tax_table(TaxTable tax_table);

		friend std::ostream& operator<<(std::ostream &out, const Family &family);
		friend std::istream& operator>>(std::istream &in, Family &family);
};

#endif