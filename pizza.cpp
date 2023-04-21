#include <iostream>
#include "pizza.h"


Pizza::Pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size) :
    Food(the_name, the_price, prep_time),
    size(the_size)
{}

unsigned int Pizza::get_price() const noexcept {
    switch (size) {
        case Size::M:
            return 1.1 * base_price;
        case Size::L:
            return 1.2 * base_price;
        case Size::XL:
            return 1.3 * base_price;
        default:
            return base_price;
    };
}

Size Pizza::get_size() const noexcept {
    return size;
}

void Pizza::set_size(Size new_size) noexcept {
    size = new_size;
}

std::string pizza_sizes[4] = {"S", "M", "L", "XL"};

std::ostream& operator<<(std::ostream& out, const Pizza pizza) {
    out << "Pizza: " << pizza.name << std::endl;
    out << "Size:  " << pizza_sizes[static_cast<int>(pizza.size)] << std::endl;
    out << "Price: " << pizza.get_price() / 100 << "." << pizza.get_price() % 100 << std::endl;
    return out;
}
