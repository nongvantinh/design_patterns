#include "pizza_store.h"

#include "Catch.hpp"
#include <iostream>

using namespace pizza_store;
void print(String v)
{
    std::cout << v << std::endl;
}
TEST_CASE("Testpizza_store", "[]")
{
    SimplePizzaFactory factory;
    PizzaStore store(factory);

    SECTION("Cheese Pizza")
    {
        std::shared_ptr<Pizza> pizza = store.order_pizza("cheese");
        REQUIRE("We ordered a Cheese Pizza\n" == "We ordered a " + pizza->get_name() + "\n");
        std::ostringstream oss;
        oss << "---- Cheese Pizza ----\n";
        oss << "Regular Crust\n";
        oss << "Marinara Pizza Sauce\n";
        oss << "Fresh Mozzarella\n";
        oss << "Parmesan\n";
        REQUIRE(oss.str() == pizza->to_string());
    }

    SECTION("Veggie Pizza")
    {
        std::shared_ptr<Pizza> pizza = store.order_pizza("veggie");
        REQUIRE("We ordered a Veggie Pizza\n" == "We ordered a " + pizza->get_name() + "\n");
        std::ostringstream oss;
        oss << "---- Veggie Pizza ----\n";
        oss << "Crust\n";
        oss << "Marinara sauce\n";
        oss << "Shredded mozzarella\n";
        oss << "Grated parmesan\n";
        oss << "Diced onion\n";
        oss << "Sliced mushrooms\n";
        oss << "Sliced red pepper\n";
        oss << "Sliced black olives\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
}