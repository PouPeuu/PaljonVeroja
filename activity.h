#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "utils.h"

class Activity {
	private:
		double flow;
		double one_time;
		std::string name;
	public:
		Activity(std::string name = "None", double flow = 0, double one_time = 0);

		double get_flow();
		double get_one_time();

		friend std::ostream& operator<<(std::ostream &out, const Profession &profession);
		friend std::istream& operator>>(std::istream &in, Profession &profession);
}

#endif // ACTIVITY_H