#include "Family.h"

Family::Family(unsigned int n_parents, unsigned int n_children, std::string family_name) : family_name(family_name), tax_table() {
	for (unsigned int i = 0; i < n_parents; ++i) {
		std::pair<std::string, double> profession = Names::create_profession();
		this->parents.push_back(Person(Names::create_name(true), 37, Activity(profession.first, profession.second), true));
	}

	for (unsigned int i = 0; i < n_children; ++i) {
		Activity hobby = Names::create_hobby();
		this->children.push_back(Person(Names::create_name(true), Utils::random_double(0, 17.99999), hobby, false));
	}
}

double Family::get_one_time() {
	double one_time;

	for (Person& person : this->get_everyone()) {
		one_time += person.get_activity().get_one_time();
	}

	return one_time;
}

std::vector<double> benefits_list = {
	94.88,
	104.84,
	133.79,
	173.24,
	192.69
};

double Family::get_child_benefits() {
	double benefits = 0;

	size_t child = 0;

	for (Person& person : this->get_children()) {
		if (child >= benefits_list.size()) {
			benefits += benefits_list.back();
			continue;
		}
		benefits += benefits_list[child];
		child++;
	}

	return benefits;
}

double Family::get_income() {
	double income = 0;

	for (Person& person : this->get_everyone()) {
		double person_flow = person.get_activity().get_flow();
		if (person_flow < 0)
			continue;
		
		income += person_flow;
	}

	return income;
}

Religion Family::get_religion() {
	return this->religion;
}

std::string Family::get_name() {
	return this->family_name;
}

std::vector<Person> Family::get_everyone() {
	std::vector<Person> everyone = this->parents;
	everyone.insert(everyone.end(), this->children.begin(), this->children.end());
	return everyone;
}

std::vector<Person> Family::get_parents() {
	return this->parents;
}

std::vector<Person> Family::get_children() {
	return this->children;
}

void Family::set_tax_table(TaxTable tax_table) {
	this->tax_table = tax_table;
}

std::ostream& operator<<(std::ostream &out, const Family &family) {
	unsigned int name_length = family.family_name.size();
	out.write(reinterpret_cast<char*>(&name_length), sizeof(unsigned int));
	out.write(family.family_name.c_str(), name_length);

	unsigned int n_parents = family.parents.size();
	out.write(reinterpret_cast<char*>(&n_parents), sizeof(unsigned int));

	unsigned int n_children = family.children.size();
	out.write(reinterpret_cast<char*>(&n_children), sizeof(unsigned int));

	unsigned int religion = family.religion;
	out.write(reinterpret_cast<char*>(&religion), sizeof(unsigned int));

	for (unsigned int i = 0; i < n_parents; ++i) {
		out << family.parents[i];
	}

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

	unsigned int n_children;
	in.read(reinterpret_cast<char*>(&n_children), sizeof(unsigned int));

	unsigned int religion;
	in.read(reinterpret_cast<char*>(&religion), sizeof(unsigned int));
	family.religion = Religion(religion);

	for (unsigned int i = 0; i < n_parents; ++i) {
		Person parent;
		in >> parent;
		family.parents.push_back(parent);
	}

	for (unsigned int i = 0; i < n_children; ++i) {
		Person child;
		in >> child;
		family.children.push_back(child);
	}

	return in;
}