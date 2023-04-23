#include <iostream>
#include "appetizer.h"


Appetizer::Appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time) :
    Food(the_name, the_price, prep_time)
{}

std::ostream& operator<<(std::ostream& out, const Appetizer& app) {
    out << "Appetizer: " << app.name << std::endl;
    out << "Price:     " << app.base_price / 100 << "." << app.base_price % 100 << std::endl;
    return out;
}
