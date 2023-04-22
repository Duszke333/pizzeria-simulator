#include <iostream>
#include "drink.h"

Drink::Drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_volume) :
    Food(the_name, the_price, prep_time),
    vol(the_volume)
{}

unsigned int Drink::get_price() const noexcept {
    switch (vol) {
        case Volume::ml500:
            return 1.2 * base_price;
        case Volume::l1:
            return 1.3 * base_price;
        default:
            return base_price;
    }
}

Volume Drink::get_volume() const noexcept {
    return vol;
}

void Drink::set_volume(Volume new_volume) noexcept {
    vol = new_volume;
}

std::string volumes[3] = {"300 ml", " 500 ml", "1 l"};

std::ostream& operator<<(std::ostream& out, const Drink& drink) {
    out << "Drink:  " << drink.name << std::endl;
    out << "Volume: " << volumes[static_cast<int>(drink.vol)] << std::endl;
    out << "Price:  " << drink.get_price() / 100 << "." << drink.get_price() % 100 << std::endl;
    return out;
}