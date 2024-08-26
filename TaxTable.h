#ifndef TAXTABLE_H
#define TAXTABLE_H

#include "Utils.h"

class TaxTable {
    private:
        std::vector<std::tuple<double, double, double>> table;
    public:
        TaxTable(std::vector<std::tuple<double, double, double>> table);
        TaxTable();

        std::tuple<bool, double, double> get_national_tax_rate(double income);
        double get_employment_pension_insurance_rate(double age);
        double get_unemployment_insurance_rate();
};

#endif // TAXTABLE_H