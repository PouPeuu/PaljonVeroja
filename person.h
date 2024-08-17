#ifndef PERSON_H
#define PERSON_H

#include "utils.h"
#include "activity.h"

class Person {
	private:
		std::string name;
		double age;
		bool parent;
		Activity activity;
	public:
		Person(std::string name = "Default", double age = 0 , Activity activity = Activity(), bool parent = false);

		std::string get_name();
		double get_age();
		bool is_parent();
		Activity get_activity();

		friend std::ostream& operator<<(std::ostream &out, const Person &person);
		friend std::istream& operator>>(std::istream &in, Person &person);
};

#endif