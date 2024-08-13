#include "person.h"

Person::Person(std::string name, double age) {
	this->name = name;
	this->age = age;
}

Adult::Adult(std::string name, double age, Profession profession) : Person(name, age) {
	this->profession = profession;
}

Child::Child(std::string name, double age, Hobby hobby) : Person(name, age) {
	this->hobby = hobby;
}