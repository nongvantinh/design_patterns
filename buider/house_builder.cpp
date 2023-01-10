#include "house_builder.h"

#include "Catch.hpp"

using namespace house_builder;

TEST_CASE("HouseDirector", "[builder]")
{
    // Fluent Interface pattern (return the builder each time so we can string the calls together)
    // Builder pattern (we have two different builders so the "same construction process can create
    //   different representations").
    // Builder is a solution to the telescoping constructor anti-pattern, where we have multiple,
    //   complex constructor methods with various args for all various combinations of options
    //   in construction options.

    SECTION("")
    {
        // The Director calls the methods in the correct order to build a m_house.
        // Could make this a lot more complicated to allow number of m_walls, m_windows, to be passed in.

        std::shared_ptr<HouseBuilder> wood_house_builder = std::make_shared<WoodHouseBuilder>();
        std::shared_ptr<House> woodHouse = wood_house_builder->add_walls()->add_windows()->add_roof()->build();
        // print(woodHouse);

        // std::shared_ptr<HouseBuilder> clay_house_builder = std::make_shared<ClayHouseBuilder>();
        // std::shared_ptr<House> clayHouse = clay_house_builder->add_walls()->add_windows()->add_roof()->build();
        // print(clayHouse);

        std::shared_ptr<HouseBuilder> gingerbread_house_builder = std::make_shared<GingerbreadHouseBuilder>();
        std::shared_ptr<House> gingerbreadHouse = gingerbread_house_builder->add_walls()->add_windows()->add_roof()->build();
        // print(gingerbreadHouse);

        // Builder has similarities to Abstract Factory.
        // But difference is that Builder provides a step by step API for building a product;
        //   the client is responsible for calling the steps, and those can vary in order, etc.
        //   With Builder, the client must have more knowledge of the details of the product being built.
        // Product implementations can be swapped for others; clients don't change because the use the abstract API.
        // REQUIRE(" " == " ");
    }
}