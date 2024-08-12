#include "utils.h"
#include "names.h"

int main(int argc, char *argv[]) {
	std::srand(std::time(0));

	uint amount = std::stoi(argv[1]);
	for(uint i=0;i<amount;++i) {
		std::cout << Names::create_name() << " " << Names::create_name() << std::endl;
	}
	return 0;
}
