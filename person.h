#ifndef PERSON_H
#define PERSON_H

#include "utils.h"
#include "hobby.h"
#include "profession.h"

class Person {
	private:
		std::string name;
		double age;
	public:
		Person(std::string name, double age);

		std::string get_name();
		double get_age();

		friend std::ostream& operator<<(std::ostream &out, const Person &person);
		friend std::istream& operator>>(std::istream &in, Person &person);
};

class Adult : public Person {
	public:
		Profession profession;
		Adult(std::string name, double age, Profession profession);

		friend std::ostream& operator<<(std::ostream &out, const Adult &adult);
		friend std::istream& operator>>(std::istream &in, Adult &adult);
};

class Child : public Person {
	public:
		Hobby hobby;
		Child(std::string name, double age, Hobby hobby);

		friend std::ostream& operator<<(std::ostream &out, const Child &child);
		friend std::istream& operator>>(std::istream &in, Child &child);
};

#endif