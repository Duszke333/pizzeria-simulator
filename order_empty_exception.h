#pragma once
#include <stdexcept>


class OrderEmptyException : public std::logic_error {
    public:
        OrderEmptyException(unsigned int t_id);
};
