#pragma once
#include "food.h"


enum class Size {S = 0, M, L, XL};

class Pizza : public Food {
    private:
        Size size;
    public:
        Pizza(std::string the_name, unsigned int the_price, unsigned short prep_time, Size the_size);

        unsigned int get_price() const noexcept override;

        Size get_size() const noexcept;
        void set_size(Size new_size) noexcept;

        bool operator==(const Pizza& other) const noexcept;
        bool operator!=(const Pizza& other) const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Pizza& pizza);
};
