#pragma once
#include <random>

class RandomNumber
{
private:
    long long value = 0LL;
public:
    // Random unsinged long long
    RandomNumber(const unsigned &seed);
    // Random number in range
    RandomNumber(const unsigned &seed, const long long &bottom, const long long &top);
    const long long &get_value() const noexcept;
};