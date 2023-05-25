#include <iostream>
#include "order.h"
#include "order_empty_exception.h"


Order::Order() :
    drinks_ready_to_serve(false),
    appetizers_ready_to_serve(false),
    pizzas_ready_to_serve(false),
    price(0) {
        // ready_to_serve[0] = false;
        // ready_to_serve[1] = false;
        // ready_to_serve[2] = false;
    }

bool Order::drinks_ready() const noexcept {
    return drinks_ready_to_serve;
}

bool Order::appetizers_ready() const noexcept {
    return appetizers_ready_to_serve;
}

bool Order::pizzas_ready() const noexcept {
    return pizzas_ready_to_serve;
}

unsigned int Order::get_price() const noexcept {
    return price;
}

void Order::add_pizza(Pizza pizza) {
    pizzas.push_back(pizza);
    price += pizza.get_price();
}

void Order::add_drink(Drink drink) {
    drinks.push_back(drink);
    price += drink.get_price();
}

void Order::add_appetizer(Appetizer appetizer) {
    appetizers.push_back(appetizer);
    price += appetizer.get_price();
}

void Order::remove_pizza(Pizza pizza) {
    for (auto it = pizzas.begin(); it != pizzas.end(); ++it) {
        if (*it == pizza) {
            pizzas.erase(it);
            price -= pizza.get_price();
            break;
        }
    }
}

void Order::remove_drink(Drink drink) {
    for (auto it = drinks.begin(); it != drinks.end(); ++it) {
        if (*it == drink) {
            drinks.erase(it);
            price -= drink.get_price();
            break;
        }
    }
}

void Order::remove_appetizer(Appetizer appetizer) {
    for (auto it = appetizers.begin(); it != appetizers.end(); ++it) {
        if (*it == appetizer) {
            appetizers.erase(it);
            price -= appetizer.get_price();
            break;
        }
    }
}

// void Order::prepare_pizzas() {
//     if (pizzas.size() == 0) throw OrderEmptyException();
//     unsigned int statuses = 0;
//     for (Pizza& pizza : pizzas) {
//         pizza.prepare();
//         if(pizza.is_ready()) statuses++;
//     }
//     if (statuses == pizzas.size()) ready_to_serve[2] = true;
// }

// void Order::prepare_drinks() {
//     if (drinks.size() == 0) throw OrderEmptyException();
//     unsigned int statuses = 0;
//     for (Drink& drink : drinks) {
//         drink.prepare();
//         if(drink.is_ready()) statuses++;
//     }
//     if (statuses == drinks.size()) ready_to_serve[0] = true;
// }

// void Order::prepare_appetizers() {
//     if (appetizers.size() == 0) throw OrderEmptyException();
//     unsigned int statuses = 0;
//     for (Appetizer& appetizer : appetizers) {
//         appetizer.prepare();
//         if(appetizer.is_ready()) statuses++;
//     }
//     if (statuses == appetizers.size()) ready_to_serve[1] = true;
// }

void Order::prepare_food() {
    if (drinks.size() == 0) throw OrderEmptyException();
    unsigned int d_statuses = 0;
    for (Drink& drink : drinks) {
        drink.prepare();
        if(drink.is_ready()) d_statuses++;
    }
    if (d_statuses == drinks.size()) drinks_ready_to_serve = true;
    
    if (appetizers.size() == 0) throw OrderEmptyException();
    unsigned int a_statuses = 0;
    for (Appetizer& appetizer : appetizers) {
        appetizer.prepare();
        if(appetizer.is_ready()) a_statuses++;
    }
    if (a_statuses == appetizers.size()) appetizers_ready_to_serve = true;

    if (pizzas.size() == 0) throw OrderEmptyException();
    unsigned int p_statuses = 0;
    for (Pizza& pizza : pizzas) {
        pizza.prepare();
        if(pizza.is_ready()) p_statuses++;
    }
    if (p_statuses == pizzas.size()) pizzas_ready_to_serve = true;
}

void Order::clear_order() {
    pizzas.clear();
    drinks.clear();
    appetizers.clear();
    price = 0;
    drinks_ready_to_serve = false;
    appetizers_ready_to_serve = false;
    pizzas_ready_to_serve = false;
    // ready_to_serve[0] = false;
    // ready_to_serve[1] = false;
    // ready_to_serve[2] = false;
}

std::ostream& operator<<(std::ostream& out, const Order& order) {
    out << "Order price: " << order.price << std::endl;
    out << "Drinks:" << std::endl;
    for (auto drink : order.drinks) {
        out << drink << std::endl;
    }
    out << std::endl << "Appetizers:" << std::endl;
    for (auto appetizer : order.appetizers) {
        out << appetizer << std::endl;
    }
    out << std::endl << "Pizzas:" << std::endl;
    for (auto pizza : order.pizzas) {
        out << pizza << std::endl;
    }
    return out;
}
