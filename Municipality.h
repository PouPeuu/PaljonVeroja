#ifndef MUNICIPALITY_H
#define MUNICIPALITY_H

#include "Utils.h"

class Municipality {
    private:
        double income_tax_percent;
        double evangelical_lutheran_tax_percent;
        double orthodox_tax_percent;
    public:
        Municipality(std::string name, double income_tax_percent, double evangelical_lutheran_tax_percent, double orthodox_tax_percent, unsigned int index);
        Municipality() = default;

        double get_income_tax_percent();
        double get_evangelical_lutheran_tax_percent();
        double get_orthodox_tax_percent();

        unsigned int index;

        std::string name;
};

#endif // MUNICIPALITY_H