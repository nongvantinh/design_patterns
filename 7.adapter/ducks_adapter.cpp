#include "ducks_adapter.h"

#include "Catch.hpp"

using namespace ducks_adapter;

TEST_CASE("AdapterBirdFixture", "[adapter]")
{
    SECTION("TestMallardDuck")
    {
        std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();

        REQUIRE("Quack" == mallard->quack());
        REQUIRE("I'm flying" == mallard->fly());
    }
    SECTION("TestWildTurkey")
    {
        std::shared_ptr<Turkey> wild_turkey = std::make_shared<WildTurkey>();

        REQUIRE("Gooble, gooble" == wild_turkey->gobble());
        REQUIRE("I'm flying a short distance" == wild_turkey->fly());
    }
    SECTION("TestTurkeyAdapter")
    {
        std::shared_ptr<Turkey> wild_turkey = std::make_shared<WildTurkey>();
        std::shared_ptr<Duck> turkey_adapter = std::make_shared<TurkeyAdapter>(wild_turkey);

        REQUIRE("Gooble, gooble" == turkey_adapter->quack());
        std::ostringstream oss;

        oss << "I'm flying a short distance\n"
            << "I'm flying a short distance\n"
            << "I'm flying a short distance\n"
            << "I'm flying a short distance\n"
            << "I'm flying a short distance\n";

        REQUIRE(oss.str() == turkey_adapter->fly());
    }
    SECTION("TestDuckAdapter")
    {
        std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
        std::shared_ptr<Turkey> duck_adapter = std::make_shared<DuckAdapter>(mallard);

        REQUIRE("Quack" == duck_adapter->gobble());
        REQUIRE("I'm flying" == duck_adapter->fly());
    }
}