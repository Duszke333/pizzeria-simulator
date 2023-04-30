#include "invalid_group_size_exception.h"


InvalidGroupSizeException::InvalidGroupSizeException() :
    std::invalid_argument("This group too big for this table.")
{}
