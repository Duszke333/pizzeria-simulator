#pragma once
#include <iostream>


class Client {
    private:
        unsigned int id;
    public:
        Client(unsigned int index);
        unsigned int get_id() const noexcept;
        void set_id(unsigned int new_id) noexcept;
        bool operator==(const Client& other) const noexcept;
        bool operator!=(const Client& other) const noexcept;
        friend std::ostream& operator<<(std::ostream& out, const Client& client);
};