#include <iostream>
#include <algorithm>
#include "menu.h"
#include "food_not_found_exception.h"
#include "no_food_exception.h"
#include "RandomNumber.h"


void Menu::add_pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size) {
    pizzas.push_back(Pizza(the_name, the_price, prep_time, the_size));
}

void Menu::add_drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_vol) {
    drinks.push_back(Drink(the_name, the_price, prep_time, the_vol));
}

void Menu::add_appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time) {
    appetizers.push_back(Appetizer(the_name, the_price, prep_time));
}

Drink Menu::random_drink() const {
    if (drinks.size() == 0) throw NoFoodException("Drink");
    unsigned long long pos = RandomNumber::RandRange(0, drinks.size());
    return drinks[pos];
}

Appetizer Menu::random_appetizer() const {
    if (appetizers.size() == 0) throw NoFoodException("Appetizer");
    unsigned long long pos = RandomNumber::RandRange(0, appetizers.size());
    return appetizers[pos];
}

Pizza Menu::random_pizza() const {
    if (pizzas.size() == 0) throw NoFoodException("Pizza");
    unsigned long long pos = RandomNumber::RandRange(0, pizzas.size());
    return pizzas[pos];
}

unsigned int Menu::calculate_total_price() const noexcept {
    unsigned int total = 0;
    for (const auto& drink : drinks) total += drink.get_price();
    for (const auto& appetizer : appetizers) total += appetizer.get_price();
    for (const auto& pizza : pizzas) total += pizza.get_price();
    return total;
}

std::ostream& operator<<(std::ostream& out, const Menu& menu) {
    out << "Menu contents: " << std::endl;
    out << "=========================" << std::endl;
    out << "Appetizers: " << std::endl;
    for (const auto& food : menu.appetizers) {
        out << "-------------------------" << std::endl;
        out << food;
    }
    out << "=========================" << std::endl;
    out << "Pizzas: " << std::endl;
    for (const auto& food : menu.pizzas) {
        out << "-------------------------" << std::endl;
        out << food;
    }
    out << "=========================" << std::endl;
    out << "Drinks: " << std::endl;
    for (const auto& food : menu.drinks) {
        out << "-------------------------" << std::endl;
        out << food;
    }
    out << "=========================" << std::endl;
    unsigned int total = menu.calculate_total_price();
    out << "Total price: " << total / 100 << "." << total % 100 << std::endl;
    return out;
}
