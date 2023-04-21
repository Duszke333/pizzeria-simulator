#include "food_already_done_exception.h"

FoodAlreadyDoneException::FoodAlreadyDoneException() :
    std::invalid_argument("Do not overcook the food.")
{}
