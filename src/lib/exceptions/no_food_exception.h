#pragma once
#include <stdexcept>


class NoFoodException : public std::logic_error {
    public:
        NoFoodException(std::string foodtype);
};
