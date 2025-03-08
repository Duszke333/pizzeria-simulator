#pragma once
#include <stdexcept>


class FoodNotFoundException : public std::invalid_argument {
    public:
        FoodNotFoundException(std::string name);
};
