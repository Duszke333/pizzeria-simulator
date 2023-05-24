#include "Simulation.h"

// Doesn't actually roll random Event at the start,
// MUST start at NewTable, rolls after
void Simulation::start() {
    communicate("Seed:" + std::to_string(seed) + "\n");
    size_t total_time = time;
    for (; time != 0; --time) {
        update_event();
        //
        communicate("\n\nTurn no. " + std::to_string(total_time - time) + "\n", 500);
        communicate("[" + get_curr_event_str() + "]\n");
        //
        handle_event(current_event);
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
    case Event::KitchenAccident:
        handle_kit_acc();
        break;
    }
}

void Simulation::handle_mod_table() {
    for (Table &table : active_tables) {
        if (!table.get_group().is_complete()) {
            //
            communicate(
                group_at_table_str(table)
                + " is not ready yet complete...\nBringing awaiting client no."
                + std::to_string(table.get_awaiting_ids().front()) + "\n"
            );
            //
            Client brought_client(table.get_awaiting_ids().front());
            table.bring_to_table(brought_client);
            communicate(brought_client.get_id() +
                " has joined their group no. " + table.get_group().get_id()
            );
            table.update_status();
            if (table.ready_for_action())
                communicate("The group is now ready for action!\n");
        }
        if (!table.ready_for_action()) {
            //
            communicate(
                group_at_table_str(table)
                + " has not received their orders yet\nPreparing...\n"
            );
            //
            table.prepare_order();
            table.update_status();
        } else {
            //
            communicate(table.interact(seed) + "\n");
            // Erase from memory if there's need
            if (table.get_status() == Status::Free)
                handle_del_table();
        }
    }
}

void Simulation::handle_nothing() {
    for (Table &table : active_tables) {
        if (!table.get_group().is_complete()) {
            Client brought_client = Client(table.get_awaiting_ids()[0]);
            table.bring_to_table(brought_client);
            communicate(brought_client.get_id() +
                " has joined their group no. " + table.get_group().get_id()
            );
        } else
        switch (table.get_status()) {
        case Status::Free:
            communicate(group_at_table_str(table) +
                " is waiting to be seated"
            );
            break;
        case Status::WaitingForMenu:
            communicate(group_at_table_str(table) +
                " is waiting for their menus"
            );
            break;
        case Status::PreparingToOrder:
            communicate(group_at_table_str(table) +
                " is still deciding on what to get..."
            );
            break;
        case Status::ReadyToPay:
            communicate(group_at_table_str(table) +
                " is ready to pay and waiting for their waiter"
            );
            break;
        default:
            communicate(group_at_table_str(table) +
                " is waiting for their orders\n"
                "\nThe kitchen is vigorously preparing orders..."
            );
            table.prepare_order();
            if (table.get_order().ready_to_serve[0]) {
                communicate("\nDrinks are ready to be served!");
                next_events.push_back(Event::ModTable);
            } else if (table.get_order().ready_to_serve[1]) {
                communicate("\nAppetizers are ready to be served!");
                next_events.push_back(Event::ModTable);
            } else if (table.get_order().ready_to_serve[2]) {
                communicate("\nPizzas are ready to be served!");
                next_events.push_back(Event::ModTable);
            }
            break;
        }
    }
}

void Simulation::handle_new_table() {
    const Table new_table = all_tables.front();
    //
    communicate("\nNew Clients flood the pizzeria!");
    communicate("\nIt's a rush!", 500);
    communicate(
        "\nTheir Group no. " + std::to_string(new_table.get_group().get_id())
        + " has been assigned at Table no. " + std::to_string(new_table.get_id()) + "\n"
    );
    //
    active_tables.push_back(new_table);

    // Push back the first element of the all_tables vector
    all_tables.push_back(new_table);
    all_tables.erase(all_tables.begin());
}

void Simulation::handle_del_table() {
    for (const Table &table : active_tables) {
        if (table.get_status() == Status::Free) {
            if (table.ready_for_action()) {
                //
                logs << table;
                std::cout << table;
                communicate("\nDecided against dining in proi pizzeria and left...\n");
                //
            }
            auto it = std::find(active_tables.begin(), active_tables.end(), table);
            active_tables.erase(it);
            break;
        }
    }
}

void Simulation::handle_kit_acc() noexcept {
    // CANNOT WRITE TO FILE WHEN CONST
    //
    communicate("Ohh no!!\nThere's been an accident in the kitchen!!\nCooks can't prepare the Food!!\n");
    //
}

void Simulation::end() noexcept {
    // CANNOT WRITE TO FILE WHEN CONST
    communicate("Pizzeria is closing...\n");
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

void Simulation::sleep(unsigned short ms) const {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Simulation::update_seed() {
    seed = RandomNumber::RandomSeed();
}

void Simulation::update_event() {
    if (next_events.size() > 0) {
        current_event = *(next_events.end() - 1);
        event_history.push_back(current_event);
        next_events.clear();
        return;
    }

    Event new_event = rand_event();
    double new_event_count = std::count(event_history.begin(), event_history.end(), new_event);
    double new_event_ratio = new_event_count / event_history.size();

    if (new_event_ratio < 0.4) {
        current_event = new_event;
        event_history.push_back(current_event);
        update_seed();
    } else update_event();
}

Client Simulation::generate_client() {
    return Client(new_client_index());
}

Group Simulation::generate_group(const unsigned &size) {
    Group temp_group = Group(new_group_index());
    auto missing_persons = RandomNumber::RandRange(1, size - 1);
    while (temp_group.get_group_size() < size - missing_persons)
        temp_group.add_client(generate_client());

    for (int i = 0; i != missing_persons; ++i) {
        temp_group.add_awaiting(new_client_index());
    }

    return temp_group;
}

Table Simulation::generate_table(const TableSize &size) {
    Table temp_table = Table(new_table_index(), size, menu);
    temp_table.set_group(generate_group(static_cast<unsigned>(size)));

    return temp_table;
}

bool operator<=(const long long &num, const Event &event) {
    return num <= static_cast<long long>(event);
}

Event Simulation::rand_event() const noexcept {
    long long random_num = RandomNumber::RandRange(1, 100);
    if (random_num <= Event::ModTable) return Event::ModTable;
    else if (random_num <= Event::Nothing) return Event::Nothing;
    else if (random_num <= Event::NewTable) return Event::NewTable;
    else if (random_num <= Event::DelTable) return Event::DelTable;
    else return Event::KitchenAccident;
}

std::string Simulation::group_at_table_str(const Table &table) const noexcept {
    return "\nThe group no." + std::to_string(table.get_group().get_id())
        + " at Table no." + std::to_string(table.get_id());
}


void Simulation::communicate(std::string message, unsigned short time) noexcept {
    std::cout << message;
    logs << message;
    sleep(time);
}
