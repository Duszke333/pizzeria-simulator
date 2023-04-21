#pragma once
#include <stdexcept>


class InstantFoodException : public std::invalid_argument {
    public:
        InstantFoodException();
};
