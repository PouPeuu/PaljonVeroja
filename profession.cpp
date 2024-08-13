#include "profession.h"

Profession::Profession(std::string name) {
	this->name = name;
}

Profession::Profession() : Profession("None") {}