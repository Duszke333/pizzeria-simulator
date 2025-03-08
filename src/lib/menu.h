#pragma once
#include <list>
#include <memory>
#include <vector>
#include "food_list.h"


class Menu : public FoodList {
    public:
        Menu() = default;
        void add_pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size);
        void add_drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_vol);
        void add_appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time);

        Drink random_drink() const;
        Appetizer random_appetizer() const;
        Pizza random_pizza() const;

        unsigned int calculate_total_price() const noexcept;
        friend std::ostream& operator<<(std::ostream& out, const Menu& menu);
};
