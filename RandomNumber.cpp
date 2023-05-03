#include "RandomNumber.h"

RandomNumber::RandomNumber(const unsigned &seed, const long long &bot, const long long &top)
{
    std::uniform_int_distribution<long long> range(bot, top);
    std::mt19937 generator(seed);
    this->value = range(generator);
}

RandomNumber::RandomNumber(const unsigned &seed)
{
    std::uniform_int_distribution<unsigned> uid;
    std::mt19937 generator(seed);
    this->value = uid(generator);
}

const long long &RandomNumber::get_value() const noexcept
{
    return this->value;
}