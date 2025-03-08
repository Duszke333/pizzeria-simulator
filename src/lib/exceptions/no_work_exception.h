#pragma once
#include <iostream>
#include <stdexcept>


class NoWorkException : public std::logic_error {
    public:
        NoWorkException(unsigned int waiter_id, unsigned int table_id);
};