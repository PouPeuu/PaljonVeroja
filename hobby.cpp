#include "hobby.h"

Hobby::Hobby(std::string name, double cost) : name(name), cost(cost) {}

Hobby::Hobby() : Hobby("None", 0) {}

std::string Hobby::get_name() {
	return this->name;
}

double Hobby::get_cost() {
	return this->cost;
}

std::ostream& operator<<(std::ostream &out, const Hobby &hobby) {
	size_t name_length = hobby.name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	out.write(hobby.name.c_str(), name_length);
	double cost = hobby.cost;
	out.write(reinterpret_cast<char*>(&cost), sizeof(cost));
	return out;
}

std::istream& operator>>(std::istream &in, Hobby &hobby) {
	size_t name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	hobby.name.resize(name_length);
	in.read(&hobby.name[0], name_length);
	double cost;
	in.read(reinterpret_cast<char*>(&cost), sizeof(cost));
	hobby.cost = cost;
	return in;
}