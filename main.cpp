#include <boost/program_options.hpp>
#include "utils.h"
#include "names.h"
#include "family.h"

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
			outfile << Family(2, vm["generate"].as<unsigned int>());

			outfile.close();
		}
	}

	if (vm.count("input")) {
		std::ifstream infile(vm["input"].as<std::string>());

		if (infile.is_open()){
			Family family;
			infile >> family;
			
			std::cout << family.printable();
			std::cout << "\nArvioidut kuukausitulot: " << family.predict_monthly_salary() << std::endl;
			std::cout << "Arvioidut kuukausimenot: " << family.predict_monthly_cost() << std::endl;


			infile.close();
		} else {
			std::cerr << "Failed to open file " << vm["input"].as<std::string>() << std::endl;
		}
	}

	return 0;
}
