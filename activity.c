#include "activity.h"

Activity::Activity(std::string name, double flow, double one_time) : name(name), flow(flow), one_time(one_time) {}

std::ostream& operator<<(std::ostream &out, const Activity &activity) {
	size_t name_length = activity.name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	out.write(activity.name.c_str(), name_length);

	out.write(reinterpret_cast<char*>(&activity.flow), sizeof(activity.flow));
	out.write(reinterpret_cast<char*>(&activity.one_time), sizeof(activity.one_time));
	return out;
}

std::istream& operator>>(std::istream &in, Activity &activity) {
	size_t name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
	activity.name.resize(name_length);
	in.read(&activity.name[0], name_length);

	in.read(reinterpret_cast<char*>(&activity.flow), sizeof(activity.flow));
	in.read(reinterpret_cast<char*>(&activity.one_time), sizeof(activity.one_time));
	return in;
}