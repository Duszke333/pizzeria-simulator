#include "catch_amalgamated.hpp"
#include "food.h"
#include "exceptions/free_food_exception.h"
#include "exceptions/instant_food_exception.h"
#include "pizza.h"
#include "drink.h"
#include "appetizer.h"
#include "food_list.h"
#include "menu.h"
#include "exceptions/food_not_found_exception.h"
#include "exceptions/no_food_exception.h"
#include "human.h"
#include "client.h"
#include "exceptions/no_work_exception.h"
#include "exceptions/double_work_exception.h"
#include "waiter.h"
#include "group.h"
#include "exceptions/client_already_in_exception.h"
#include "exceptions/client_already_awaiting_exception.h"
#include "exceptions/client_not_invited_exception.h"
#include "order.h"
#include "exceptions/order_empty_exception.h"
#include "table.h"
#include "exceptions/table_not_ready_exception.h"
#include "exceptions/invalid_group_size_exception.h"
#include "RandomNumber.h"

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
        spag.prepare();
        CHECK(spag.get_remaining_time() == 2);
        CHECK(spag.is_ready() == false);
        spag.prepare();
        CHECK(spag.get_remaining_time() == 1);
        CHECK(spag.is_ready() == false);
        spag.prepare();
        CHECK(spag.get_remaining_time() == 0);
        CHECK(spag.is_ready() == true);
        spag.prepare();
        CHECK(spag.get_remaining_time() == 0);
        CHECK(spag.is_ready() == true);
    }

    SECTION("== and !=")
    {
        Food f1("Spaghetti carbanana", 1234, 13);
        Food f2("Spaghetti carbanana", 124, 3);
        Food f3("Spaghetti carbanana", 1234, 1);
        f3.prepare();
        CHECK(f1 == spag);
        CHECK(f1 != f2);
        CHECK(f1 == f3);
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

    SECTION("== and !=")
    {
        Pizza p1("Margherita", 2999, 2, Size::S);
        Pizza p2("Margherita", 2999, 12, Size::L);
        CHECK(p1 == pizza);
        CHECK(p1 != p2);
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

    SECTION("== and !=")
    {
        Drink d1("Cola", 799, 1, Volume::ml330);
        Drink d2("Cola", 799, 12, Volume::l1);
        CHECK(d1 == drink);
        CHECK(d1 != d2);
    }
}


TEST_CASE("Appetizer tests", "[appetizer]")
{
    Appetizer app("Breadsticks", 1299, 1);

    CHECK(app.get_name() == "Breadsticks");
    CHECK(app.get_price() == 1299);
    CHECK(app.get_remaining_time() == 1);
    CHECK(app.is_ready() == false);

    SECTION("== and !=")
    {
        Appetizer a1("Breadsticks", 1299, 31);
        Appetizer a2("Breadsticks", 1298, 1);
        CHECK(a1 == app);
        CHECK(a1 != a2);
    }
}


TEST_CASE("Menu tests", "[menu]")
{
    Menu menu;

    SECTION("Add free food")
    {
        CHECK_THROWS(menu.add_pizza("Margherita", 0, 14, Size::S));
        CHECK_THROWS(menu.add_drink("Water", 0, 1, Volume::ml330));
        CHECK_THROWS(menu.add_appetizer("Garlic bread", 0, 13));
    }

    SECTION("Add instant food")
    {
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
    }

    SECTION("Random foods empty menu")
    {
        CHECK_THROWS(menu.random_drink());
        CHECK_THROWS(menu.random_appetizer());
        CHECK_THROWS(menu.random_pizza());
    }
}


TEST_CASE("Human tests", "[human]")
{
    Human h(12);
    CHECK(h.get_id() == 12);

    SECTION("id modification")
    {
        h.set_id(11);
        CHECK(h.get_id() == 11);
    }

    SECTION("== and != operators")
    {
        Human h1(12);
        Human h2(13);
        CHECK(h == h1);
        CHECK(h1 != h2);
    }
}


TEST_CASE("Waiter tests", "[waiter]")
{
    Waiter w(12);
    CHECK(w.get_id() == 12);
    CHECK(w.is_occupied() == false);
    CHECK(w.get_table_count() == 0);

    SECTION("id modification")
    {
        w.set_id(11);
        CHECK(w.get_id() == 11);
    }

    SECTION("occupation modification")
    {
        w.occupy();
        CHECK(w.is_occupied() == true);
        w.unoccupy();
        CHECK(w.is_occupied() == false);
    }

    SECTION("add table")
    {
        CHECK(w.get_table_count() == 0);
        CHECK(w.has_table(1) == false);
        w.add_table(1);
        CHECK(w.get_table_count() == 1);
        CHECK(w.has_table(1) == true);
        CHECK_THROWS(w.add_table(1));
    }

    SECTION("remove table")
    {
        CHECK(w.get_table_count() == 0);
        CHECK(w.has_table(1) == false);
        w.add_table(1);
        CHECK(w.get_table_count() == 1);
        CHECK(w.has_table(1) == true);
        w.remove_table(1);
        CHECK(w.get_table_count() == 0);
        CHECK(w.has_table(1) == false);
        CHECK_THROWS(w.remove_table(1));
    }

    SECTION("== and != operators")
    {
        Waiter w1(12);
        Waiter w2(13);
        CHECK(w == w1);
        CHECK(w1 != w2);
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
        std::vector<unsigned int> expected = {2};
        CHECK(gr.get_awaiting_ids() == expected);
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
    CHECK(order.drinks_ready() == false);
    CHECK(order.appetizers_ready() == false);
    CHECK(order.pizzas_ready() == false);
    
    SECTION("Add pizza")
    {
        Pizza p("Margherita", 3199, 5, Size::XL);
        order.add_pizza(p);
        CHECK(order.get_price() == 4159);
    } 

    SECTION("Add drink")
    {
        Drink d("Coke", 599, 1, Volume::l1);
        order.add_drink(d);
        CHECK(order.get_price() == 779);
    }

    SECTION("Add appetizer")
    {
        Appetizer a("Breadsticks", 1299, 3);
        order.add_appetizer(a);
        CHECK(order.get_price() == 1299);
    }

    SECTION("Prepare pizzas")
    {
        Pizza p1("Margherita", 2199, 3, Size::S);
        Pizza p2("Pepperoni", 2599, 5, Size::S);
        Drink d("D", 1, 1, Volume::ml330);
        Appetizer a("A", 1, 1);
        order.add_pizza(p1);
        order.add_pizza(p2);
        order.add_drink(d);
        order.add_appetizer(a);
        CHECK(order.get_price() == 4800);
        CHECK(order.drinks_ready() == false);
        CHECK(order.appetizers_ready() == false);
        CHECK(order.pizzas_ready() == false);
        order.prepare_food(0);
        order.prepare_food(0);
        order.prepare_food(0);
        // Now p1 is ready
        CHECK(order.pizzas_ready() == false);
        order.prepare_food(0);
        order.prepare_food(0);
        // Now all pizzas are ready
        CHECK(order.pizzas_ready() == true);
        order.prepare_food(0);
        CHECK(order.pizzas_ready() == true);
    }

    SECTION("Prepare drinks")
    {
        Drink d1("Coke", 599, 1, Volume::ml330);
        Drink d2("Coffee", 799, 2, Volume::ml330);
        Appetizer a("A", 1, 1);
        Pizza p("P", 1, 1, Size::S);
        order.add_drink(d1);
        order.add_drink(d2);
        order.add_appetizer(a);
        order.add_pizza(p);
        CHECK(order.get_price() == 1400);
        CHECK(order.drinks_ready() == false);
        CHECK(order.appetizers_ready() == false);
        CHECK(order.pizzas_ready() == false);
        order.prepare_food(0);
        // Now d1 is ready
        CHECK(order.drinks_ready() == false);
        order.prepare_food(0);
        // Now all drinks are ready
        CHECK(order.drinks_ready() == true);
        order.prepare_food(0);
        CHECK(order.drinks_ready() == true);
    }

    SECTION("Prepare appetizers")
    {
        Appetizer a1("Breadsticks", 1299, 2);
        Appetizer a2("Scallops", 1699, 3);
        Drink d("D", 1, 1, Volume::ml330);
        Pizza p("P", 1, 1, Size::S);
        order.add_appetizer(a1);
        order.add_appetizer(a2);
        order.add_pizza(p);
        order.add_drink(d);
        CHECK(order.get_price() == 3000);
        CHECK(order.drinks_ready() == false);
        CHECK(order.appetizers_ready() == false);
        CHECK(order.pizzas_ready() == false);
        order.prepare_food(0);
        order.prepare_food(0);
        // Now a1 is ready
        CHECK(order.appetizers_ready() == false);
        order.prepare_food(0);
        order.prepare_food(0);
        // Now all appetizers are ready
        CHECK(order.appetizers_ready() == true);
        order.prepare_food(0);
        CHECK(order.appetizers_ready() == true);
    }

    SECTION("Prepare empty order")
    {
        CHECK(order.get_price() == 0);
        CHECK_THROWS(order.prepare_food(0));
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
            order.prepare_food(0);
        }
        CHECK(order.drinks_ready() == true);
        CHECK(order.appetizers_ready() == true);
        CHECK(order.pizzas_ready() == true);
        order.clear_order();
        CHECK(order.get_price() == 0);
        CHECK(order.drinks_ready() == false);
        CHECK(order.appetizers_ready() == false);
        CHECK(order.pizzas_ready() == false);
    }
}


TEST_CASE("Table tests", "[table]")
{
    Menu menu;
    menu.add_pizza("Margherita", 2199, 4, Size::S);
    menu.add_pizza("Margherita", 2199, 5, Size::M);
    menu.add_pizza("Margherita", 2199, 6, Size::L);
    menu.add_pizza("Margherita", 2199, 7, Size::XL);
    menu.add_pizza("Pepperoni", 2499, 5, Size::S);
    menu.add_pizza("Pepperoni", 2499, 6, Size::M);
    menu.add_pizza("Pepperoni", 2499, 7, Size::L);
    menu.add_pizza("Pepperoni", 2499, 8, Size::XL);
    menu.add_appetizer("Breadsticks", 1299, 3);
    menu.add_appetizer("Garlic bread", 899, 4);
    menu.add_drink("Coke", 599, 1, Volume::ml330);
    menu.add_drink("Coke", 599, 1, Volume::ml500);
    menu.add_drink("Coke", 599, 1, Volume::l1);
    menu.add_drink("Coffee", 699, 2, Volume::ml330);
    menu.add_drink("Coffee", 699, 2, Volume::ml500);
    menu.add_drink("Coffee", 699, 2, Volume::l1);

    Table table(1, TableSize::standard, menu);
    CHECK(table.get_status() == Status::Free);
    CHECK(table.get_id() == 1);
    CHECK(table.get_earnings() == 0);
    CHECK(table.get_size() == TableSize::standard);
    CHECK(table.get_group().get_group_size() == 0);
    CHECK(table.get_group().get_id() == 0);
    CHECK(table.ready_for_action() == true);

    SECTION("Set id")
    {
        table.set_id(2);
        CHECK(table.get_id() == 2);
    }

    SECTION("Set size")
    {
        table.set_size(TableSize::big);
        CHECK(table.get_size() == TableSize::big);
    }

    SECTION("Set status")
    {
        table.set_status(Status::WaitingForMenu);
        CHECK(table.get_status() == Status::WaitingForMenu);
        table.set_status(Status::PreparingToOrder);
        CHECK(table.get_status() == Status::PreparingToOrder);
        table.set_status(Status::WaitingForDrinks);
        CHECK(table.get_status() == Status::WaitingForDrinks);
        table.set_status(Status::WaitingForAppetizers);
        CHECK(table.get_status() == Status::WaitingForAppetizers);
        table.set_status(Status::WaitingForPizzas);
        CHECK(table.get_status() == Status::WaitingForPizzas);
        table.set_status(Status::WaitingForReceipt);
        CHECK(table.get_status() == Status::WaitingForReceipt);
        table.set_status(Status::ReadyToPay);
        CHECK(table.get_status() == Status::ReadyToPay);
    }

    SECTION("Set group")
    {
        Group group(12);
        group.add_client(Client(1));
        group.add_client(Client(2));
        group.add_client(Client(3));
        group.add_client(Client(4));
        table.set_group(group);
        CHECK(table.get_group().get_group_size() == 4);
        CHECK(table.get_group().get_id() == 12);
    }

    Group group(12);
    group.add_client(Client(1));
    group.add_client(Client(2));
    group.add_awaiting(3);
    group.add_awaiting(4);
    table.set_group(group);
    std::vector<unsigned int> expected = {3, 4};
    CHECK(table.get_awaiting_ids() == expected);

    SECTION("Bring to table")
    {
        table.bring_to_table(3);
        std::vector<unsigned int> expected1 = {4};
        CHECK(table.get_awaiting_ids() == expected1);
        table.bring_to_table(4);
        std::vector<unsigned int> expected2 = {};
        CHECK(table.get_awaiting_ids() == expected2);
    }

    SECTION("Bring to table not awaiting")
    {
        CHECK_THROWS(table.bring_to_table(1));
    }

    table.set_group(Group());

    SECTION("Interaction")
    {
        // Sitting at the table
        CHECK(table.ready_for_action() == true);
        CHECK(table.get_status() == Status::Free);
        table.set_group(group);
        table.interact();
        // Recieving menu
        CHECK(table.ready_for_action() == true);
        CHECK(table.get_status() == Status::WaitingForMenu);
        table.interact();
        // Ordering
        CHECK(table.ready_for_action() == false);
        CHECK(table.get_status() == Status::PreparingToOrder);
        CHECK_THROWS(table.interact()); // Won't order as group is incomplete
        table.update_status();
        CHECK(table.ready_for_action() == false); // Still not ready as group is incomplete
        table.bring_to_table(Client(3));
        table.bring_to_table(Client(4));
        table.update_status();
        CHECK(table.ready_for_action() == true); // Ready as group is complete
        table.interact();
        CHECK(table.get_order().get_price() != 0);

        // Getting drinks
        CHECK(table.ready_for_action() == false);
        CHECK(table.get_status() == Status::WaitingForDrinks);
        CHECK_THROWS(table.interact()); // Won't get drinks as they're not ready
        table.update_status();
        CHECK(table.ready_for_action() == false); // Still not ready as drinks are not ready
        table.prepare_order();
        table.prepare_order(); // times are now: Drinks - 0, Appetizers - 2, Pizzas - 5
        table.update_status();
        CHECK(table.ready_for_action() == true); // Ready as drinks are now ready
        table.interact();
        // Getting appetizers
        CHECK(table.ready_for_action() == false);
        CHECK(table.get_status() == Status::WaitingForAppetizers);
        CHECK_THROWS(table.interact()); // Won't get appetizers as they're not ready
        table.update_status();
        CHECK(table.ready_for_action() == false); // Still not ready as appetizers are not ready
        table.prepare_order();
        table.prepare_order(); // times are now: Drinks - 0, Appetizers - 0, Pizzas - 4
        table.update_status();
        CHECK(table.ready_for_action() == true); // Ready as appetizers are now ready
        table.interact();
        // Getting pizzas
        CHECK(table.ready_for_action() == false);
        CHECK(table.get_status() == Status::WaitingForPizzas);
        CHECK_THROWS(table.interact()); // Won't get pizzas as they're not ready
        table.update_status();
        CHECK(table.ready_for_action() == false); // Still not ready as pizzas are not ready
        table.prepare_order();
        table.prepare_order();
        table.prepare_order();
        table.prepare_order(); // times are now: Drinks - 0, Appetizers - 0, Pizzas - 0
        table.update_status();
        CHECK(table.ready_for_action() == true); // Ready as pizzas are now ready
        table.interact();
        // Getting receipt
        CHECK(table.ready_for_action() == true);
        CHECK(table.get_status() == Status::WaitingForReceipt);
        table.interact();
        // Paying
        CHECK(table.ready_for_action() == true);
        CHECK(table.get_status() == Status::ReadyToPay);
        table.interact();
        // Leaving
        CHECK(table.get_earnings() != 0);
        CHECK(table.get_group().get_group_size() == 0);
        CHECK(table.get_status() == Status::Free);
        CHECK(table.get_order().get_price() == 0);
    }
}
