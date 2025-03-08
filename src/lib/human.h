#pragma once
#include <iostream>


class Human {
    protected:
        unsigned int id;
    public:
        Human(unsigned int index);
        unsigned int get_id() const noexcept;
        void set_id(unsigned int new_id) noexcept;
        bool operator==(const Human& other) const noexcept;
        bool operator!=(const Human& other) const noexcept;
};