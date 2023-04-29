#pragma once
#include <iostream>
#include <vector>
#include "pizza.h"
#include "drink.h"
#include "appetizer.h"


class Order {
    private:
        unsigned int price;
        std::vector<Pizza> pizzas;
        std::vector<Drink> drinks;
        std::vector<Appetizer> appetizers;
    public:
        bool ready_to_serve[3];
        Order();
        unsigned int get_price() const noexcept;
        void add_pizza(Pizza pizza);
        void add_drink(Drink drink);
        void add_appetizer(Appetizer appetizer);
        void remove_pizza(Pizza pizza);
        void remove_drink(Drink drink);
        void remove_appetizer(Appetizer appetizer);
        void prepare_pizzas();
        void prepare_drinks();
        void prepare_appetizers();
        void clear_order();
        friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
