#pragma once
#include <list>
#include <memory>
#include <vector>
#include "food.h"
#include "pizza.h"
#include "drink.h"
#include "appetizer.h"


class Menu {
    private:
        //std::list<std::unique_ptr<Food>> foods;
        std::vector<Pizza> pizzas;
        std::vector<Drink> drinks;
        std::vector<Appetizer> appetizers;

        void remove_pizza(std::string the_name);
        void remove_drink(std::string the_name);
        void remove_appetizer(std::string the_name);
    public:
        //void add_food(std::string the_name, unsigned int the_price, unsigned short prep_time);
        void add_pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size);
        void add_drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_vol);
        void add_appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time);

        Drink random_drink(unsigned int seed) const;
        Appetizer random_appetizer(unsigned int seed) const;
        Pizza random_pizza(unsigned int seed) const;

        unsigned int calculate_total_price() const noexcept;
        //Food find_by_name(std::string the_name);
        //void remove_by_name(std::string the_name);
        friend std::ostream& operator<<(std::ostream& out, const Menu& menu);
};
