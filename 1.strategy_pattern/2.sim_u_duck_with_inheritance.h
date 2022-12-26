#ifndef SIM_U_DUCK_WITH_INHERITANCE_H
#define SIM_U_DUCK_WITH_INHERITANCE_H

/*
 * When we use inheritance, we generate a lot of duplicate code. What if we make a little change that requires
 * updating all other overridden methods?
 */

class IFlyable
{
public:
	virtual void fly() = 0;
};

class IQuackable
{
public:
	virtual void quack() = 0;
};

class Duck
{
public:
	virtual void display() = 0;
	virtual void swim();
};

class MallardDuck : public Duck, IFlyable, IQuackable
{
public:
	void fly() override;
	void quack() override;
	void display() override;
};

class RedheadDuck : public Duck, IFlyable, IQuackable
{
public:
	void fly() override;
	void quack() override;
	void display() override;
};

class RubberDuck : public Duck, IQuackable
{
public:
	void quack() override;
	void display() override;
};

class DecoyDuck : public Duck
{
public:
	void display() override;
};
#endif // !SIM_U_DUCK_WITH_INHERITANCE_H
