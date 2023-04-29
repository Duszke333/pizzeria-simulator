#include <iostream>
#include "order.h"
#include "order_empty_exception.h"


Order::Order() :
    price(0) {
        ready_to_serve[0] = false;
        ready_to_serve[1] = false;
        ready_to_serve[2] = false;
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

void Order::prepare_pizzas() {
    if (pizzas.size() == 0) throw OrderEmptyException();
    unsigned int statuses = 0;
    for (Pizza& pizza : pizzas) {
        pizza.prepare();
        if(pizza.is_ready()) statuses++;
    }
    if (statuses == pizzas.size()) ready_to_serve[2] = true;
}

void Order::prepare_drinks() {
    if (drinks.size() == 0) throw OrderEmptyException();
    unsigned int statuses = 0;
    for (Drink& drink : drinks) {
        drink.prepare();
        if(drink.is_ready()) statuses++;
    }
    if (statuses == drinks.size()) ready_to_serve[0] = true;
}

void Order::prepare_appetizers() {
    if (appetizers.size() == 0) throw OrderEmptyException();
    unsigned int statuses = 0;
    for (Appetizer& appetizer : appetizers) {
        appetizer.prepare();
        if(appetizer.is_ready()) statuses++;
    }
    if (statuses == appetizers.size()) ready_to_serve[1] = true;
}

void Order::clear_order() {
    pizzas.clear();
    drinks.clear();
    appetizers.clear();
    price = 0;
    ready_to_serve[0] = false;
    ready_to_serve[1] = false;
    ready_to_serve[2] = false;
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
