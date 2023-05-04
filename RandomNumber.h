#pragma once
#include <random>
#include <chrono>

class RandomNumber
{
private:
    long long value = 0LL;
public:
    // Random unsinged long long
    RandomNumber(const unsigned &seed);
    RandomNumber();
    // Random number in range
    RandomNumber(const unsigned &seed, const long long &bottom, const long long &top);
    RandomNumber(const long long &bottom, const long long &top);
    const long long &get() const noexcept;
    static unsigned RandomSeed();
};