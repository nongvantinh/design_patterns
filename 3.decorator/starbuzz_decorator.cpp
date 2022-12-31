#include "starbuzz_decorator.h"

#include "Catch.hpp"
#include <iostream>
using namespace starbuzz_decorator;

TEST_CASE("DecoratorStarbuzzFixture", "[decorator]")
{
    SECTION("TestEspresso")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();
        REQUIRE("Espresso $1.990000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestEspressoWithSize")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<Espresso>();

        beverage = std::make_shared<Mocha>(beverage);

        REQUIRE("Espresso, Mocha $2.190000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestHouseBlend")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<HouseBlend>();
        beverage = std::make_shared<Mocha>(beverage);
        beverage = std::make_shared<Milk>(beverage);

        REQUIRE("House Blend Coffee, Mocha, Milk $1.190000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestDarkRoast")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<DarkRoast>();
        beverage = std::make_shared<Mocha>(beverage);
        beverage = std::make_shared<Soy>(beverage);

        REQUIRE("Dark Roast Coffee, Mocha, Soy $1.340000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }

    SECTION("TestDecaf")
    {
        std::shared_ptr<Beverage> beverage = std::make_shared<Decaf>();
        beverage = std::make_shared<Mocha>(beverage);
        beverage = std::make_shared<Whip>(beverage);

        REQUIRE("Decaf Coffee, Mocha, Whip $1.350000" == beverage->description() + " $" + std::to_string(beverage->cost()));
    }
}
