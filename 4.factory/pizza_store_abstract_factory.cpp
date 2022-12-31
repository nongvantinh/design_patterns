#include "pizza_store_abstract_factory.h"

#include "Catch.hpp"
#include <iostream>

using namespace pizza_store_abstract_factory;
void print(String p_value)
{
    std::cout << p_value << std::endl;
}

TEST_CASE("", "[]")
{

    std::shared_ptr<PizzaStore> ny_store = std::make_shared<NYPizzaStore>();
    std::shared_ptr<PizzaStore> chicago_store = std::make_shared<ChicagoPizzaStore>();
    SECTION("New York Style Cheese Pizza")
    {
        std::shared_ptr<Pizza> pizza = ny_store->order_pizza("cheese");
        std::ostringstream oss;
        oss << "---- New York Style Cheese Pizza ----\n";
        oss << "Thin Crust Dough\n";
        oss << "Marinara Sauce\n";
        oss << "Reggiano Cheese\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("Chicago Style Cheese Pizza")
    {
        std::shared_ptr<Pizza> pizza = chicago_store->order_pizza("cheese");
        std::ostringstream oss;
        oss << "---- Chicago Style Cheese Pizza ----\n";
        oss << "ThickCrust style extra thick crust dough\n";
        oss << "Tomato sauce with plum tomatoes\n";
        oss << "Shredded Mozzarella\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("New York Style Clam Pizza")
    {
        std::shared_ptr<Pizza> pizza = ny_store->order_pizza("clam");
        std::ostringstream oss;
        oss << "---- New York Style Clam Pizza ----\n";
        oss << "Thin Crust Dough\n";
        oss << "Marinara Sauce\n";
        oss << "Reggiano Cheese\n";
        oss << "Fresh Clams from Long Island Sound\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("Chicago Style Clam Pizza")
    {
        std::shared_ptr<Pizza> pizza = chicago_store->order_pizza("clam");
        std::ostringstream oss;
        oss << "---- Chicago Style Clam Pizza ----\n";
        oss << "ThickCrust style extra thick crust dough\n";
        oss << "Tomato sauce with plum tomatoes\n";
        oss << "Shredded Mozzarella\n";
        oss << "Frozen Clams from Chesapeake Bay\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("New York Style Pepperoni Pizza")
    {
        std::shared_ptr<Pizza> pizza = ny_store->order_pizza("pepperoni");
        std::ostringstream oss;
        oss << "---- New York Style Pepperoni Pizza ----\n";
        oss << "Thin Crust Dough\n";
        oss << "Marinara Sauce\n";
        oss << "Reggiano Cheese\n";
        oss << "Garlic, Onion, Mushrooms, Red Pepper\n";
        oss << "Sliced Pepperoni\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("Chicago Style Pepperoni Pizza")
    {
        std::shared_ptr<Pizza> pizza = chicago_store->order_pizza("pepperoni");
        std::ostringstream oss;
        oss << "---- Chicago Style Pepperoni Pizza ----\n";
        oss << "ThickCrust style extra thick crust dough\n";
        oss << "Tomato sauce with plum tomatoes\n";
        oss << "Shredded Mozzarella\n";
        oss << "Black Olives, Spinach, Eggplant\n";
        oss << "Sliced Pepperoni\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("New York Style Veggie Pizza")
    {
        std::shared_ptr<Pizza> pizza = ny_store->order_pizza("veggie");
        std::ostringstream oss;
        oss << "---- New York Style Veggie Pizza ----\n";
        oss << "Thin Crust Dough\n";
        oss << "Marinara Sauce\n";
        oss << "Reggiano Cheese\n";
        oss << "Garlic, Onion, Mushrooms, Red Pepper\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
    SECTION("Chicago Style Veggie Pizza")
    {
        std::shared_ptr<Pizza> pizza = chicago_store->order_pizza("veggie");
        std::ostringstream oss;
        oss << "---- Chicago Style Veggie Pizza ----\n";
        oss << "ThickCrust style extra thick crust dough\n";
        oss << "Tomato sauce with plum tomatoes\n";
        oss << "Shredded Mozzarella\n";
        oss << "Black Olives, Spinach, Eggplant\n";
        REQUIRE(oss.str() == pizza->to_string());
    }
};

// std::shared_ptr<PizzaStore> new_york_store = std::make_shared<NYPizzaStore>();
// std::shared_ptr<PizzaStore> chicago_store = std::make_shared<ChicagoPizzaStore>();

// std::shared_ptr<Pizza> pizza = new_york_store->order_pizza("cheese");
// REQUIRE("NY Style Sauce and Cheese Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = chicago_store->order_pizza("cheese");
// REQUIRE("Chicago Style Deep Dish Cheese Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = new_york_store->order_pizza("clam");
// REQUIRE("NY Style Clam Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = chicago_store->order_pizza("clam");
// REQUIRE("Chicago Style Clam Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = new_york_store->order_pizza("pepperoni");
// REQUIRE("NY Style Pepperoni Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = chicago_store->order_pizza("pepperoni");
// REQUIRE("Chicago Style Pepperoni Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = new_york_store->order_pizza("veggie");
// REQUIRE("NY Style Veggie Pizza\n" == "" + pizza->get_name() + "\n");

// pizza = chicago_store->order_pizza("veggie");
// REQUIRE("Chicago Deep Dish Veggie Pizza\n" == "" + pizza->get_name() + "\n");