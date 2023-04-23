#include "food_not_found_exception.h"

FoodNotFoundException::FoodNotFoundException(std::string name) :
    std::invalid_argument("No food found under name " + name + ".")
{}
