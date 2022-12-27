#include "2.duck_interface.h"

#include <iostream>
#include <memory>

String Duck::swim() const { return "All ducks float, even decoys!"; }

String MallardDuck::fly() { return "I\'m flying!"; }
String MallardDuck::quack() { return "Quack!"; }
String MallardDuck::display() { return "I\'m a real Mallard duck"; }

String RedheadDuck::fly() { return "I\'m flying!"; }
String RedheadDuck::quack() { return "Quack!"; }
String RedheadDuck::display() { return "I\'m a real Red Headed duck"; }

String RubberDuck::quack() { return "Squeak!"; }
String RubberDuck::display() { return "I\'m a rubber duckie"; }

String DecoyDuck::display() { return "I\'m a duck Decoy"; }

int main()
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    mallard->display();
    // Can not use interface, class "Duck" has no member "fly" here.
    mallard->fly();
    mallard->quack();

    std::shared_ptr<Duck> model = std::make_shared<DecoyDuck>();
    model->display();
    model->fly();
    model->quack();
}
