#include "Catch.hpp"

#include <iostream>
#include <memory>

/*
* The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
* Strategy lets the algorithm vary independently from clients that use it.
* 
* With this design, other types of objects can reuse our fly() and quack() behaviors because
* these behaviors are no longer hidden away in our Duck classes!
* 
* And we can add new behaviors without modifying any of our existing behavior classes or
* touching any of the Duck classes that use flying behaviors.
*/

class FlyBehavior
{
public:
	virtual void fly() = 0;
};

class FlyWithWings : public FlyBehavior
{
	void fly() override
	{
		std::cout << "I\'m flying!" << std::endl;
	}
};

class FlyNoWay : public FlyBehavior
{
	void fly() override
	{
		std::cout << "I can\'t fly!" << std::endl;
	}
};

class FlyRocketPowered : public FlyBehavior
{
	void fly() override
	{
		std::cout << "I\'m flying with a rocket!" << std::endl;
	}
};

class QuackBehavior
{
public:
	virtual void quack() = 0;
};

class Quack : public QuackBehavior
{
	void quack() override
	{
		std::cout << "Quack!" << std::endl;
	}
};

class Squeak : public QuackBehavior
{
	void quack() override
	{
		std::cout << "Squeak!" << std::endl;
	}
};

class MuteQuack : public QuackBehavior
{
	void quack() override
	{
		std::cout << " << Silence >> " << std::endl;
	}
};

class Duck
{
public:
	void perform_fly() const { m_fly_behavior->fly(); }
	void perform_quack() const { m_quack_behavior->quack(); }

	void set_fly_behaviour(std::shared_ptr<FlyBehavior> p_fly_behavior) { m_fly_behavior = p_fly_behavior; }
	void set_quack_behaviour(std::shared_ptr<QuackBehavior> p_quack_behavior) { m_quack_behavior = p_quack_behavior; }

	void swim()
	{
		std::cout << "All ducks float, even decoys!" << std::endl;
	}
	virtual void display() = 0;
protected:
	Duck(std::shared_ptr<FlyBehavior> p_fly_behavior, std::shared_ptr<QuackBehavior> p_quack_behavior)
		: m_fly_behavior(p_fly_behavior), m_quack_behavior(p_quack_behavior) {}
private:
	std::shared_ptr<FlyBehavior> m_fly_behavior;
	std::shared_ptr<QuackBehavior> m_quack_behavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}

	void display() override
	{
		std::cout << "I\'m a real Mallard duck" << std::endl;
	}
};

class RedheadDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a RedheadDuck" << std::endl;
	}
};

class RubberDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a RubberDuck" << std::endl;
	}
};

class DecoyDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a DecoyDuck" << std::endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Quack>()) {}

	void display() override
	{
		std::cout << "I\'m a model duck" << std::endl;
	}
};

//TEST_CASE("Separate things change with unchange", "[strategy_pattern]")
//{
//
//	std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
//	mallard->display();
//	mallard->perform_fly();
//	mallard->perform_quack();
//
//	std::shared_ptr<Duck> model = std::make_shared<ModelDuck>();
//	model->display();
//	model->perform_fly();
//	model->set_fly_behaviour(std::make_shared<FlyRocketPowered>());
//	model->perform_fly();
//}