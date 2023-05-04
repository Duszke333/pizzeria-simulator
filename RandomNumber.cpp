#include "RandomNumber.h"

RandomNumber::RandomNumber(const unsigned &seed, const long long &bot, const long long &top) {
    std::uniform_int_distribution<long long> range(bot, top);
    std::mt19937 generator(seed);
    this->value = range(generator);
}

RandomNumber::RandomNumber(const long long &bot, const long long &top) {
    *this = RandomNumber(RandomNumber::RandomSeed(), bot, top);
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