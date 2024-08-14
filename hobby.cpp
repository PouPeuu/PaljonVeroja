#include "hobby.h"

Hobby::Hobby(std::string name) {
	this->name = name;
}

Hobby::Hobby() : Hobby("None") {}

std::ostream& operator<<(std::ostream &out, const Hobby &hobby) {
	size_t name_length = hobby.name.size();
	out.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
	out.write(hobby.name.c_str(), name_length);
	return out;
}

std::istream& operator>>(std::istream &in, Hobby &hobby) {
	size_t name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	hobby.name.resize(name_length);
	in.read(&hobby.name[0], name_length);
	return in;
}