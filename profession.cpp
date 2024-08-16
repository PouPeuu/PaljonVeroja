#include "profession.h"

Profession::Profession(std::string name, double monthly_salary) : name(name), monthly_salary(monthly_salary) {}

Profession::Profession() : Profession("None", 0) {}

std::string Profession::get_name() {
	return this->name;
}

double Profession::get_salary() {
	return this->monthly_salary;
}

std::ostream& operator<<(std::ostream &out, const Profession &profession) {
	size_t name_length = profession.name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	out.write(profession.name.c_str(), name_length);
	double monthly_salary = profession.monthly_salary;
	out.write(reinterpret_cast<char*>(&monthly_salary), sizeof(monthly_salary));
	return out;
}

std::istream& operator>>(std::istream &in, Profession &profession) {
	size_t name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	profession.name.resize(name_length);
	in.read(&profession.name[0], name_length);
	double monthly_salary;
	in.read(reinterpret_cast<char*>(&monthly_salary), sizeof(monthly_salary));
	profession.monthly_salary = monthly_salary;
	return in;
}