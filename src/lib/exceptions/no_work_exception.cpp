#include "no_work_exception.h"


NoWorkException::NoWorkException(unsigned int waiter_id, unsigned int table_id) : 
    std::logic_error("Waiter no. " + std::to_string(waiter_id) + " is not serving table " + std::to_string(table_id) + ".") 
{}
