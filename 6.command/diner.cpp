#include "diner.h"

#include "Catch.hpp"

using namespace diner;

TEST_CASE("Diner", "[]")
{
    SECTION("")
    {
        std::shared_ptr<Order> order = std::make_shared<Order>();
        std::shared_ptr<Waitress> waitress = std::make_shared<Waitress>();
        std::shared_ptr<Customer> custm_ordermer = std::make_shared<Customer>(waitress);

        REQUIRE(" " == custm_ordermer->create_order(std::make_shared<BurgerAndFriesOrder>(order)));
        REQUIRE(" " == custm_ordermer->hungry());
    }
}