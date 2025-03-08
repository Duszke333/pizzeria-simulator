#pragma once
#include <stdexcept>


class FreeFoodException : public std::invalid_argument {
    public:
        FreeFoodException();
};
