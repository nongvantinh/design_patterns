#include "gumball_machine_proxy.h"

#include "Catch.hpp"

using namespace gumball_machine_proxy;

TEST_CASE("GumballMachineTestDrive", "[gumball_machine_proxy]")
{

    int size = 2;
    GumballMachine gumball_machine("home", size);
    GumballMonitor monitor(gumball_machine);

    std::ostringstream oss;
    oss << "Gumball machine: home\n";
    oss << "Current Inventory: " << std::to_string(size) << "\n";

    REQUIRE(oss.str() == monitor.report());
}