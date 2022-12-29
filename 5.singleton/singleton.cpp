#include "singleton.h"

#include "Catch.hpp"

using namespace classic_singleton;

TEST_CASE("TestSingleton", "[singleton]")
{
    SECTION("Singleton")
    {
        Singleton* boiler = Singleton::get_instance();
        // will return the existing instance
        Singleton* boiler2 = Singleton::get_instance();

        REQUIRE(boiler == boiler2);
    }
}