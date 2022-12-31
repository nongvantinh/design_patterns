#include "pizza_decorator.h"

#include "Catch.hpp"

using namespace pizza_decorator;

TEST_CASE("Test Pizza Store decorator", "[decorator]")
{
    SECTION("Pizza Store")
    {
        std::shared_ptr<Pizza> pizza = std::make_shared<ThincrustPizza>();
        std::shared_ptr<Pizza> cheese_pizza = std::make_shared<Cheese>(pizza);
        std::shared_ptr<Pizza> greek_pizza = std::make_shared<Olives>(cheese_pizza);

        REQUIRE("Thin crust pizza, with tomato sauce, Cheese, Olives $8.290000" == greek_pizza->description() + " $" + std::to_string(greek_pizza->cost()));
    }
}