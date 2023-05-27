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
#include "waiter.h"
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <algorithm>
#include <utility>
#include <array>
#include <fstream>
#include <chrono>

// Must be ordered in this order
// Chance of getting Event = [Event value] - [previous Event value]
// Must cap at 100 and start at 0
//
// During ModTable, waiters attend to their tables or missing customers join the group
// During Nothing, we wait for food to be prepared and/or eaten
// During NewClients, new customers flood the scene
// During ClientsExit, customers exit the building
// During KitchenAccident, basically nothing happens since
// the kitchen can't operate and prepare food
enum class Event {
    ModTable = 55, NewClients = 95, ClientsExit = 98, KitchenAccident = 100
//  55%            40%              3%                2%
};

class Simulation {
private:
    size_t time = 0;
    const Menu &menu;
    unsigned seed;

    size_t client_index = 1ULL;
    size_t group_index = 1ULL;
    size_t table_index = 1ULL;
    size_t staff_index = 1ULL;

    std::ofstream logs;

    // Tables in current scope
    std::vector<Table> active_tables;
    // Main Table database
    std::vector<Table> all_tables;
    // Add random amount of client to a table, returns amount of clients added
    long clients_showup(Table &table);

    // Waiters
    std::vector<Waiter> waiters;
    // Get a waiter with the least amount of tables
    Waiter& best_waiter();
    // Get that table waiter
    Waiter& waiter(const Table &table);

    // To influence event randomizing
    std::vector<Event> event_history;
    std::vector<Event> next_events = {Event::NewClients};


    // Starting event
    Event current_event;

    //// Update seed and event - Randomizers

    void update_seed();
    void update_event();
    Waiter generate_waiter();
    Client generate_client();
    Group generate_group(const TableSize &table_size);
    Table generate_table(const TableSize &table_size);

    //// Handlers
    // General purpose, calls other handlers
    void handle_event(const Event &event);
    void handle_mod_table();
    void handle_new_clients();
    void handle_clients_exit();
    void handle_kit_acc() noexcept;

    void sleep(unsigned short ms) const;
    void end() noexcept;

    //// Printers

    std::string group_at_table_str(const Table &table) const noexcept;

    void communicate(std::string message, unsigned short time = 1500) noexcept;

public:
    //// Constructors

    // tables: [first] = amount of tables of [second] TableSize
    Simulation(const size_t& time, const Menu &menu, std::array<std::pair<int, TableSize>, 3> tables, short waiters)
        : time(time)
        , menu(menu)
        {
            update_seed();
            for (short i = 0; i != 3; ++i)
                for (int j = 0; j != tables[i].first; ++j)
                    all_tables.push_back(generate_table(tables[i].second));

            for (short i = 0; i != waiters; ++i)
                this->waiters.push_back(generate_waiter());

            const auto now = std::chrono::system_clock::now();
            const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
            std::string file_name = std::ctime(&t_c);
            logs.open("./logs/" + file_name + ".txt");
        }

    ~Simulation() {
        logs.close();
    }

    Event rand_event() const noexcept;

    const size_t& get_time() const {
        return this->time;
    }
    void set_time(const size_t& time) {
        this->time = time;
    }
    const Event& get_curr_event() {
        return this->current_event;
    }

    size_t new_staff_index() {
        return staff_index++;
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