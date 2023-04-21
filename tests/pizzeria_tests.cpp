#include "catch_amalgamated.hpp"
#include "../food.h"
#include "../free_food_exception.h"
#include "../instant_food_exception.h"
#include "../food_already_done_exception.h"
#include "../pizza.h"


TEST_CASE("Food tests", "[food]")
{
    Food spag("Spaghetti carbanana", 1234, 3);

    CHECK(spag.get_name() == "Spaghetti carbanana");
    CHECK(spag.get_price() == 1234);
    CHECK(spag.get_remaining_time() == 3);
    CHECK(spag.is_ready() == false);

    SECTION("inicialize with price = 0")
    {
        CHECK_THROWS(Food("YAS", 0, 12));
    }

    SECTION("inicialize with preparation time = 0")
    {
        CHECK_THROWS(Food("THEST", 1212, 0));
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

    SECTION("preparation time modification")
    {
        CHECK(spag.get_remaining_time() == 3);
        spag.set_preparation_time(14);
        CHECK(spag.get_remaining_time() == 14);
    }

    SECTION("change preparation time to 0")
    {
        CHECK_THROWS(spag.set_preparation_time(0));
    }

    SECTION("food preparation")
    {
        CHECK(spag.get_remaining_time() == 3);
        CHECK(spag.is_ready() == false);
        spag.prepare_food();
        CHECK(spag.get_remaining_time() == 2);
        CHECK(spag.is_ready() == false);
        spag.prepare_food();
        CHECK(spag.get_remaining_time() == 1);
        CHECK(spag.is_ready() == false);
        spag.prepare_food();
        CHECK(spag.get_remaining_time() == 0);
        CHECK(spag.is_ready() == true);
        CHECK_THROWS(spag.prepare_food());
    }
}


TEST_CASE("Pizza tests", "[pizza]")
{
    Pizza pizza("Margherita", 2999, 12, Size::S);

    CHECK(pizza.get_name() == "Margherita");
    CHECK(pizza.get_price() == 2999);
    CHECK(pizza.get_size() == Size::S);

    SECTION("inicialize with price = 0")
    {
        CHECK_THROWS(Pizza("YAS", 0, 12, Size::S));
    }

    SECTION("get price for different sizes")
    {
        CHECK(pizza.get_price() == 2999);
        pizza.set_size(Size::M);
        CHECK(pizza.get_price() == 3298);
        pizza.set_size(Size::L);
        CHECK(pizza.get_price() == 3598);
        pizza.set_size(Size::XL);
        CHECK(pizza.get_price() == 3898);
    }
}