#ifndef HOBBY_DEFINITION_H
#define HOBBY_DEFINITION_H

#include "Utils.h"
#include "CSV.h"
#include "Activity.h"

class HobbyDefinition {
	private:
		std::string name;

		double min_flow;
		double min_one_time;
		double max_flow;
		double max_one_time;
	public:
		HobbyDefinition(std::string name, double min_flow, double max_flow, double min_one_time, double max_one_time);
		HobbyDefinition();

		Activity create();
};
#endif