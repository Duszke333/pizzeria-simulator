#include "catch_amalgamated.hpp"
#include "../food.h"
#include "../free_food_exception.h"
#include "../instant_food_exception.h"
#include "../pizza.h"
#include "../drink.h"
#include "../appetizer.h"
#include "../menu.h"
#include "../food_not_found_exception.h"
#include "../client.h"
#include "../group.h"
#include "../client_already_in_exception.h"
#include "../client_already_awaiting_exception.h"
#include "../client_not_invited_exception.h"
#include "../order.h"
#include "../order_empty_exception.h"


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
        spag.prepare_food();
        CHECK(spag.get_remaining_time() == 0);
        CHECK(spag.is_ready() == true);
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

    SECTION("== and != operators")
    {
        Client c1(12);
        Client c2(13);
        CHECK(cl == c1);
        CHECK(c1 != c2);
    }
}


TEST_CASE("Group tests", "[group]")
{
    Group gr(1);
    CHECK(gr.get_id() == 1);
    CHECK(gr.get_group_size() == 0);
    CHECK(gr.is_complete() == true);

    SECTION("id modification")
    {
        gr.set_id(12);
        CHECK(gr.get_id() == 12);
    }

    Client c1(1);
    Client c2(2);
    Client c3(3);

    SECTION("add client")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_client(c1);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == true);
        gr.add_client(c2);
        CHECK(gr.get_group_size() == 2);
        CHECK(gr.is_complete() == true);
        gr.add_client(c3);
        CHECK(gr.get_group_size() == 3);
        CHECK(gr.is_complete() == true);
    }

    SECTION("try adding the same client twice")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_client(c1);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == true);
        CHECK_THROWS(gr.add_client(c1));
    }

    SECTION("remove client")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_client(c1);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == true);
        gr.remove_client(c1);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
    }

    SECTION("remove the same client twice")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_client(c1);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == true);
        gr.remove_client(c1);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.remove_client(c1);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
    }

    SECTION("remove client not in group")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.remove_client(c1);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
    }

    SECTION("add awaiting")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_awaiting(2);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == false);
    }

    SECTION("try adding the same awaiting twice")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_awaiting(2);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == false);
        CHECK_THROWS(gr.add_awaiting(2));
    }

    SECTION("remove awaiting")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_awaiting(2);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == false);
        gr.remove_awaiting(2);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
    }

    SECTION("remove the same awaiting twice")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_awaiting(2);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == false);
        gr.remove_awaiting(2);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.remove_awaiting(2);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
    }

    SECTION("remove awaiting not in list")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.remove_awaiting(2);
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);        
    }

    SECTION("join the group")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        gr.add_client(c1);
        CHECK(gr.get_group_size() == 1);
        CHECK(gr.is_complete() == true);
        gr.add_awaiting(3);
        CHECK(gr.get_group_size() == 2);
        CHECK(gr.is_complete() == false);
        gr.join(c3);
        CHECK(gr.get_group_size() == 2);
        CHECK(gr.is_complete() == true);
    }

    SECTION("join the group uninvited")
    {
        CHECK(gr.get_group_size() == 0);
        CHECK(gr.is_complete() == true);
        CHECK_THROWS(gr.join(c2));   
    }
}

TEST_CASE("Order tests", "[order]")
{
    Order order;
    CHECK(order.get_price() == 0);
    CHECK(order.ready_to_serve[0] == false);
    CHECK(order.ready_to_serve[1] == false);
    CHECK(order.ready_to_serve[2] == false);
    
    SECTION("Add pizza")
    {
        Pizza p("Margherita", 3199, 5, Size::XL);
        order.add_pizza(p);
        CHECK(order.get_price() == 4159);
    }

    SECTION("Remove pizza")
    {
        Pizza p("Margherita", 3199, 5, Size::XL);
        order.add_pizza(p);
        CHECK(order.get_price() == 4159);
        order.remove_pizza(p);
        CHECK(order.get_price() == 0);
        order.remove_pizza(p);
        CHECK(order.get_price() == 0);
    }    

    SECTION("Add drink")
    {
        Drink d("Coke", 599, 1, Volume::l1);
        order.add_drink(d);
        CHECK(order.get_price() == 779);
    }

    SECTION("Remove drink")
    {
        Drink d("Coke", 599, 1, Volume::l1);
        order.add_drink(d);
        CHECK(order.get_price() == 779);
        order.remove_drink(d);
        CHECK(order.get_price() == 0);
        order.remove_drink(d);
        CHECK(order.get_price() == 0);
    }

    SECTION("Add appetizer")
    {
        Appetizer a("Breadsticks", 1299, 3);
        order.add_appetizer(a);
        CHECK(order.get_price() == 1299);
    }

    SECTION("Remove appetizer")
    {
        Appetizer a("Breadsticks", 1299, 3);
        order.add_appetizer(a);
        CHECK(order.get_price() == 1299);
        order.remove_appetizer(a);
        CHECK(order.get_price() == 0);
        order.remove_appetizer(a);
        CHECK(order.get_price() == 0);
    }

    SECTION("Prepare pizzas")
    {
        Pizza p1("Margherita", 2199, 3, Size::S);
        Pizza p2("Pepperoni", 2599, 5, Size::S);
        order.add_pizza(p1);
        order.add_pizza(p2);
        CHECK(order.get_price() == 4798);
        CHECK(order.ready_to_serve[0] == false);
        CHECK(order.ready_to_serve[1] == false);
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_pizzas();
        order.prepare_pizzas();
        order.prepare_pizzas();
        // Now p1 is ready
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_pizzas();
        order.prepare_pizzas();
        // Now all pizzas are ready
        CHECK(order.ready_to_serve[2] == true);
        order.prepare_pizzas();
        CHECK(order.ready_to_serve[2] == true);
    }

    SECTION("Prepare drinks")
    {
        Drink d1("Coke", 599, 1, Volume::ml330);
        Drink d2("Coffee", 799, 2, Volume::ml330);
        order.add_drink(d1);
        order.add_drink(d2);
        CHECK(order.get_price() == 1398);
        CHECK(order.ready_to_serve[0] == false);
        CHECK(order.ready_to_serve[1] == false);
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_drinks();
        // Now d1 is ready
        CHECK(order.ready_to_serve[0] == false);
        order.prepare_drinks();
        // Now all drinks are ready
        CHECK(order.ready_to_serve[0] == true);
        CHECK(order.ready_to_serve[1] == false);
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_drinks();
        CHECK(order.ready_to_serve[0] == true);
    }

    SECTION("Prepare appetizers")
    {
        Appetizer a1("Breadsticks", 1299, 2);
        Appetizer a2("Scallops", 1699, 3);
        order.add_appetizer(a1);
        order.add_appetizer(a2);
        CHECK(order.get_price() == 2998);
        CHECK(order.ready_to_serve[0] == false);
        CHECK(order.ready_to_serve[1] == false);
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_appetizers();
        order.prepare_appetizers();
        // Now a1 is ready
        CHECK(order.ready_to_serve[1] == false);
        order.prepare_appetizers();
        // Now all appetizers are ready
        CHECK(order.ready_to_serve[0] == false);
        CHECK(order.ready_to_serve[1] == true);
        CHECK(order.ready_to_serve[2] == false);
        order.prepare_appetizers();
        CHECK(order.ready_to_serve[1] == true);
    }

    SECTION("Prepare empty order")
    {
        CHECK(order.get_price() == 0);
        CHECK_THROWS(order.prepare_appetizers());
        CHECK_THROWS(order.prepare_drinks());
        CHECK_THROWS(order.prepare_pizzas());
    }

    SECTION("Order clearing")
    {
        Pizza p1("Margherita", 2199, 3, Size::S);
        Pizza p2("Pepperoni", 2599, 5, Size::S);
        order.add_pizza(p1);
        order.add_pizza(p2);
        Drink d1("Coke", 599, 1, Volume::ml330);
        Drink d2("Coffee", 799, 2, Volume::ml330);
        order.add_drink(d1);
        order.add_drink(d2);
        Appetizer a1("Breadsticks", 1299, 2);
        Appetizer a2("Scallops", 1699, 3);
        order.add_appetizer(a1);
        order.add_appetizer(a2);
        CHECK(order.get_price() == 9194);
        for (short i = 0; i < 5; i++) {
            order.prepare_drinks();
            order.prepare_appetizers();
            order.prepare_pizzas();
        }
        CHECK(order.ready_to_serve[0] == true);
        CHECK(order.ready_to_serve[1] == true);
        CHECK(order.ready_to_serve[2] == true);
        order.clear_order();
        CHECK(order.get_price() == 0);
        CHECK(order.ready_to_serve[0] == false);
        CHECK(order.ready_to_serve[1] == false);
        CHECK(order.ready_to_serve[2] == false);
    }
}
