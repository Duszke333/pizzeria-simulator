#include <iostream>
#include "food.h"
#include "free_food_exception.h"


Food::Food(std::string the_name, unsigned int the_price) :
    name(the_name) {
    if (the_price == 0) throw FreeFoodException();
    price = the_price;
}

Food::~Food() {}

std::string Food::get_name() const noexcept {
    return name;
}

unsigned int Food::get_price() const noexcept {
    return price;
}

void Food::set_name(std::string new_name) noexcept {
    name = new_name;
}

void Food::set_price(unsigned int new_price) {
    if (new_price == 0) throw FreeFoodException();
    price = new_price;
}

std::ostream& operator<<(std::ostream& out, const Food& food) {
    out << food.name << std::endl;
    out << "Price: " << food.price << std::endl;
    return out;
}
