#include "RandomNumber.h"

RandomNumber::RandomNumber(const unsigned &seed, const long long &bot, const long long &top) {
    *this = RandomNumber(RandRange(seed, bot, top));
}

RandomNumber::RandomNumber(const long long &bot, const long long &top) {
    *this = RandomNumber(RandRange(bot, top));
}

RandomNumber::RandomNumber(const unsigned &seed) {
    std::uniform_int_distribution<unsigned> uid;
    std::mt19937 generator(seed);
    this->value = uid(generator);
}

RandomNumber::RandomNumber() {
    *this = RandomNumber(RandomNumber::RandomSeed());
}

const long long &RandomNumber::get() const noexcept {
    return this->value;
}

unsigned RandomNumber::RandomSeed() {
    return std::chrono::system_clock::now().time_since_epoch().count();
}

long long RandomNumber::RandRange(const unsigned &seed, const long long &bot, const long long &top) {
    std::uniform_int_distribution<long long> range(bot, top);
    std::mt19937 generator(seed);
    return range(generator);
}

long long RandomNumber::RandRange(const long long &bot, const long long &top) {
    return RandRange(RandomSeed(), bot, top);
}