#include <boost/program_options.hpp>
#include "Utils.h"
#include "Names.h"
#include "Family.h"
#include "CSV.h"
#include "TaxTable.h"

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
		("list,l", "list everyone in the family")
		("hobbies,H", po::value<std::string>(), "hobbies file")
		("jobs,j", po::value<std::string>(), "jobs file")
		("municipalities,m", po::value<std::string>(), "municipalities file")
		("taxtable,t", po::value<std::string>(), "tax table file");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	
	std::ifstream config_file("config.cfg");
	po::store(po::parse_config_file(config_file, desc), vm);

	po::notify(vm);

	if (vm.count("help") || vm.empty()) {
		std::cout << desc << "\n";
		return 1;
	}

	if (vm.count("hobbies")) {
		std::vector<std::vector<std::string>> hobbies = CSV::load_csv(vm["hobbies"].as<std::string>());

		for (std::vector<std::string>& row : hobbies) {
			ActivityDefinition hobby(row[0], std::stod(row[1]), std::stod(row[2]), std::stod(row[3]), std::stod(row[4]));
			Names::hobbies.push_back(hobby);
		}
	}

	if (vm.count("jobs")) {
		std::vector<std::vector<std::string>> jobs = CSV::load_csv(vm["jobs"].as<std::string>());

		for (std::vector<std::string>& row : jobs) {
			ActivityDefinition job(row[0], std::stod(row[1]), std::stod(row[2]), 0, 0);
			Names::jobs.push_back(job);
		}
	}

	if (vm.count("municipalities")) {
		std::vector<std::vector<std::string>> municipalities_csv = CSV::load_csv(vm["municipalities"].as<std::string>());

		for (unsigned int i = 0; i < municipalities_csv.size(); ++i) {
			std::vector<std::string>& row = municipalities_csv[i];
			Municipality municipality(row[0], std::stod(row[1]), std::stod(row[2]), std::stod(row[3]), i);
			Names::municipalities.push_back(municipality);
		}
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

	if (vm.count("taxtable")) {
		std::vector<std::vector<std::string>> tax_table_csv = CSV::load_csv(vm["taxtable"].as<std::string>());

		std::vector<std::tuple<double, double, double>> tax_table;

		for (std::vector<std::string>& row : tax_table_csv) {
			if (row[0] == "inf") {
				tax_table.push_back(std::make_tuple(0, std::stod(row[1]), std::stod(row[2])));
				continue;
			}

			tax_table.push_back(std::make_tuple(std::stod(row[0]), std::stod(row[1]), std::stod(row[2])));
		}

		input_family.set_tax_table(TaxTable(tax_table));
	}

	if (vm.count("generate")) {
		if (Names::hobbies.empty()) {
			std::cerr << "No hobbies!\n";
			return 1;
		}

		if (Names::jobs.empty()) {
			std::cerr << "No jobs!\n";
			return 1;
		}

		Family family(2, vm["generate"].as<unsigned int>(), Names::create_name(), Utils::random_choice(Names::municipalities), Religion(std::rand()%3));

		if (outfile.is_open()){
			outfile << family;

			outfile.close();
		} else {
			std::cout << family;
		}
	}

	if (vm.count("summary")) {
		std::vector<Person> parents = input_family.get_parents();
		std::vector<Person> children = input_family.get_children();

		TaxTable tax_table = input_family.get_tax_table();
		double income = input_family.get_income();

		Religion religion = input_family.get_religion();
		std::string religion_string = religion == NONE ? "None" : religion == EVANGELICAL_LUTHERAN ? "Evangelical Lutheran" : "Orthodox";

		std::tuple<bool, double, double> national_tax_rate = tax_table.get_national_tax_rate(income); 
		double municipality_tax_rate = input_family.get_municipality().get_income_tax_percent();
		double orthodox_tax_rate = input_family.get_municipality().get_orthodox_tax_percent();
		double evangelical_lutheran_tax_rate = input_family.get_municipality().get_evangelical_lutheran_tax_percent();

		printf("Summary of %s:\n", input_family.get_name().c_str());
		printf("Municipality: %s\n", input_family.get_municipality().name.c_str());
		printf("Religion: %s\n", religion_string.c_str());
		printf("Parents: %d\n", parents.size());
		printf("Children: %d\n", children.size());
		printf("Gross Income: %lf€\n", input_family.get_income());

		double national_tax_deduction = income * std::get<2>(national_tax_rate);
		printf("National Tax: %lf%, %lf€\n", std::get<2>(national_tax_rate) * 100, national_tax_deduction);

		double municipality_tax_deduction = income * municipality_tax_rate;
		printf("Municipality Tax: %lf%, %lf€\n", municipality_tax_rate * 100, municipality_tax_deduction);

		double religion_tax_deduction = 0;
		if (religion == ORTHODOX) {
			religion_tax_deduction = income * orthodox_tax_rate;
			printf("Orthodox Tax: %lf%, %lf€\n", orthodox_tax_rate * 100, religion_tax_deduction);
		} else if (religion == EVANGELICAL_LUTHERAN) {
			religion_tax_deduction = income * evangelical_lutheran_tax_rate;
			printf("Evangelical Lutheran Tax: %lf%, %lf€\n", evangelical_lutheran_tax_rate * 100, religion_tax_deduction);
		}
		//printf("Employment Pension Insurance: %lf%, %lf€\n", tax_table.get_employment_pension_insurance_rate());
		printf("Net Income: %lf€\n", income - national_tax_deduction - municipality_tax_deduction - religion_tax_deduction);
		printf("Child Benefits: %lf€\n", input_family.get_child_benefits());
		printf("One Time Costs: %lf€\n", input_family.get_one_time());
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
