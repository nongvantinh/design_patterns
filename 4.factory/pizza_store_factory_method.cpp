#include "pizza_store_factory_method.h"

#include "Catch.hpp"
#include <iostream>

using namespace pizza_store_factory_method;
void print(String p_value)
{
    std::cout << p_value << std::endl;
}

TEST_CASE("", "[]")
{
    std::shared_ptr<PizzaStore> new_york_store = std::make_shared<NYPizzaStore>();
    std::shared_ptr<PizzaStore> chicago_store = std::make_shared<ChicagoPizzaStore>();

    std::shared_ptr<Pizza> pizza = new_york_store->order_pizza("cheese");
    REQUIRE("Ethan ordered a NY Style Sauce and Cheese Pizza\n" == "Ethan ordered a " + pizza->get_name() + "\n");

    pizza = chicago_store->order_pizza("cheese");
    REQUIRE("Joel ordered a Chicago Style Deep Dish Cheese Pizza\n" == "Joel ordered a " + pizza->get_name() + "\n");

    pizza = new_york_store->order_pizza("clam");
    REQUIRE("Ethan ordered a NY Style Clam Pizza\n" == "Ethan ordered a " + pizza->get_name() + "\n");

    pizza = chicago_store->order_pizza("clam");
    REQUIRE("Joel ordered a Chicago Style Clam Pizza\n" == "Joel ordered a " + pizza->get_name() + "\n");

    pizza = new_york_store->order_pizza("pepperoni");
    REQUIRE("Ethan ordered a NY Style Pepperoni Pizza\n" == "Ethan ordered a " + pizza->get_name() + "\n");

    pizza = chicago_store->order_pizza("pepperoni");
    REQUIRE("Joel ordered a Chicago Style Pepperoni Pizza\n" == "Joel ordered a " + pizza->get_name() + "\n");

    pizza = new_york_store->order_pizza("veggie");
    REQUIRE("Ethan ordered a NY Style Veggie Pizza\n" == "Ethan ordered a " + pizza->get_name() + "\n");

    pizza = chicago_store->order_pizza("veggie");
    REQUIRE("Joel ordered a Chicago Deep Dish Veggie Pizza\n" == "Joel ordered a " + pizza->get_name() + "\n");
}