#pragma once
#include "food.h"


enum class Volume {ml330 = 0, ml500, l1};

class Drink : public Food {
    private:
        Volume vol;
    public:
        Drink(std::string the_name, unsigned int the_price, unsigned short prep_time, Volume the_volume);
        unsigned int get_price() const noexcept override;

        Volume get_volume() const noexcept;
        void set_volume(Volume new_volume) noexcept;

        bool operator==(const Drink& other) const noexcept;
        bool operator!=(const Drink& other) const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Drink& drink);
};
