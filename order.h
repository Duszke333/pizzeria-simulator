#pragma once
#include <iostream>
#include <vector>
#include "food_list.h"


class Order : public FoodList {
    private:
        bool drinks_ready_to_serve;
        bool appetizers_ready_to_serve;
        bool pizzas_ready_to_serve;
        unsigned int price;
    public:
        Order();
        bool drinks_ready() const noexcept;
        bool appetizers_ready() const noexcept;
        bool pizzas_ready() const noexcept;
        unsigned int get_price() const noexcept;
        void add_pizza(Pizza pizza);
        void add_drink(Drink drink);
        void add_appetizer(Appetizer appetizer);
        void prepare_food(unsigned int t_id);
        void clear_order();
        friend std::ostream& operator<<(std::ostream& os, const Order& order);
};
