#pragma once
#include <stdexcept>


class MissingDataException : public std::invalid_argument {
    public:
        MissingDataException();
};
