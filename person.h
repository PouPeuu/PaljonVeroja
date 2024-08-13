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
};

class Adult : public Person {
	private:
		Profession profession;
	public:
		Adult(std::string name, double age, Profession profession);
};

class Child : public Person {
	private:
		Hobby hobby;
	public:
		Child(std::string name, double age, Hobby hobby);
};

#endif