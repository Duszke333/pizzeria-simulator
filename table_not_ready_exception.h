#pragma once
#include <stdexcept>


class TableNotReadyException : public std::logic_error {
    public:
        TableNotReadyException();
};