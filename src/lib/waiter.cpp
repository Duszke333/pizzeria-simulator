#include "waiter.h"
#include "double_work_exception.h"
#include "no_work_exception.h"


Waiter::Waiter(unsigned int index) : 
    Human(index),
    occupied(false)
{}

bool Waiter::is_occupied() const noexcept {
    return occupied;
}

void Waiter::occupy() noexcept {
    occupied = true;
}

void Waiter::unoccupy() noexcept {
    occupied = false;
}

void Waiter::add_table(unsigned int table_id) {
    if(has_table(table_id)) throw DoubleWorkException(id, table_id);
    assigned_tables.push_back(table_id);
}

void Waiter::remove_table(unsigned int table_id) {
    auto it = assigned_tables.begin();
    while (it != assigned_tables.end()) {
        if (*it == table_id) {
            assigned_tables.erase(it);
            return;
        }
        ++it;
    }
    throw NoWorkException(id, table_id);
}

bool Waiter::has_table(unsigned int table_id) const noexcept {
    for (unsigned int t_id : assigned_tables) {
        if (t_id == table_id) {
            return true;
        }
    }
    return false;
}

unsigned int Waiter::get_table_count() const noexcept {
    return assigned_tables.size();
}

std::ostream& operator<<(std::ostream& out, const Waiter& waiter) {
    out << "Waiter no. " << waiter.id;
    return out;
}
