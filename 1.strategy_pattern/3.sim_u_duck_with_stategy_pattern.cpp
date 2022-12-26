#include "3.sim_u_duck_with_stategy_pattern.h"

#include <iostream>

void FlyWithWings::fly() { std::cout << "I\'m flying!" << std::endl; }
void FlyNoWay::fly() { std::cout << "I can\'t fly!" << std::endl; }
void FlyRocketPowered::fly() { std::cout << "I\'m flying with a rocket!" << std::endl; }

void Quack::quack() { std::cout << "Quack!" << std::endl; }
void Squeak::quack() { std::cout << "Squeak!" << std::endl; }
void MuteQuack::quack() { std::cout << " << Silence >> " << std::endl; }

Duck::Duck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior)
	: m_fly_behavior(p_fly_behavior), m_quack_behavior(p_quack_behavior) {}
void Duck::perform_fly() const { m_fly_behavior->fly(); }
void Duck::perform_quack() const { m_quack_behavior->quack(); }
void Duck::set_fly_behaviour(std::shared_ptr<IFlyBehavior> p_fly_behavior) { m_fly_behavior = p_fly_behavior; }
void Duck::set_quack_behaviour(std::shared_ptr<IQuackBehavior> p_quack_behavior) { m_quack_behavior = p_quack_behavior; }
void Duck::swim() { std::cout << "All ducks float, even decoys!" << std::endl; }

MallardDuck::MallardDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}
void MallardDuck::display() { std::cout << "I\'m a real Mallard duck" << std::endl; }

void RedheadDuck::display() { std::cout << "looks like a RedheadDuck" << std::endl; }

void RubberDuck::display() { std::cout << "looks like a RubberDuck" << std::endl; }

void DecoyDuck::display() { std::cout << "looks like a DecoyDuck" << std::endl; }

ModelDuck::ModelDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Quack>()) {}
void ModelDuck::display() { std::cout << "I\'m a model duck" << std::endl; }

int main()
{
	std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
	mallard->display();
	mallard->perform_fly();
	mallard->perform_quack();

	std::shared_ptr<Duck> model = std::make_shared<ModelDuck>();
	model->display();
	model->perform_fly();
	model->set_fly_behaviour(std::make_shared<FlyRocketPowered>());
	model->perform_fly();
}
