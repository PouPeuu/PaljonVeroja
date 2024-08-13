#include <boost/program_options.hpp>
#include "utils.h"
#include "names.h"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
	std::srand(std::time(0));

	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("generate,g", po::value<unsigned int>(), "generate people");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help") || vm.empty()) {
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("generate")) {
		for (unsigned int i = 0; i < vm["generate"].as<unsigned int>(); ++i) {
			printf("%s\n", Names::create_name(true).c_str());
		}
	}

	return 0;
}
