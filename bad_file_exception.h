#pragma once
#include <stdexcept>


class BadFileException : public std::invalid_argument {
    public:
        BadFileException();
};
