#include "order_empty_exception.h"


OrderEmptyException::OrderEmptyException() :
    std::logic_error("Order is empty")
{}
