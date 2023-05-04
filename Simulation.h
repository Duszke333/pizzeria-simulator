#pragma once
#include "appetizer.cpp"
#include "client_already_awaiting_exception.cpp"
#include "client_already_in_exception.cpp"
#include "client_not_invited_exception.cpp"
#include "client.cpp"
#include "drink.cpp"
#include "food_not_found_exception.cpp"
#include "food.cpp"
#include "free_food_exception.cpp"
#include "group.cpp"
#include "instant_food_exception.cpp"
#include "invalid_group_size_exception.cpp"
#include "menu.cpp"
#include "no_food_exception.cpp"
#include "order_empty_exception.cpp"
#include "order.cpp"
#include "pizza.cpp"
#include "table_not_ready_exception.cpp"
#include "table.cpp"
#include "RandomNumber.cpp"
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

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
    // Tables in current scope
    std::vector<Table> active_tables;
    // Main Table database
    std::vector<Table> new_tables;
    Event current_event = Event::NewTable;

    //// Update seed and event - Randomizers

    void update_seed();
    void update_event();

    //// Handlers
    // General purpose, calls other handlers
    void handle_event(const Event &event);
    void handle_mod_table();
    void handle_nothing();
    void handle_new_table();
    void handle_del_table();
    void handle_kit_acc() const noexcept;

    Event new_random_event() const noexcept;
    void sleep(const unsigned short& ms) const;
    void end() const;

    //// Printers

    std::string group_at_table_str(const Table &table) const noexcept;

public:
    Simulation(const size_t& time)
        : time(time)
        {
            update_seed();
        }

    const size_t& get_time() const {
        return this->time;
    }
    void set_time(const size_t& time) {
        this->time = time;
    }
    const Event& get_curr_event() {
        return this->current_event;
    }

    const std::string get_curr_event_str() const noexcept;

    // Get the ball rollin'
    void start();
};