#include "person.h"

// Person

Person::Person(std::string name, double age) : name(name), age(age) {}

std::string Person::get_name() {
	return this->name;
}

double Person::get_age() {
	return this->age;
}

std::ostream& operator<<(std::ostream &out, const Person &person) {
	unsigned int name_length = person.name.size();
	out.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
	out.write(person.name.c_str(), name_length);

	out.write(reinterpret_cast<const char*>(&person.age), sizeof(person.age));
	return out;
}

std::istream& operator>>(std::istream &in, Person &person) {
	unsigned int name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	person.name.resize(name_length);
	in.read(&person.name[0], name_length);

	in.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));
	return in;
}

// Adult

Adult::Adult(std::string name, double age, Profession profession) : Person(name, age), profession(profession) {}
Adult::Adult() : Adult("", 0, Profession()) {}

std::ostream& operator<<(std::ostream &out, const Adult &adult) {
	out << static_cast<const Person&>(adult);
	out << adult.profession;
	return out;
}

std::istream& operator>>(std::istream &in, Adult &adult) {
	in >> static_cast<Person&>(adult);
	in >> adult.profession;
	return in;
}

//Child

Child::Child(std::string name, double age, Hobby hobby) : Person(name, age), hobby(hobby) {}
Child::Child() : Child("", 0, Hobby()) {}

std::ostream& operator<<(std::ostream &out, const Child &child) {
	out << static_cast<const Person&>(child);
	out << child.hobby;
	return out;
}

std::istream& operator>>(std::istream &in, Child &child) {
	in >> static_cast<Person&>(child);
	in >> child.hobby;
	return in;
}