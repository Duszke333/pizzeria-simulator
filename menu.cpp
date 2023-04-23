#include <iostream>
#include "menu.h"
#include "food_not_found_exception.h"


void Menu::add_food(std::string the_name, unsigned int the_price, unsigned short prep_time) {
    std::unique_ptr<Food> added_food = std::make_unique<Food>(the_name, the_price, prep_time);
    foods.push_back(std::move(added_food));
}

void Menu::add_pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size) {
    std::unique_ptr<Pizza> added_pizza = std::make_unique<Pizza>(the_name, the_price, prep_time, the_size);
    foods.push_back(std::move(added_pizza));
}

void Menu::add_drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_vol) {
    std::unique_ptr<Drink> added_drink = std::make_unique<Drink>(the_name, the_price, prep_time, the_vol);
    foods.push_back(std::move(added_drink));
}

void Menu::add_appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time) {
    std::unique_ptr<Appetizer> added_appetizer = std::make_unique<Appetizer>(the_name, the_price, prep_time);
    foods.push_back(std::move(added_appetizer));
}

unsigned int Menu::calculate_total_price() const noexcept {
    unsigned int total = 0;
    for (const auto& food_ptr : foods) total += food_ptr -> get_price();
    return total;
}

Food Menu::find_by_name(std::string the_name) {
    for (const auto& food_ptr : foods) {
        if (food_ptr -> get_name() == the_name) return *food_ptr;
    }
    throw FoodNotFoundException(the_name);
}

void Menu::remove_by_name(std::string the_name) {
    auto it = foods.begin();
    while (it != foods.end()) {
        if ((*it) -> get_name() == the_name) {
            auto it_cp = it;
            ++it;
            foods.erase(it_cp);
        }
        else ++it;
    }
}

std::ostream& operator<<(std::ostream& out, const Menu& menu) {
    out << "Menu contents: " << std::endl;
    for (const auto& food_ptr : menu.foods) {
        out << "-------------------------" << std::endl;
        out << *food_ptr;
    }
    out << "-------------------------" << std::endl;
    unsigned int total = menu.calculate_total_price();
    out << "Total price: " << total / 100 << "." << total % 100 << std::endl;
    return out;
}
