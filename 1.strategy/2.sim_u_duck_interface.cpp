#include "2.sim_u_duck_interface.h"

#include <iostream>
#include <memory>

using namespace sim_u_duck_interface;

String Duck::swim() const { return "All ducks float, even decoys!"; }

String MallardDuck::fly() { return "I'm flying!!"; }
String MallardDuck::quack() { return "Quack"; }
String MallardDuck::display() { return "I'm a real Mallard duck"; }

String RedheadDuck::fly() { return "I'm flying!!"; }
String RedheadDuck::quack() { return "Quack"; }
String RedheadDuck::display() { return "I'm a real Red Headed duck"; }

String RubberDuck::quack() { return "Squeak"; }
String RubberDuck::display() { return "I'm a rubber duckie"; }

String DecoyDuck::display() { return "I'm a duck Decoy"; }

TEST_CASE("Test sim_u_duck_interface", "[strategy]")
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    REQUIRE("I'm a real Mallard duck" == mallard->display());
    // Can not use interface, class "Duck" has no member "fly" here.
    mallard->fly();
    mallard->quack();

    std::shared_ptr<Duck> decoy = std::make_shared<DecoyDuck>();
    REQUIRE("I'm a duck Decoy" == decoy->display());
    decoy->display();
    decoy->fly();
    decoy->quack();
}
