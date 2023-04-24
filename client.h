#pragma once
#include <iostream>


class Client {
    private:
        unsigned int id;
    public:
        Client(unsigned int index);
        unsigned int get_id();
        void set_id(unsigned int new_id);
        friend std::ostream& operator<<(std::ostream& out, const Client& client);
};