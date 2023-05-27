#include "Simulation.h"

// Doesn't actually roll random Event at the start,
// MUST start at NewClients, rolls after
void Simulation::start()
{
    communicate("Seed:" + std::to_string(seed));
    size_t total_time = time;
    for (; time != 0; --time)
    {
        update_event();
        communicate("\nTurn no. " + std::to_string(total_time - time), 700);
        communicate("[" + get_curr_event_str() + "]");
        handle_event(current_event);
    }
    end();
}

void Simulation::handle_event(const Event &event)
{
    switch (event)
    {
    case Event::ModTable:
        handle_mod_table();
        break;
    case Event::NewClients:
        handle_new_clients();
        break;
    case Event::ClientsExit:
        handle_clients_exit();
        break;
    case Event::KitchenAccident:
        handle_kit_acc();
        break;
    }
}

void Simulation::handle_mod_table()
{
    for (Table &table : active_tables)
    {
        if (waiter(table).is_occupied()) {
            communicate("Waiter no. " + std::to_string(waiter(table).get_id()) +
                " cannot attend to Table no. " + std::to_string(table.get_id())
            );
            // Change the prority to this table
            auto it = std::find(active_tables.begin(), active_tables.end(), table);
            active_tables.erase(it);
            active_tables.insert(active_tables.begin(), table);
            communicate("As a result this table will be considered with higher priority!");
            continue;
        }
        else if (!table.get_group().is_complete())
        {
            communicate(group_at_table_str(table) + " is not ready yet complete...");
            // Chanced based event that some clients show up and join the table
            clients_showup(table);
        }
        else if (!table.ready_for_action())
        {
            communicate(group_at_table_str(table) + " has not received their orders yet\nPreparing...");
            table.prepare_order();
            table.update_status();
        }
        else
        {
            communicate(table.interact());
            waiter(table).occupy();
            if (table.get_status() == Status::WaitingForDrinks) {
                communicate("Their order: ");
                std::cout << table.get_order();
                logs << table.get_order();
            }

            // Erase from memory if there's need
            if (table.get_status() == Status::Free)
                next_events.push_back(Event::ClientsExit);
        }
    }

    // Unoccupy the waiters
    for (Waiter &w : waiters)
        w.unoccupy();
}

void Simulation::handle_new_clients()
{
    const Table new_table = all_tables.front();
    communicate("New Clients flood the pizzeria!");
    communicate("It's a rush!", 500);
    communicate("Their Group no. " +
        std::to_string(new_table.get_group().get_id()) +
        " has been assigned at Table no. " + std::to_string(new_table.get_id())
    );
    // Activate the table
    active_tables.push_back(new_table);
    // Assign it to a waiter
    communicate("The table has been assigned to Waiter no. "
        + std::to_string(best_waiter().get_id())
    );
    best_waiter().add_table(new_table.get_id());

    /// Disable the table from all tables
    // Regenerate the group
    all_tables[0].set_group(generate_group(all_tables[0].get_size()));
    // Push back the first element of the all_tables vector
    all_tables.push_back(all_tables[0]);
    all_tables.erase(all_tables.begin());
}

void Simulation::handle_clients_exit()
{
    for (const Table &table : active_tables)
    {
        if (table.get_status() == Status::Free)
        {
            communicate("Group no. " + std::to_string(table.get_group().get_id()) +
                " decided against dining in proi pizzeria and left leaving Table no. " +
                std::to_string(table.get_id()) + " empty..."
            );
            auto it = std::find(active_tables.begin(), active_tables.end(), table);
            active_tables.erase(it);
            break;
        }
    }
}

void Simulation::handle_kit_acc() noexcept
{
    // CANNOT WRITE TO FILE WHEN CONST
    communicate("Ohh no!!\nThere's been an accident in the kitchen!!\nCooks can't prepare the Food!!");
}

void Simulation::end() noexcept
{
    // CANNOT WRITE TO FILE WHEN CONST
    communicate("Pizzeria is closing...");
}

const std::string Simulation::get_curr_event_str() const noexcept
{
    switch (current_event)
    {
    case Event::ModTable:
        return "ModTable";
    case Event::NewClients:
        return "NewClients";
    case Event::ClientsExit:
        return "ClientsExit";
    case Event::KitchenAccident:
        return "KitchenAccident";
    }
    return "ModTable";
}

void Simulation::sleep(unsigned short ms) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void Simulation::update_seed()
{
    seed = RandomNumber::RandomSeed();
}

void Simulation::update_event()
{
    if (next_events.size() > 0)
    {
        current_event = *(next_events.end() - 1);
        event_history.push_back(current_event);
        next_events.clear();
    }
    else if (active_tables.empty())
        current_event = Event::NewClients;
    else if (active_tables.size() == all_tables.size())
        current_event = Event::ModTable;
    else current_event = rand_event();
}

bool comp_waiters(const Waiter &first, const Waiter &second) {
    return first.get_table_count() < second.get_table_count();
}

Waiter& Simulation::best_waiter() {
    return *std::min_element(waiters.begin(), waiters.end(), comp_waiters);
}

Waiter& Simulation::waiter(const Table &table) {
    for (Waiter &w : waiters)
        if (w.has_table(table.get_id()))
            return w;

    return best_waiter();
}

Waiter Simulation::generate_waiter()
{
    return Waiter(new_staff_index());
}

Client Simulation::generate_client()
{
    return Client(new_client_index());
}

long Simulation::clients_showup(Table &table) {
    long iters = RandomNumber::RandRange(0, table.get_awaiting_ids().size());
    if (iters == 1)
        communicate("\nYou can see a client on the horizon!");
    else if (iters > 1)
        communicate("\nYou can see multiple clients on the horizon!!");

    for (long i = 0; i != iters; ++i)
    {
        Client brought_client(table.get_awaiting_ids().front());
        table.bring_to_table(brought_client);

        communicate("Client no. " +
            std::to_string(brought_client.get_id()) +
            " has joined the group no. " +
            std::to_string(table.get_group().get_id())
        );

        table.update_status();
        if (table.get_group().is_complete())
            communicate("The group is now ready for action!\n");
    }
    return iters;
}

Group Simulation::generate_group(const TableSize &table_size)
{
    Group temp_group = Group(new_group_index());
    unsigned size = static_cast<int>(table_size);
    unsigned group_size = RandomNumber::RandRange(size / 2, size);
    unsigned missing_persons = 0;

    if (group_size > 1)
        missing_persons = RandomNumber::RandRange(1, group_size - 1);

    while (temp_group.get_group_size() < group_size - missing_persons)
        temp_group.add_client(generate_client());

    for (unsigned i = 0; i != missing_persons; ++i)
        temp_group.add_awaiting(new_client_index());

    return temp_group;
}

Table Simulation::generate_table(const TableSize &size)
{
    Table temp_table = Table(new_table_index(), size, menu);
    temp_table.set_group(generate_group(size));

    return temp_table;
}

bool operator<=(long long num, const Event &event)
{
    return num <= static_cast<long long>(event);
}

Event Simulation::rand_event() const noexcept
{
    long long random_num = RandomNumber::RandRange(1, 100);
    if (random_num <= Event::ModTable)
        return Event::ModTable;
    else if (random_num <= Event::NewClients)
        return Event::NewClients;
    else if (random_num <= Event::ClientsExit)
        return Event::ClientsExit;
    else
        return Event::KitchenAccident;
}

std::string Simulation::group_at_table_str(const Table &table) const noexcept
{
    return "Table no. " + std::to_string(table.get_id()) + ": " +
        "The group no. " + std::to_string(table.get_group().get_id());
}

void Simulation::communicate(std::string message, unsigned short time) noexcept
{
    std::cout << message << std::endl;
    logs << message;
    sleep(time);
}
