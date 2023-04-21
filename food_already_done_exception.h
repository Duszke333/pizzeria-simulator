#pragma once
#include <stdexcept>


class FoodAlreadyDoneException : public std::invalid_argument {
    public:
        FoodAlreadyDoneException();
};
