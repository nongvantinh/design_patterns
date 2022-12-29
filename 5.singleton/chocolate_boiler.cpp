#include "chocolate_boiler.h"

#include "Catch.hpp"

using namespace chocolate_boiler;
std::shared_ptr<ChocolateBoiler> ChocolateBoiler::m_unique_instance = nullptr;

TEST_CASE("TestChocolateBoiler", "[singleton]")
{
    SECTION("ChocolateBoiler")
    {
        std::shared_ptr<ChocolateBoiler> boiler = ChocolateBoiler::get_instance();
        boiler->fill();
        boiler->boil();
        boiler->drain();

        // will return the existing instance
        std::shared_ptr<ChocolateBoiler> boiler2 = ChocolateBoiler::get_instance();

        REQUIRE(boiler == boiler2);
    }
}