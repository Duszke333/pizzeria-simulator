#include "catch_amalgamated.hpp"
#include "../food.h"
#include "../free_food_exception.h"
#include "../instant_food_exception.h"
#include "../food_already_done_exception.h"
#include "../pizza.h"
#include "../drink.h"
#include "../appetizer.h"
#include "../menu.h"
#include "../food_not_found_exception.h"
#include "../client.h"


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
    CHECK(pizza.get_remaining_time() == 12);
    CHECK(pizza.is_ready() == false);

    SECTION("size modification")
    {
        CHECK(pizza.get_size() == Size::S);
        pizza.set_size(Size::XL);
        CHECK(pizza.get_size() == Size::XL);
    }

    SECTION("get price for different sizes")
    {
        CHECK(pizza.get_price() == 2999);
        pizza.set_size(Size::M);
        CHECK(pizza.get_price() == 3299);
        pizza.set_size(Size::L);
        CHECK(pizza.get_price() == 3599);
        pizza.set_size(Size::XL);
        CHECK(pizza.get_price() == 3899);
    }
}


TEST_CASE("Drink tests", "[drink]")
{
    Drink drink("Cola", 799, 12, Volume::ml330);

    CHECK(drink.get_name() == "Cola");
    CHECK(drink.get_price() == 799);
    CHECK(drink.get_volume() == Volume::ml330);
    CHECK(drink.get_remaining_time() == 12);
    CHECK(drink.is_ready() == false);

    SECTION("size modification")
    {
        CHECK(drink.get_volume() == Volume::ml330);
        drink.set_volume(Volume::l1);
        CHECK(drink.get_volume() == Volume::l1);
    }

    SECTION("get price for different sizes")
    {
        CHECK(drink.get_price() == 799);
        drink.set_volume(Volume::ml500);
        CHECK(drink.get_price() == 959);
        drink.set_volume(Volume::l1);
        CHECK(drink.get_price() == 1039);
    }
}


TEST_CASE("Appetizer tests", "[appetizer]")
{
    Appetizer app("Breadsticks", 1299, 1);

    CHECK(app.get_name() == "Breadsticks");
    CHECK(app.get_price() == 1299);
    CHECK(app.get_remaining_time() == 1);
    CHECK(app.is_ready() == false);
}


TEST_CASE("Menu tests", "[menu]")
{
    Menu menu;

    SECTION("Add free food")
    {
        CHECK_THROWS(menu.add_food("Some food", 0, 12));
        CHECK_THROWS(menu.add_pizza("Margherita", 0, 14, Size::S));
        CHECK_THROWS(menu.add_drink("Water", 0, 1, Volume::ml330));
        CHECK_THROWS(menu.add_appetizer("Garlic bread", 0, 13));
    }

    SECTION("Add instant food")
    {
        CHECK_THROWS(menu.add_food("Some food", 1, 0));
        CHECK_THROWS(menu.add_pizza("Margherita", 12, 0, Size::S));
        CHECK_THROWS(menu.add_drink("Water", 12, 0, Volume::ml330));
        CHECK_THROWS(menu.add_appetizer("Garlic bread", 3, 0));
    }

    SECTION("Calculate total price")
    {
        menu.add_pizza("Margherita", 3199, 12, Size::XL);
        menu.add_appetizer("Garlic bread", 1299, 12);
        menu.add_drink("Water", 599, 1, Volume::l1);
        unsigned int expected = 4159 + 1299 + 779;
        CHECK(menu.calculate_total_price() == expected);
    }

    SECTION("Find food by name")
    {
        menu.add_pizza("Margherita", 3199, 12, Size::XL);
        menu.add_appetizer("Garlic bread", 1299, 12);
        menu.add_drink("Water", 599, 1, Volume::l1);
        Food expected("Margherita", 3199, 12);
        CHECK(menu.find_by_name("Margherita") == expected);
    }

    SECTION("Find food by name not in menu")
    {
        CHECK_THROWS(menu.find_by_name("Bread"));
    }

    SECTION("Remove food")
    {
        menu.add_pizza("Margherita", 3199, 12, Size::S);
        menu.add_pizza("Margherita", 3199, 12, Size::M);
        menu.add_pizza("Margherita", 3199, 12, Size::L);
        menu.add_pizza("Margherita", 3199, 12, Size::XL);
        Food expected("Margherita", 3199, 12);
        CHECK(menu.find_by_name("Margherita") == expected);
        menu.remove_by_name("Margherita");
        CHECK_THROWS(menu.find_by_name("Margherita"));
    }
}


TEST_CASE("Client tests", "[client]")
{
    Client cl(12);
    CHECK(cl.get_id() == 12);
    SECTION("id modification")
    {
        cl.set_id(11);
        CHECK(cl.get_id() == 11);
    }
}
