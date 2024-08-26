#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "Utils.h"

class Activity {
	private:
		double flow;
		double one_time;
		std::string name;
	public:
		Activity(std::string name = "None", double flow = 0, double one_time = 0);

		double get_flow();
		double get_one_time();
		std::string get_name();

		// builder !!!
		Activity& invert();

		friend std::ostream& operator<<(std::ostream &out, const Activity &activity);
		friend std::istream& operator>>(std::istream &in, Activity &activity);
};

#endif // ACTIVITY_H