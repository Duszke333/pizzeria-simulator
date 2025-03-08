#include "order_empty_exception.h"


OrderEmptyException::OrderEmptyException(unsigned int t_id) :
    std::logic_error("Order from table " + std::to_string(t_id) + " is empty")
{}
