#include "duck_compound.h"

#include "Catch.hpp"

using namespace duck_compound;

TEST_CASE("CompoundDuckFixture", "[compound]")
{
    SECTION("DuckSimulator")
    {
        std::shared_ptr<AbstractDuckFactory> duckFactory = std::make_shared<CountingDuckFactory>();

        std::shared_ptr<IQuackable> redheadDuck = duckFactory->create_redhead_duck();
        std::shared_ptr<IQuackable> duckCall = duckFactory->create_duck_call();
        std::shared_ptr<IQuackable> rubberDuck = duckFactory->create_rubber_duck();
        std::shared_ptr<IQuackable> gooseDuck = std::make_shared<GooseAdapter>(std::make_shared<Goose>());

        std::shared_ptr<Flock> flockOfDucks = std::make_shared<Flock>();
        flockOfDucks->add(redheadDuck);
        flockOfDucks->add(duckCall);
        flockOfDucks->add(rubberDuck);
        flockOfDucks->add(gooseDuck);

        std::shared_ptr<IQuackable> mallard1 = duckFactory->create_mallard_duck();
        std::shared_ptr<IQuackable> mallard2 = duckFactory->create_mallard_duck();
        std::shared_ptr<IQuackable> mallard3 = duckFactory->create_mallard_duck();
        std::shared_ptr<IQuackable> mallard4 = duckFactory->create_mallard_duck();
        std::shared_ptr<Flock> flockOfMallards = std::make_shared<Flock>();
        std::shared_ptr<Quackologist> quackologist = std::make_shared<Quackologist>();
        flockOfDucks->register_observer(quackologist);
        flockOfMallards->register_observer(quackologist);

        flockOfDucks->add(mallard1);
        flockOfDucks->add(mallard2);
        flockOfDucks->add(mallard3);
        flockOfDucks->add(mallard4);

        SECTION("flockOfDucks")
        {
            std::ostringstream oss;
            oss << "Quack\n";
            oss << "Kwak\n";
            oss << "Squeak\n";
            oss << "Honk\n";
            oss << "Quack\n";
            oss << "Quack\n";
            oss << "Quack\n";
            oss << "Quack\n";
            REQUIRE(oss.str() == flockOfDucks->quack());
        }

        SECTION("flockOfMallards")
        {
            std::ostringstream mallad;
            mallad << "Quack\n";
            mallad << "Quack\n";
            mallad << "Quack\n";
            mallad << "Quack\n";
            REQUIRE(mallad.str() == flockOfMallards->quack());
        }

        REQUIRE(11 == QuackCounter::get_quack_count());
    }
}
