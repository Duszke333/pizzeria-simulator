#include "instant_food_exception.h"

InstantFoodException::InstantFoodException() :
    std::invalid_argument("This is a serious pizzeria, we don't serve instant food.")
{}
