#include "starbuzz_with_size_decorator.h"

#include "Catch.hpp"
#include <iostream>
using namespace starbuzz_with_size_decorator;

TEST_CASE("DecoratorStarbuzzWithSizeFixture", "[decorator]")
{
    SECTION("TestEspresso")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
        REQUIRE("Espresso $1.990000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestDarkRoast")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<DarkRoast>();
        beverage->set_size(BeverageSize::GRANDE);
        beverage = std::make_shared<Mocha>(beverage);
        beverage = std::make_shared<Soy>(beverage);

        REQUIRE("Dark Roast Coffee, Mocha, Mocha, Whip $1.340000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestHouseBlend")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<Decaf>();
        beverage->set_size(BeverageSize::GRANDE);
        beverage = std::make_shared<Mocha>(beverage);
        beverage = std::make_shared<Whip>(beverage);

        REQUIRE("Decaf Coffee, Mocha, Whip $1.350000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }
}
