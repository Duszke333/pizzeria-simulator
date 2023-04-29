#pragma once
#include "food.h"


class Appetizer : public Food {
    public:
        Appetizer(std::string the_name, unsigned int the_price, unsigned short prep_time);

        bool operator==(const Appetizer& other) const noexcept;
        bool operator!=(const Appetizer& other) const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Appetizer& app);
};
