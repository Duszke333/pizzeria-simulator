#include "no_food_exception.h"


NoFoodException::NoFoodException(std::string foodtype) :
    std::logic_error("No foods of type: " + foodtype + " are on the menu.")
{}
