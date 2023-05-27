#include "RandomNumber.h"

std::mt19937 RandomNumber::engine = std::mt19937(RandomNumber::RandomSeed());

unsigned RandomNumber::RandomSeed() {
    return std::chrono::system_clock::now().time_since_epoch().count();
}

long RandomNumber::RandRange(long bot, long top) {
    std::uniform_int_distribution<long> range(bot, top);
    return range(engine);
}