#include "double_work_exception.h"


DoubleWorkException::DoubleWorkException(unsigned int waiter_id, unsigned int table_id) : 
    std::logic_error("Waiter no. " + std::to_string(waiter_id) + " is already serving table " + std::to_string(table_id) + ".")
{}
