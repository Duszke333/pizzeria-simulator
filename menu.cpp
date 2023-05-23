#include <iostream>
#include <algorithm>
#include "menu.h"
#include "food_not_found_exception.h"
#include "no_food_exception.h"
#include "RandomNumber.h"


void Menu::remove_pizza(std::string the_name) {
    pizzas.erase(std::remove_if(pizzas.begin(), pizzas.end(), [the_name](const Pizza& pi) {
        return pi.get_name() == the_name;
    }));
}

void Menu::remove_drink(std::string the_name) {
    drinks.erase(std::remove_if(drinks.begin(), drinks.end(), [the_name](const Drink& dr) {
        return dr.get_name() == the_name;
    }));
}
void Menu::remove_appetizer(std::string the_name) {
    appetizers.erase(std::remove_if(appetizers.begin(), appetizers.end(), [the_name](const Appetizer& ap) {
        return ap.get_name() == the_name;
    }));
}

// void Menu::add_food(std::string the_name, unsigned int the_price, unsigned short prep_time) {
//     std::unique_ptr<Food> added_food = std::make_unique<Food>(the_name, the_price, prep_time);
//     foods.push_back(std::move(added_food));
// }

void Menu::add_pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size) {
    std::unique_ptr<Pizza> added_pizza = std::make_unique<Pizza>(the_name, the_price, prep_time, the_size);
    //foods.push_back(std::move(added_pizza));
    pizzas.push_back(Pizza(the_name, the_price, prep_time, the_size));
}

void Menu::add_drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_vol) {
    std::unique_ptr<Drink> added_drink = std::make_unique<Drink>(the_name, the_price, prep_time, the_vol);
    //foods.push_back(std::move(added_drink));
    drinks.push_back(Drink(the_name, the_price, prep_time, the_vol));
}

void Menu::add_appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time) {
    std::unique_ptr<Appetizer> added_appetizer = std::make_unique<Appetizer>(the_name, the_price, prep_time);
    //foods.push_back(std::move(added_appetizer));
    appetizers.push_back(Appetizer(the_name, the_price, prep_time));
}

Drink Menu::random_drink(unsigned int seed) const {
    if (drinks.size() == 0) throw NoFoodException("Drink");
    unsigned long long pos = RandomNumber(seed).get() % drinks.size();
    return drinks[pos];
}

Appetizer Menu::random_appetizer(unsigned int seed) const {
    if (appetizers.size() == 0) throw NoFoodException("Appetizer");
    unsigned long long pos = RandomNumber(seed).get() % appetizers.size();
    return appetizers[pos];
}

Pizza Menu::random_pizza(unsigned int seed) const {
    if (pizzas.size() == 0) throw NoFoodException("Pizza");
    unsigned long long pos = RandomNumber(seed).get() % pizzas.size();
    return pizzas[pos];
}

unsigned int Menu::calculate_total_price() const noexcept {
    unsigned int total = 0;
    //for (const auto& food_ptr : foods) total += food_ptr -> get_price();
    for (const auto& drink : drinks) total += drink.get_price();
    for (const auto& appetizer : appetizers) total += appetizer.get_price();
    for (const auto& pizza : pizzas) total += pizza.get_price();
    return total;
}

// Food Menu::find_by_name(std::string the_name) {
//     for (const auto& food_ptr : foods) {
//         if (food_ptr -> get_name() == the_name) return *food_ptr;
//     }
//     throw FoodNotFoundException(the_name);
// }

// void Menu::remove_by_name(std::string the_name) {
//     auto vector_eraser = foods.begin();
//     auto it = foods.begin();
//     while (it != foods.end()) {
//         if ((*it) -> get_name() == the_name) {
//             //auto it_cp = it;
//             vector_eraser = it;
//             ++it;
//             //foods.erase(it_cp);
//         }
//         else ++it;
//     }
//     if (dynamic_cast<Pizza*>((*vector_eraser).get())) {
//         remove_pizza(the_name);
//     }
//     else if (dynamic_cast<Drink*>((*vector_eraser).get())) {
//         remove_drink(the_name);
//     }
//     else if (dynamic_cast<Appetizer*>((*vector_eraser).get())) {
//         remove_appetizer(the_name);
//     }
// }

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
