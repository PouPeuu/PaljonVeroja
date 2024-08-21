#include "HobbyDefinition.h"

HobbyDefinition::HobbyDefinition(std::string name, double min_flow, double max_flow, double min_one_time, double max_one_time)
: name(name), min_flow(min_flow), max_flow(max_flow), min_one_time(min_one_time), max_one_time(max_one_time) {}

HobbyDefinition::HobbyDefinition()
: HobbyDefinition("", 0, 0, 0, 0) {}

Activity HobbyDefinition::create() {
    return Activity(name, -Utils::random_double(min_flow, max_flow), -Utils::random_double(min_one_time, max_one_time));
}