#include "Municipality.h"

Municipality::Municipality(std::string name, double income_tax_percent, double evangelical_lutheran_tax_percent, double orthodox_tax_percent, unsigned int index)
: name(name), 
income_tax_percent(income_tax_percent), 
evangelical_lutheran_tax_percent(evangelical_lutheran_tax_percent), 
orthodox_tax_percent(orthodox_tax_percent),
index(index) {}

double Municipality::get_income_tax_percent() {
    return this->income_tax_percent;
}

double Municipality::get_evangelical_lutheran_tax_percent() {
    return this->evangelical_lutheran_tax_percent;
}

double Municipality::get_orthodox_tax_percent() {
    return this->orthodox_tax_percent;
}