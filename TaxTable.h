#ifndef TAXTABLE_H
#define TAXTABLE_H

#include "Utils.h"

class TaxTable {
    private:
        std::vector<std::tuple<double, double, double>> table;
    public:
        TaxTable(std::vector<std::tuple<double, double, double>> table);
        TaxTable();

        std::tuple<bool, double, double> get_tax_rate(double income);
};

#endif // TAXTABLE_H