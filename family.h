#ifndef FAMILY_H
#define FAMILY_H

#include "names.h"
#include "person.h"

class Family {
	private:
		std::vector<Adult> parents;
		std::vector<Child> children;

		std::string family_name;
	public:
		Family();
		Family(unsigned int n_parents, unsigned int n_children);

		std::string printable(bool include_parents = true, bool include_children = true);

		double predict_monthly_cost();
		double predict_monthly_salary();

		friend std::ostream& operator<<(std::ostream &out, const Family &family);
		friend std::istream& operator>>(std::istream &in, Family &family);
};

#endif