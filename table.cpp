#include <iostream>
#include "table.h"
#include "table_not_ready_exception.h"
#include "invalid_group_size_exception.h"
#include "RandomNumber.h"

void Table::place_order()
{
    for (unsigned i = 0; i < group.get_group_size(); i++)
    {
        order.add_drink(menu.random_drink());
        order.add_appetizer(menu.random_appetizer());
        order.add_pizza(menu.random_pizza());
    }
}

Table::Table(unsigned int id, TableSize the_size, const Menu &the_menu) : ready(true),
                                                                          table_id(id),
                                                                          earned(0),
                                                                          size(the_size),
                                                                          status(Status::Free),
                                                                          menu(the_menu)
{
}

unsigned int Table::get_id() const noexcept
{
    return table_id;
}

unsigned int Table::get_earnings() const noexcept
{
    return earned;
}

TableSize Table::get_size() const noexcept
{
    return size;
}

Status Table::get_status() const noexcept
{
    return status;
}

Group Table::get_group() const noexcept
{
    return group;
}

Order Table::get_order() const noexcept
{
    return order;
}

bool Table::ready_for_action() const noexcept
{
    return ready;
}

void Table::set_id(unsigned int new_id) noexcept
{
    table_id = new_id;
}

void Table::set_size(TableSize the_size) noexcept
{
    size = the_size;
}

void Table::set_status(Status the_status) noexcept
{
    status = the_status;
}

void Table::set_group(Group the_group)
{
    if (the_group.get_group_size() > static_cast<unsigned int>(size))
        throw InvalidGroupSizeException();
    group = the_group;
}

std::vector<unsigned int> Table::get_awaiting_ids() const noexcept
{
    return group.get_awaiting_ids();
}

void Table::bring_to_table(Client client)
{
    group.join(client);
}

void Table::prepare_order() noexcept
{
    order.prepare_food(table_id);
}

void Table::update_status() noexcept
{
    switch (status)
    {
    case Status::PreparingToOrder:
        ready = (group.is_complete() ? true : false);
        break;
    case Status::WaitingForDrinks:
        if (order.drinks_ready())
            ready = true;
        break;
    case Status::WaitingForAppetizers:
        if (order.appetizers_ready())
            ready = true;
        break;
    case Status::WaitingForPizzas:
        if (order.pizzas_ready())
            ready = true;
        break;
    default:
        return;
    }
}

std::string Table::interact()
{
    if (!ready)
        throw TableNotReadyException();
    std::string output = "Table no. " + std::to_string(table_id) + ": ";
    switch (status)
    {
    case Status::Free:
        output += "The group no. " + std::to_string(group.get_id()) + " is waiting for menus.";
        status = Status::WaitingForMenu;
        break;
    case Status::WaitingForMenu:
        output += "The group no. " + std::to_string(group.get_id()) + " got the menus and will soon be ready to order.";
        status = Status::PreparingToOrder;
        ready = (group.is_complete() ? true : false);
        break;
    case Status::PreparingToOrder:
        place_order();
        output += "The group no. " + std::to_string(group.get_id()) + " ordered and is waiting for drinks.";
        status = Status::WaitingForDrinks;
        ready = false;
        break;
    case Status::WaitingForDrinks:
        output += "The group no. " + std::to_string(group.get_id()) + " received their drinks and is waiting for appetizers.";
        status = Status::WaitingForAppetizers;
        ready = false;
        break;
    case Status::WaitingForAppetizers:
        output += "The group no. " + std::to_string(group.get_id()) + " received their appetizers and is waiting for pizzas.";
        status = Status::WaitingForPizzas;
        ready = false;
        break;
    case Status::WaitingForPizzas:
        output += "The group no. " + std::to_string(group.get_id()) + " received their pizzas and is waiting for receipt.";
        status = Status::WaitingForReceipt;
        break;
    case Status::WaitingForReceipt:
        output += "The group no. " + std::to_string(group.get_id()) + " received their receipt and is ready to pay.";
        status = Status::ReadyToPay;
        break;
    case Status::ReadyToPay:
        earned += order.get_price();
        output += "The group no. " + std::to_string(group.get_id()) + " paid and left the restaurant.";
        status = Status::Free;
        group = Group();
        order.clear_order();
        return output;
    }
    return output;
}

std::string statuses[8] = {"Free", "Waiting for menu", "Ready to order", "Waiting for drinks", "Waiting for appetizers", "Waiting for pizzas", "Waiting for receipt", "Ready to pay"};

std::ostream &operator<<(std::ostream &out, const Table &table)
{
    out << "Table no. " << table.table_id << "." << std::endl;
    out << "Size: " << static_cast<int>(table.size) << "." << std::endl;
    if (table.status == Status::Free)
    {
        out << "Status: " << statuses[static_cast<int>(table.status)] << "." << std::endl;
    }
    else
    {
        out << "Group no. " << table.get_group().get_id() << "." << std::endl;
        out << "Status: " << statuses[static_cast<int>(table.status)] << "." << std::endl;
    }
    return out;
}

bool Table::operator==(const Table &other) const
{
    return this->table_id == other.table_id;
}

void Table::operator=(const Table &other)
{
    this->table_id = other.table_id;
    this->ready = other.ready;
    this->size = other.size;
    this->group = other.group;
    this->order = other.order;
    this->earned = other.earned;
    this->status = other.status;
}