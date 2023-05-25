#pragma once
#include <iostream>
#include "group.h"
#include "order.h"
#include "menu.h"


enum class TableSize {small = 2, standard = 4, big = 8};

enum class Status {Free = 0, WaitingForMenu, PreparingToOrder, WaitingForDrinks, WaitingForAppetizers, WaitingForPizzas, WaitingForReceipt, ReadyToPay};

class Table {
    private:
        bool ready;
        unsigned int table_id;
        unsigned int earned;
        TableSize size;
        Status status;
        Group group;
        Order order;
        const Menu &menu;
        void place_order(); // menu powinno być polem? wtedy call z interact()
    public:
        Table(unsigned int id, TableSize the_size, const Menu& the_menu);
        unsigned int get_id() const noexcept;
        unsigned int get_earnings() const noexcept;
        TableSize get_size() const noexcept;
        Status get_status() const noexcept;
        Group get_group() const noexcept;
        Order get_order() const noexcept;
        bool ready_for_action() const noexcept;
        void set_id(unsigned int new_id) noexcept;
        void set_size(TableSize the_size) noexcept;
        void set_status(Status the_status) noexcept;
        void set_group(Group the_group);
        std::vector<unsigned int> get_awaiting_ids() const noexcept;
        void bring_to_table(Client client);
        void prepare_order() noexcept;
        void update_status() noexcept;
        std::string interact();

        friend std::ostream& operator<<(std::ostream& os, const Table& table);
        bool operator==(const Table &other) const;
        void operator=(const Table &other);
};
