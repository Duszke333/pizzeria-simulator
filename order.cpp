#include <iostream>
#include "order.h"
#include "order_empty_exception.h"


Order::Order() :
    drinks_ready_to_serve(false),
    appetizers_ready_to_serve(false),
    pizzas_ready_to_serve(false),
    price(0) 
{}

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
