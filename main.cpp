#include <boost/program_options.hpp>
#include "utils.h"
#include "names.h"
#include "person.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
	std::srand(std::time(0));

	// Adult parent1(Names::create_name(true), 25, Profession("Biljonääri"));
	// Adult parent2(Names::create_name(true), 25, Profession("Röllien toimitusjohtaja"));

	// Child child1(Names::create_name(true), 16, Hobby("Muurahaiskasan tökkiminen"));

	// std::ofstream outfile("blurg");
	// if (outfile.is_open()) {
	// 	outfile << parent1;
	// 	outfile << parent2;
	// 	outfile << child1;
	// 	outfile.close();
	// }

	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("generate,g", po::value<unsigned int>(), "generate people")
		("input,i", po::value<std::string>(), "input file");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || vm.empty()) {
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("generate")) {
		std::ofstream outfile("family");
		if (outfile.is_open()){
			std::string surname = Names::create_name(true);
			Adult parent1(Names::create_name(true), 37, Profession(Names::create_profession()));
			Adult parent2(Names::create_name(true), 37, Profession(Names::create_profession()));

			outfile << parent1 << parent2;
			for (unsigned int i = 0; i < vm["generate"].as<unsigned int>(); ++i) {
				Child child(Names::create_name(true), ((double) std::rand() / RAND_MAX) * 17.0, Hobby(Names::create_profession()));
				outfile << child;
			}

			outfile.close();
		}
	}

	if (vm.count("input")) {
		std::vector<Child> children;

		std::ifstream infile(vm["input"].as<std::string>());
		Adult parent1("", 0, Profession(""));
		Adult parent2("", 0, Profession(""));

		infile >> parent1;
		infile >> parent2;

		printf("------------------\n");
		printf("Vanhempi 1:\nNimi: %s\nIkä: %lf\nTyö: %s\n", parent1.get_name().c_str(), parent1.get_age(), parent1.profession.get_name().c_str());
		printf("------------------\n");
		printf("Vanhempi 2:\nNimi: %s\nIkä: %lf\nTyö: %s\n", parent2.get_name().c_str(), parent2.get_age(), parent2.profession.get_name().c_str());

		
	}

	return 0;
}
