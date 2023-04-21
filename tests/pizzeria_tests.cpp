#include "catch_amalgamated.hpp"
#include "../food.h"
#include "../free_food_exception.h"


TEST_CASE("Food tests", "[food]")
{
    Food spag("Spaghetti carbanana", 1234);

    CHECK(spag.get_name() == "Spaghetti carbanana");
    CHECK(spag.get_price() == 1234);

    SECTION("inicialize with price = 0")
    {
        CHECK_THROWS(Food("YAS", 0));
    }

    SECTION("name modification")
    {
        CHECK(spag.get_name() == "Spaghetti carbanana");
        spag.set_name("Spaghetti mistakese");
        CHECK(spag.get_name() == "Spaghetti mistakese");
    }

    SECTION("price modification")
    {
        CHECK(spag.get_price() == 1234);
        spag.set_price(2137);
        CHECK(spag.get_price() == 2137);
    }

    SECTION("change price to 0")
    {
        CHECK_THROWS(spag.set_price(0));
    }
}