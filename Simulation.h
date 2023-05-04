#pragma once
#include "appetizer.h"
#include "client_already_awaiting_exception.h"
#include "client_already_in_exception.h"
#include "client_not_invited_exception.h"
#include "client.h"
#include "drink.h"
#include "food_not_found_exception.h"
#include "food.h"
#include "free_food_exception.h"
#include "group.h"
#include "instant_food_exception.h"
#include "invalid_group_size_exception.h"
#include "menu.h"
#include "no_food_exception.h"
#include "order_empty_exception.h"
#include "order.h"
#include "pizza.h"
#include "table_not_ready_exception.h"
#include "table.h"
#include "RandomNumber.h"
#include <vector>
#include <string>
#include <iostream>
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
    const Menu &menu;
    unsigned seed;

    size_t client_index = 1ULL;
    size_t group_index = 1ULL;
    size_t table_index = 1ULL;

    // Tables in current scope
    std::vector<Table> active_tables;
    // Main Table database
    std::vector<Table> new_tables;
    Event current_event = Event::NewTable;

    //// Update seed and event - Randomizers

    void update_seed();
    void update_event();
    Client generate_client();
    Group generate_group(const unsigned &group_size);
    Table generate_table(const TableSize &table_size);

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
    //// Constructors

    // tables: [first] = amount of tables of [second] TableSize
    Simulation(const size_t& time, const Menu &menu, std::array<std::pair<int, TableSize>, 3> tables)
        : time(time)
        , menu(menu)
        {
            update_seed();
            for (short i = 0; i != 3; ++i)
                for (int j = 0; j != tables[i].first; ++j)
                    new_tables.push_back(generate_table(tables[i].second));
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

    size_t new_client_index() {
        return client_index++;
    }
    size_t new_group_index() {
        return group_index++;
    }
    size_t new_table_index() {
        return table_index++;
    }

    const std::string get_curr_event_str() const noexcept;

    // Get the ball rollin'
    void start();
};