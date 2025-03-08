#pragma once
#include <string>


class Food {
    protected:
        unsigned int base_price;
        unsigned short preparation_time;
        bool ready;
        std::string name;
    public:
        Food(std::string the_name, unsigned int the_price, unsigned short prep_time);
        virtual ~Food();

        std::string get_name() const noexcept;
        virtual unsigned int get_price() const noexcept;
        unsigned short get_remaining_time() const noexcept;
        bool is_ready() const noexcept;

        void set_name(std::string new_name) noexcept;
        void set_price(unsigned int new_price);
        void set_preparation_time(unsigned short new_time);

        void prepare();

        bool operator==(const Food& other) const noexcept;
        bool operator!=(const Food& other) const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Food& food);
};
