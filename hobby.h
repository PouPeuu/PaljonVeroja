#ifndef HOBBY_H
#define HOBBY_H

#include "utils.h"

class Hobby {
	private:
		std::string name;
	public:
		Hobby(std::string name);
		Hobby();

		std::string get_name();

		friend std::ostream& operator<<(std::ostream &out, const Hobby &hobby);
		friend std::istream& operator>>(std::istream &in, Hobby &hobby);
};

#endif