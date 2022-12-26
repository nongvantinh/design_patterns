#include "2.sim_u_duck_with_inheritance.h"

#include <iostream>
#include <memory>

void Duck::swim() { std::cout << "swim" << std::endl; }

void MallardDuck::fly() { std::cout << "fly" << std::endl; }
void MallardDuck::quack() { std::cout << "quack" << std::endl; }
void MallardDuck::display() { std::cout << "looks like a MallardDuck" << std::endl; }

void RedheadDuck::fly() { std::cout << "fly" << std::endl; }
void RedheadDuck::quack() { std::cout << "quack" << std::endl; }
void RedheadDuck::display() { std::cout << "looks like a RedheadDuck" << std::endl; }

void RubberDuck::quack() { std::cout << "quack" << std::endl; }
void RubberDuck::display() { std::cout << "looks like a RubberDuck" << std::endl; }

void DecoyDuck::display() { std::cout << "looks like a DecoyDuck" << std::endl; }

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
