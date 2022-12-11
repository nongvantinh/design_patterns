#include <iostream>

class Duck
{
	virtual void display() = 0;
	virtual void quack()
	{
		std::cout << "quack" << std::endl;
	}
	virtual void swim()
	{
		std::cout << "swim" << std::endl;
	}
	// By putting fly() in the superclass, we gave flying ability to ALL ducks, including those that shouldn’t.
	virtual void fly()
	{
		std::cout << "Fly" << std::endl;
	}
};

class MallardDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a MallardDuck" << std::endl;
	}
};

class RedheadDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a RedheadDuck" << std::endl;
	}

};

// RubberDuck can't fly, so we can just override fly() and do nothing.
class RubberDuck : public Duck
{
	void quack() override
	{
		std::cout << "squeak" << std::endl;
	}
	void display() override
	{
		std::cout << "looks like a RubberDuck" << std::endl;
	}
	void fly() override
	{
		// Do nothing.
	}
};

// But the DecoyDuck can't "fly" nor "quack", but it inherit fly() and quack() from the Duck class.
class DecoyDuck : public Duck
{
	void display() override
	{
		std::cout << "looks like a DecoyDuck" << std::endl;
	}
};

/*
* We know that the the spec will keep changing, and we will need to override all unused methods and
* It causes the following problems:
*		- Code is duplicated across subclasses.
*		- Runtime behavior changes are difficult.
*		- Hard to gain knowledge of all duck behaviors.
*		- Changes can unintentionally affect other ducks.
*/