#ifndef ACTIVITY_DEFINITION_H
#define ACTIVITY_DEFINITION_H

#include "Utils.h"
#include "CSV.h"
#include "Activity.h"

class ActivityDefinition {
	private:
		std::string name;

		double min_flow;
		double min_one_time;
		double max_flow;
		double max_one_time;
	public:
		ActivityDefinition(std::string name, double min_flow, double max_flow, double min_one_time, double max_one_time);
		ActivityDefinition();

		Activity create();
};
#endif