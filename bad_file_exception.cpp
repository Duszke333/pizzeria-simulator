#include "bad_file_exception.h"


BadFileException::BadFileException() :
    std::invalid_argument("Could not open file.")
{}
