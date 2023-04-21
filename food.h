#pragma once
#include <string>


class Food {
    protected:
        std::string name;
        unsigned int price;
    public:
        Food(std::string the_name, unsigned int the_price);
        virtual ~Food();

        std::string get_name() const noexcept;
        virtual unsigned int get_price() const noexcept;

        void set_name(std::string new_name) noexcept;
        void set_price(unsigned int new_price);

        friend std::ostream& operator<<(std::ostream& out, const Food& food);
};
