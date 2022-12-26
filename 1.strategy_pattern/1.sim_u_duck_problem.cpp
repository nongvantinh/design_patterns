#include "1.sim_u_duck_problem.h"

#include <iostream>
#include <memory>

void Duck::quack() { std::cout << "quack" << std::endl; }
void Duck::swim() { std::cout << "swim" << std::endl; }
void Duck::fly() { std::cout << "Fly" << std::endl; }

void MallardDuck::display() { std::cout << "looks like a MallardDuck" << std::endl; }
void RedheadDuck::display() { std::cout << "looks like a RedheadDuck" << std::endl; }

void RubberDuck::quack() { std::cout << "squeak" << std::endl; }
void RubberDuck::display() { std::cout << "looks like a RubberDuck" << std::endl; }
void RubberDuck::fly()
{ /* Do nothing.*/
}

void DecoyDuck::display() { std::cout << "looks like a DecoyDuck" << std::endl; }

int main()
{
    std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
    mallard->display();
    mallard->fly();
    mallard->quack();

    std::shared_ptr<Duck> model = std::make_shared<DecoyDuck>();
    model->display();
    model->fly();
    model->quack();
}
