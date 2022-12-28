#include "1.sim_u_duck_inheritance.h"

#include "Catch.hpp"
#include <memory>

using namespace sim_u_duck_inheritance;

String Duck::quack() { return "Quack"; }
String Duck::swim() const { return "All ducks float, even decoys!"; }
String Duck::fly() { return "I'm flying!!"; }

String MallardDuck::display() { return "I'm a real Mallard duck"; }
String RedHeadDuck::display() { return "I'm a real Red Headed duck"; }

String RubberDuck::quack() { return "Squeak"; }
String RubberDuck::display() { return "I'm a rubber duckie"; }
String RubberDuck::fly() { return "I can't fly"; /* Do nothing.*/ }

String DecoyDuck::quack() { return "<< Silence >>"; }
String DecoyDuck::fly() { return "I can't fly"; /* Do nothing.*/ }
String DecoyDuck::display() { return "I'm a duck Decoy"; }

TEST_CASE("Test sim_u_duck_inheritance", "[strategy]")
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    REQUIRE("I'm a real Mallard duck" == mallard->display());
    REQUIRE("Quack" == mallard->quack());
    REQUIRE("I'm flying!!" == mallard->fly());

    std::shared_ptr<Duck> decoy = std::make_shared<DecoyDuck>();
    REQUIRE("I'm a duck Decoy" == decoy->display());
    REQUIRE("<< Silence >>" == decoy->quack());
    REQUIRE("I can't fly" == decoy->fly());
}
