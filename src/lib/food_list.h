#pragma once
#include <vector>
#include "pizza.h"
#include "drink.h"
#include "appetizer.h"



class FoodList {
    protected:
        std::vector<Pizza> pizzas;
        std::vector<Drink> drinks;
        std::vector<Appetizer> appetizers;
    public:
        FoodList() = default;
        virtual ~FoodList() = default;
};
