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
	Family family;

	if (vm.count("output")) {
		outfile.open(vm["output"].as<std::string>());
	}

	if (vm.count("input")) {
		std::ifstream infile(vm["input"].as<std::string>());
		if (infile.is_open()) {
			infile >> family;
		} else {
			std::cerr << "Failed to open input file!" << std::endl;
			return 1;
		}
	}

	if (vm.count("generate")) {
		Family family(2, vm["generate"].as<unsigned int>());
		if (outfile.is_open()){
			outfile << family;

			outfile.close();
		} else {
			std::cout << family;
		}
	}

	if (vm.count("summary")) {
		std::cout << "Summary of " <<  << std::endl;
	}

	return 0;
}
