#pragma once
#include <stdexcept>


class InvalidGroupSizeException : public std::invalid_argument {
    public:
        InvalidGroupSizeException();
};