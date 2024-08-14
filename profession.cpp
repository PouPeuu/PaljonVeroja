#include "profession.h"

Profession::Profession(std::string name) : name(name) {}

Profession::Profession() : Profession("None") {}

std::string Profession::get_name() {
	return this->name;
}

std::ostream& operator<<(std::ostream &out, const Profession &profession) {
	size_t name_length = profession.name.size();
	out.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
	out.write(profession.name.c_str(), name_length);
	return out;
}

std::istream& operator>>(std::istream &in, Profession &profession) {
	size_t name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	profession.name.resize(name_length);
	in.read(&profession.name[0], name_length);
	return in;
}