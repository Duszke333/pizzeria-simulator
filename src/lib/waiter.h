#pragma once
#include <iostream>
#include <vector>
#include "human.h"


class Waiter : public Human {
    private:
        bool occupied;
        std::vector<unsigned int> assigned_tables;
    public:
        Waiter(unsigned int index);

        bool is_occupied() const noexcept;
        void occupy() noexcept;
        void unoccupy() noexcept;

        void add_table(unsigned int table_id);
        void remove_table(unsigned int table_id);
        bool has_table(unsigned int table_id) const noexcept;
        unsigned int get_table_count() const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Waiter& waiter);
};
