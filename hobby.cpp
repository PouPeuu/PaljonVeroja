#include "hobby.h"

Hobby::Hobby(std::string name) {
	this->name = name;
}

Hobby::Hobby() : Hobby("None") {}