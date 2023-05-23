#pragma once
#include <iostream>
#include <stdexcept>


class DoubleWorkException : public std::logic_error {
    public:
        DoubleWorkException(unsigned int waiter_id, unsigned int table_id);
};