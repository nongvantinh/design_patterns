#include "diner_lambda.h"

#include "Catch.hpp"

using namespace diner_lambda;

TEST_CASE("TestDiner", "[command]")
{
    SECTION("")
    {
        std::shared_ptr<Cook> cook = std::make_shared<Cook>();
        std::shared_ptr<Waitress> waitress = std::make_shared<Waitress>();
        std::shared_ptr<Customer> customer = std::make_shared<Customer>(waitress, cook);

        REQUIRE(" " == customer->create_order());
        REQUIRE(" " == customer->hungry());
    }
}