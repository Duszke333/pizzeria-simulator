#include "table_not_ready_exception.h"


TableNotReadyException::TableNotReadyException() :
    std::logic_error("Table is not ready to interact.")
{}
