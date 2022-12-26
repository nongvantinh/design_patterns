#ifndef SIM_U_DUCK_WITH_STRATEGY_PATTERN_H
#define SIM_U_DUCK_WITH_STRATEGY_PATTERN_H
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

class IFlyBehavior
{
public:
	virtual void fly() = 0;
};

class FlyWithWings : public IFlyBehavior
{
	void fly() override;
};

class FlyNoWay : public IFlyBehavior
{
	void fly() override;
};

class FlyRocketPowered : public IFlyBehavior
{
	void fly() override;
};

class IQuackBehavior
{
public:
	virtual void quack() = 0;
};
class Quack : public IQuackBehavior
{
	void quack() override;
};
class Squeak : public IQuackBehavior
{
	void quack() override;
};

class MuteQuack : public IQuackBehavior
{
	void quack() override;
};

class Duck
{
protected:
	Duck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior);

public:
	void perform_fly() const;
	void perform_quack() const;

	void set_fly_behaviour(std::shared_ptr<IFlyBehavior> p_fly_behavior);
	void set_quack_behaviour(std::shared_ptr<IQuackBehavior> p_quack_behavior);

	void swim();
	virtual void display() = 0;

private:
	std::shared_ptr<IFlyBehavior> m_fly_behavior;
	std::shared_ptr<IQuackBehavior> m_quack_behavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck();
	void display() override;
};

class RedheadDuck : public Duck
{
	void display() override;
};

class RubberDuck : public Duck
{
	void display() override;
};

class DecoyDuck : public Duck
{
	void display() override;
};

class ModelDuck : public Duck
{
public:
	ModelDuck();
	void display() override;
};
#endif // !SIM_U_DUCK_WITH_STRATEGY_PATTERN_H
