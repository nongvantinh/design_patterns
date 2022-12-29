#include "1.gumball_machine.h"

#include "Catch.hpp"

using namespace gumball_machine;

TEST_CASE("GumballMachineTestDrive", "[state]")
{
    int count = 5;
    GumballMachine gumballMachine(count);
    SECTION("GumballMachine with 5 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumballMachine.toString());
    }

    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("You turned..." == gumballMachine.turn_crank());
    --count;

    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("Quarter returned" == gumballMachine.eject_quarter());
    REQUIRE("You turned but there's no quarter" == gumballMachine.turn_crank());

    SECTION("GumballMachine with 5 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumballMachine.toString());
    }
    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("You turned..." == gumballMachine.turn_crank());
    --count;
    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("You turned..." == gumballMachine.turn_crank());
    --count;
    gumballMachine.eject_quarter();

    SECTION("GumballMachine with 5 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumballMachine.toString());
    }

    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("You can't insert another quarter" == gumballMachine.insert_quarter());
    REQUIRE("You turned..." == gumballMachine.turn_crank());
    --count;
    REQUIRE("You inserted a quarter" == gumballMachine.insert_quarter());
    REQUIRE("You turned..." == gumballMachine.turn_crank());
    --count;
    REQUIRE("You can't insert a quarter, the machine is sold out" == gumballMachine.insert_quarter());
    REQUIRE("You turned, but there are no gumballs" == gumballMachine.turn_crank());

    SECTION("GumballMachine with 5 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "sold out";
        result << "\n";

        REQUIRE(result.str() == gumballMachine.toString());
    }
}