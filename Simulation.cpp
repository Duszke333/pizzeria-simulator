#include "Simulation.h"

void Simulation::start() {
    for (; time != 0; --time) {
        std::cout << get_curr_event_str() << std::endl;
        update_event();
        sleep(100);
    }
    end();
}

void Simulation::end() const {
    std::cout << "Pizzeria is closing...\n";
}

const std::string Simulation::get_curr_event_str() const noexcept {
    switch (current_event) {
    case Event::ModTable:
        return "ModTable";
    case Event::NewTable:
        return "NewTable";
    case Event::DelTable:
        return "DelTable";
    case Event::KitchenAccident:
        return "KitchenAccident";
    case Event::Nothing:
        return "Nothing";
    }
    return "Nothing";
}

void Simulation::sleep(const unsigned short& ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Simulation::update_seed() {
    seed = std::chrono::system_clock::now().time_since_epoch().count();
}

void Simulation::update_event() {
    current_event = new_random_event();
    update_seed();
}

unsigned Simulation::rnum(const unsigned& bot, const unsigned& top) const noexcept {
    std::uniform_int_distribution<unsigned> range(bot, top);
    std::mt19937 generator(seed);
    return range(generator);
}

Event Simulation::new_random_event() const noexcept {
    unsigned r100(rnum(1, 100));
    if (r100 < static_cast<unsigned short>(Event::ModTable)) return Event::ModTable;
    else if (r100 < static_cast<unsigned short>(Event::NewTable)) return Event::Nothing;
    else if (r100 < static_cast<unsigned short>(Event::DelTable)) return Event::NewTable;
    else if (r100 < static_cast<unsigned short>(Event::KitchenAccident)) return Event::DelTable;
    else return Event::Nothing;
}