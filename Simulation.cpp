#include "Simulation.h"

// Doesn't actually roll random Event at the start,
// MUST start at NewTable, rolls after
void Simulation::start() {
    for (; time != 0; --time) {
        //
        std::cout << "Rolling random Event...\n";
        //
        sleep(200);
        //
        std::cout << "It's " << get_curr_event_str() << "!!\n";
        handle_event(current_event);
        update_event();
    }
    end();
}

void Simulation::handle_event(const Event &event) {
    switch (event) {
    case Event::ModTable:
        handle_mod_table();
        break;
    case Event::Nothing:
        handle_nothing();
        break;
    case Event::NewTable:
        handle_new_table();
        break;
    case Event::DelTable:
        handle_del_table();
        break;
    }
}

void Simulation::handle_mod_table() {
    for (Table &table : active_tables) {
        if (!table.get_group().is_complete()) {
            //
            std::cout << group_at_table_str(table)
                << "is not ready yet complete...\nBringing awaiting client no."
                << table.get_awaiting_ids().front() << std::endl;
                sleep(100);
            //
            Client awaiting_c(table.get_awaiting_ids().front());
            table.bring_to_table(awaiting_c);
            table.update_status();
        }
        if (!table.ready_for_action()) {
            //
            std::cout << group_at_table_str(table)
                << "has not received their orders yet\nPreparing...\n";
                sleep(100);
            //
            table.prepare_order();
            table.update_status();
        } else {
            std::cout << table.interact(seed);
            // Erase from memory if there's need
            if (table.get_status() == Status::Free)
                handle_del_table();
        }
    }
}

void Simulation::handle_nothing() {
    for (Table &table : active_tables) {
        //
        std::cout << "Preparing orders...\n";
        sleep(300);
        //
        table.prepare_order();
    }
}

void Simulation::handle_new_table() {
    const Table new_table = new_tables.front();
    //
    std::cout << "New Clients flood the pizzeria!\nIt's a rush!\n";
    sleep(100);
    std::cout << "Their Group no. " << new_table.get_group().get_id()
        << "has been assigned at Table no. " << new_table.get_id()
        << std::endl;
    //
    active_tables.push_back(new_table);
    new_tables.erase(new_tables.begin());
}

void Simulation::handle_del_table() {
    for (const Table &table : active_tables) {
        if (table.get_status() == Status::Free) {
            if (table.ready_for_action()) {
                //
                std::cout << table
                    << "\nDecided against dining in proi pizzeria and left...\n";
                //
            }
            auto it = std::find(active_tables.begin(), active_tables.end(), table);
            active_tables.erase(it);
            break;
        }
    }
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

Event Simulation::new_random_event() const noexcept {
    RandomNumber R100(seed, 1, 100);
    long long r100 = R100.get_value();
    if (r100 <= static_cast<unsigned short>(Event::ModTable)) return Event::ModTable;
    else if (r100 <= static_cast<unsigned short>(Event::NewTable)) return Event::Nothing;
    else if (r100 <= static_cast<unsigned short>(Event::DelTable)) return Event::NewTable;
    else if (r100 <= static_cast<unsigned short>(Event::KitchenAccident)) return Event::DelTable;
    else return Event::Nothing;
}

std::string Simulation::group_at_table_str(const Table &table) const noexcept {
    return "The group no." + std::to_string(table.get_group().get_id())
        + "at Table no." + std::to_string(table.get_id());
}