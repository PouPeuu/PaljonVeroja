#include "TaxTable.h"

TaxTable::TaxTable(std::vector<std::tuple<double, double, double>> table) : table(table) {}

TaxTable::TaxTable() : table() {}

std::tuple<bool, double, double> TaxTable::get_national_tax_rate(double income) {
    double previous = 0;

    for (std::tuple<double, double, double>& bracket : table) {
        double max_income = std::get<0>(bracket);

        if (income <= max_income || max_income == 0) {
            return std::make_tuple(previous - income > 0, std::get<1>(bracket), std::get<2>(bracket));
        }

        previous = max_income;
    }

    // die
    return std::make_tuple(false, 0, 0);
}