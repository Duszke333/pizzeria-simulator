#include "missing_data_exception.h"


MissingDataException::MissingDataException() :
    std::invalid_argument("File data missing key information.")
{}
