#include "client.h"
#include "drink.h"
#include "order.h"
#include "appetizer.h"
#include "pizza.h"
#include "menu.h"
#include "table.h"
#include "food.h"
#include "RandomNumber.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

// Must be ordered in this order
// Chance of getting Event = [Event value] - [previous Event value]
// Must cap at 100 and start at 0
//
// During ModTable, waiters attend to their tables or missing customers join the group
// During Nothing, we wait for food to be prepared and/or eaten
// During NewTable, new customers flood the scene
// During DelTable, customers exit the building
// During KitchenAccident, basically nothing happens since
// the kitchen can't operate and prepare food
enum class Event {
    ModTable = 20, Nothing = 62, NewTable = 92, DelTable = 97, KitchenAccident = 100
};

class Simulation {
private:
    size_t time = 0;
    unsigned seed;
    std::vector<Table> active_tables;
    std::vector<Table> new_tables;
    Event current_event = Event::NewTable;

    void update_seed();
    void update_event();
    // Handlers

    void handle_event(const Event &event);
    void handle_mod_table();
    void handle_nothing();
    void handle_new_table();

    Event new_random_event() const noexcept;
    void sleep(const unsigned short& ms) const;
    void end() const;

    // Printers
    std::string group_at_table_str(const Table &table) const noexcept;

public:
    Simulation(const size_t& time)
        : time(time)
        {
            update_seed();
        }

    const size_t& get_time() const { return this->time; }
    void set_time(const size_t& time) { this->time = time; }
    const std::string get_curr_event_str() const noexcept;
    const Event& get_curr_event() { return this->current_event; }
    void start();
};