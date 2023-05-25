#pragma once
#include <iostream>
#include <vector>
#include "pizza.h"
#include "drink.h"
#include "appetizer.h"


class Order {
    private:
        bool drinks_ready_to_serve;
        bool appetizers_ready_to_serve;
        bool pizzas_ready_to_serve;
        unsigned int price;
        std::vector<Pizza> pizzas;
        std::vector<Drink> drinks;
        std::vector<Appetizer> appetizers;
    public:
        Order();
        bool drinks_ready() const noexcept;
        bool appetizers_ready() const noexcept;
        bool pizzas_ready() const noexcept;
        unsigned int get_price() const noexcept;
        void add_pizza(Pizza pizza);
        void add_drink(Drink drink);
        void add_appetizer(Appetizer appetizer);
        void prepare_food();
        void clear_order();
        friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
