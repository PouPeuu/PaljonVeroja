#include "person.h"

Person::Person(std::string name, double age, Activity activity, bool parent) : name(name), age(age), activity(activity), parent(parent) {}

std::string Person::get_name() {
	return this->name;
}

double Person::get_age() {
	return this->age;
}

Activity Person::get_activity() {
	return this->activity;
}

bool Person::is_parent() {
	return this->parent;
}

std::ostream& operator<<(std::ostream &out, const Person &person) {
	unsigned int name_length = person.name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(name_length));

	out.write(person.name.c_str(), name_length);

	double age = person.age;
	out.write(reinterpret_cast<char*>(&age), sizeof(age));

	bool is_parent = person.parent;
	out.write(reinterpret_cast<char*>(&is_parent), sizeof(is_parent));

	out << person.activity;
	return out;
}

std::istream& operator>>(std::istream &in, Person &person) {
	unsigned int name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));

	person.name.resize(name_length);
	in.read(&person.name[0], name_length);

	in.read(reinterpret_cast<char*>(&person.age), sizeof(person.age));

	in.read(reinterpret_cast<char*>(&person.parent), sizeof(person.parent));

	in >> person.activity;
	return in;
}