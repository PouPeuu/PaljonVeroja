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

		std::tuple<bool, double, double> national_tax_rate = tax_table.get_national_tax_rate(income*12); 
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
		printf("Income After Taxes: %lf€\n", income - national_tax_deduction - municipality_tax_deduction - religion_tax_deduction);
		printf("Child Benefits: %lf€\n", input_family.get_child_benefits());
		printf("One Time Hobby Costs: %lf€\n", -input_family.get_one_time());
		
		double house_area = 90;

		double area_per_child = 10;

		house_area += area_per_child * input_family.get_amount_of_children();

		double price_per_square_meter = 1951;

		double housing_cost = house_area * price_per_square_meter;

		printf("House Cost: %lf€\n", housing_cost);

		double food_cost_per_parent = 400;
		double food_cost_per_child = 300;

		double total_food_cost = food_cost_per_parent * input_family.get_amount_of_parents() + food_cost_per_child * input_family.get_amount_of_children();

		printf("Food Cost: %lf€\n", total_food_cost);

		double monthly_transportation_cost = 50 * input_family.get_amount_of_parents();

		for (Person& child : input_family.get_children()) {
			monthly_transportation_cost += child.get_age() <= 7 ? 0 : 30;
		}

		printf("Transporation Cost: %lf€\n", monthly_transportation_cost);

		double water_usage_liters = 7000 * input_family.get_amount_of_people();
		double water_cost_per_liter = 0.00186;
		double water_cost = water_usage_liters * water_cost_per_liter;

		printf("Water Cost: %lf€\n", water_cost);

		double electricity_usage_kilowatt_hours = 500 * input_family.get_amount_of_people(); // pulled this out of my ass
		double electricity_cost_per_kilowatt_hour = 0.203;
		double electricity_cost = electricity_usage_kilowatt_hours * electricity_cost_per_kilowatt_hour;

		printf("Electricity Cost: %lf€\n", electricity_cost);

		double employment_pension_insurance_rate = tax_table.get_employment_pension_insurance_rate(37); // hardcoded because I'm lazy
		double unemployment_insurance_rate = tax_table.get_unemployment_insurance_rate();

		double employment_pension_insurance_deduction = income * employment_pension_insurance_rate;
		double unemployment_insurance_deduction = income * unemployment_insurance_rate;

		double monthly_money_left_so_far = income 
		- national_tax_deduction 
		- municipality_tax_deduction 
		- religion_tax_deduction 
		- employment_pension_insurance_deduction 
		- unemployment_insurance_deduction
		- monthly_transportation_cost
		- water_cost
		- electricity_cost;

		double other_monthly_costs = Utils::random_double(0, monthly_money_left_so_far);

		printf("Other Costs: %lf€\n", other_monthly_costs);

		printf("Net Income: %lf€\n", monthly_money_left_so_far - other_monthly_costs);
	}

	if (vm.count("list")) {
		std::vector<Person> everyone = input_family.get_everyone();
		for (Person& person : everyone) {
			printf("-----------------------\n");
			printf("%s, %s:\n", (person.get_name() + " " + input_family.get_name()).c_str(), person.is_parent() ? "parent" : "child");
			printf("Age: %lf\n", person.get_age());
			printf("%s: %s\n", person.is_parent() ? "Job" : "Hobby", person.get_activity().get_name().c_str());
			printf("%s: %lf€\n", person.is_parent() ? "Salary" : "Monthly cost", std::fabs(person.get_activity().get_flow()));
			if (!person.is_parent()) {
				printf("One time cost: %lf\n", person.get_activity().get_one_time());
				continue;
			}

			double income = person.get_activity().get_flow();

			if (income < 0) 
				continue;

			TaxTable tax_table = input_family.get_tax_table();
			Municipality municipality = input_family.get_municipality();
			Religion religion = input_family.get_religion();

			double municipality_tax_rate = municipality.get_income_tax_percent();
			double religion_tax_rate = 
			religion == EVANGELICAL_LUTHERAN ? municipality.get_evangelical_lutheran_tax_percent() : 
			religion == ORTHODOX ? municipality.get_orthodox_tax_percent() : 
			0;
			
			std::tuple<bool, double, double> tax_row = tax_table.get_national_tax_rate(income*12);
			double employment_pension_insurance_rate = tax_table.get_employment_pension_insurance_rate(person.get_age());
			double unemployment_insurance_rate = tax_table.get_unemployment_insurance_rate();

			double municipality_tax_deduction = income * municipality_tax_rate;
			double religion_tax_deduction = income * religion_tax_rate;
			double national_tax_deduction = income * std::get<2>(tax_row);
			if (std::get<0>(tax_row))
				national_tax_deduction += std::get<1>(tax_row);
			double employment_pension_insurance_deduction = income * employment_pension_insurance_rate;
			double unemployment_insurance_deduction = income * unemployment_insurance_rate;

			printf("Municipality Tax: %lf%, %lf€\n", municipality_tax_rate * 100, municipality_tax_deduction);
			printf("Religion Tax: %lf%, %lf€\n", religion_tax_rate * 100, religion_tax_deduction);
			printf("National Tax: %lf%, thing %lf€, %lf€\n", std::get<2>(tax_row) * 100, std::get<0>(tax_row), national_tax_deduction);
			printf("Employment Pension Insurance: %lf%, %lf€\n", employment_pension_insurance_rate * 100, employment_pension_insurance_deduction);
			printf("Unemplyment Insurance: %lf%, %lf€\n", unemployment_insurance_rate * 100, unemployment_insurance_deduction);

			double total_deductions = 
			  municipality_tax_deduction 
			+ religion_tax_deduction 
			+ national_tax_deduction 
			+ employment_pension_insurance_deduction 
			+ unemployment_insurance_deduction;

			printf("Total After Deductions: %lf€ - %lf€ = %lf€\n", income, total_deductions, income - total_deductions);


			std::cout << std::endl;
		}
	}

	return 0;
}
