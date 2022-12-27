#include "1.duck_inheritance.h"

#include <iostream>
#include <memory>

String Duck::quack() { return "Quack!"; }
String Duck::swim() const { return "All ducks float, even decoys!"; }
String Duck::fly() { return "I\'m flying!"; }

String MallardDuck::display() { return "I\'m a real Mallard duck"; }
String RedheadDuck::display() { return "I\'m a real Red Headed duck"; }

String RubberDuck::quack() { return "Squack!"; }
String RubberDuck::display() { return "I\'m a rubber duckie"; }
String RubberDuck::fly() { return "I can\'t fly!"; /* Do nothing.*/}

String DecoyDuck::quack() { return " << Silence >> "; }
String DecoyDuck::fly() { return "I can\'t fly!"; /* Do nothing.*/}
String DecoyDuck::display() { return "I\'m a duck Decoy"; }

int main()
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    std::cout << mallard->display() << std::endl;
    std::cout << mallard->fly() << std::endl;
    std::cout << mallard->quack() << std::endl;

    std::shared_ptr<Duck> model = std::make_shared<DecoyDuck>();
    std::cout << model->display() << std::endl;
    std::cout << model->fly() << std::endl;
    std::cout << model->quack() << std::endl;
}
