#include "family.h"

Family::Family() : children(), parents(), family_name(Names::create_name(true)) {}

Family::Family(unsigned int n_parents, unsigned int n_children) : Family() {
	for (unsigned int i = 0; i < n_parents; ++i) {
		std::pair<std::string, double> profession = Names::create_profession();
		this->parents.push_back(Adult(Names::create_name(true), 37, Profession(profession.first, profession.second)));
	}

	for (unsigned int i = 0; i < n_children; ++i) {
		std::pair<std::string, double> profession = Names::create_profession();
		this->children.push_back(Child(Names::create_name(true), ((double) std::rand() / RAND_MAX) * 17.9999, Hobby(profession.first, profession.second)));
	}
}

std::string separator = "----------------\n";

std::string Family::printable(bool include_parents, bool include_children) {
	std::string result = family_name + "n Perhe:\n";
	result += "Määrä vanhempia: " + std::to_string(parents.size()) + "\n";
	result += "Määrä lapsia: " + std::to_string(children.size()) + "\n";

	if (include_parents){
		for (unsigned int i = 0; i < parents.size(); ++i) {
			Adult parent = parents[i];
			result += separator;
			result += "Vanhempi " + std::to_string(i) + "\n";
			result += "Nimi: " + parent.get_name() + " " + family_name + "\n";
			result += "Ikä: " + std::to_string(parent.get_age()) + "\n";
			result += "Työ: " + parent.profession.get_name() + "\n";
			result += "Kuukausipalkka: " + std::to_string(parent.profession.get_salary()) + "\n";
		}
	}

	if (include_children){
		for (unsigned int i = 0; i < children.size(); ++i) {
			Child child = children[i];
			result += separator;
			result += "Lapsi " + std::to_string(i) + "\n";
			result += "Nimi: " + child.get_name() + " " + family_name + "\n";
			result += "Ikä: " + std::to_string(child.get_age()) + "\n";
			result += "Harrastus: " + child.hobby.get_name() + "\n";
			result += "Harrastuksen kulut: " + std::to_string(child.hobby.get_cost()) + "\n";
		}
	}

	return result;
}

double Family::predict_monthly_cost() {
	double total_cost;

	// Average monthly food cost
	double food_cost = parents.size() * 300;
	food_cost += children.size() * 200;

	total_cost += food_cost;

	for (Child& child : children) {
		total_cost += child.hobby.get_cost();
	}

	return total_cost;
}

double Family::predict_monthly_salary() {
	double gross_salary;

	for (Adult& adult : parents) {
		gross_salary += adult.profession.get_salary();
	}

	
}

std::ostream& operator<<(std::ostream &out, const Family &family) {
	unsigned int name_length = family.family_name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(unsigned int));
	out.write(family.family_name.c_str(), name_length);

	unsigned int n_parents = family.parents.size();
	out.write(reinterpret_cast<char*>(&n_parents), sizeof(unsigned int));

	for (unsigned int i = 0; i < n_parents; ++i) {
		out << family.parents[i];
	}

	unsigned int n_children = family.children.size();
	out.write(reinterpret_cast<char*>(&n_children), sizeof(unsigned int));

	for (unsigned int i = 0; i < n_children; ++i) {
		out << family.children[i];
	}

	return out;
}

std::istream& operator>>(std::istream &in, Family &family) {
	unsigned int name_length;
	in.read(reinterpret_cast<char*>(&name_length), sizeof(unsigned int));
	family.family_name.resize(name_length);
	in.read(&family.family_name[0], name_length);

	unsigned int n_parents;
	in.read(reinterpret_cast<char*>(&n_parents), sizeof(unsigned int));

	for (unsigned int i = 0; i < n_parents; ++i) {
		Adult adult;
		in >> adult;
		family.parents.push_back(adult);
	}

	unsigned int n_children;
	in.read(reinterpret_cast<char*>(&n_children), sizeof(unsigned int));

	for (unsigned int i = 0; i < n_children; ++i) {
		Child child;
		in >> child;
		family.children.push_back(child);
	}

	return in;
}