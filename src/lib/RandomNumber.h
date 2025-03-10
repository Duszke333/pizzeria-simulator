#pragma once
#include <random>
#include <chrono>

class RandomNumber
{
private:
    static std::mt19937 engine;
public:
    // Constructor
    RandomNumber() = default;

    // Current time
    static unsigned RandomSeed();

    // Inclusive at top and bottom
    static long RandRange(long bottom, long top);
};