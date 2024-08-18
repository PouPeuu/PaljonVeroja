#include <boost/program_options.hpp>
#include "utils.h"
#include "names.h"
#include "family.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
	std::srand(std::time(0));

	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("generate,g", po::value<unsigned int>(), "generate people")
		("input,i", po::value<std::string>(), "input file")
		("output,o", po::value<std::string>(), "output file")
		("summary,s", "show summary of the family")
		("list,l", "list everyone in the family");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || vm.empty()) {
		std::cout << desc << "\n";
		return 1;
	}

	std::ofstream outfile;
	Family input_family;

	if (vm.count("output")) {
		outfile.open(vm["output"].as<std::string>());
	}

	if (vm.count("input")) {
		std::ifstream infile(vm["input"].as<std::string>());
		if (infile.is_open()) {
			infile >> input_family;
		} else {
			std::cerr << "Failed to open input file!" << std::endl;
			return 1;
		}
	}

	if (vm.count("generate")) {
		Family family(2, vm["generate"].as<unsigned int>(), Names::create_name(true));
		if (outfile.is_open()){
			outfile << family;

			outfile.close();
		} else {
			std::cout << family;
		}
	}

	if (vm.count("summary")) {
		std::cout << "Summary of " << input_family.get_name() << ":" << std::endl;

	}

	if (vm.count("list")) {
		std::vector<Person> everyone = input_family.get_everyone();
		for (Person& person : everyone) {
			printf("-----------------------\n");
			printf("%s, %s:\n", person.get_name().c_str(), person.is_parent() ? "parent" : "child");
			printf("Age: %lf\n", person.get_age());
			printf("%s: %s\n", person.is_parent() ? "Job" : "Hobby", person.get_activity().get_name().c_str());
			printf("%s: %lf€\n", person.is_parent() ? "Salary" : "Monthly cost", std::fabs(person.get_activity().get_flow()));
			if (!person.is_parent())
				printf("One time cost: %lf\n", person.get_activity().get_one_time());
			std::cout << std::endl;
		}
	}

	return 0;
}
