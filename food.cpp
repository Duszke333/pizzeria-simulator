#include <iostream>
#include "food.h"
#include "free_food_exception.h"
#include "instant_food_exception.h"
#include "food_already_done_exception.h"

Food::Food(std::string the_name, unsigned int the_price, unsigned short prep_time) :
    name(the_name),
    ready(false) {
    if (the_price == 0) throw FreeFoodException();
    base_price = the_price;
    if (prep_time == 0) throw InstantFoodException();
    preparation_time = prep_time;
}

Food::~Food() {}

std::string Food::get_name() const noexcept {
    return name;
}

unsigned int Food::get_price() const noexcept {
    return base_price;
}

unsigned short Food::get_remaining_time() const noexcept {
    return preparation_time;
}

bool Food::is_ready() const noexcept {
    return ready;
}

void Food::set_name(std::string new_name) noexcept {
    name = new_name;
}

void Food::set_price(unsigned int new_price) {
    if (new_price == 0) throw FreeFoodException();
    base_price = new_price;
}

void Food::set_preparation_time(unsigned short new_time) {
    if (new_time == 0) throw InstantFoodException();
    preparation_time = new_time;
}

void Food::prepare_food() {
    if (ready == true) throw FoodAlreadyDoneException();
    preparation_time--;
    if (preparation_time == 0) ready = true;
}

bool Food::operator==(const Food& other) const noexcept {
    if (this->name == other.name &&
        this->base_price == other.base_price &&
        this->preparation_time == other.preparation_time) return true;
    return false;
}

bool Food::operator!=(const Food& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Food& food) {
    out << food.name << std::endl;
    out << "Price: " << food.base_price / 100 << "." << food.base_price % 100 << std::endl;
    return out;
}
