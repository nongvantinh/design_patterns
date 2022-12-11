#include <iostream>

/*
* When we use inheritance, we generate a lot of duplicate code. What if we make a little change that requires
* updating all other overridden methods?
*/

class Flyable
{
	virtual void fly() = 0;
};

class Quackable
{
	virtual void quack() = 0;
};

class Duck
{
	virtual void display() = 0;
	virtual void swim()
	{
		std::cout << "swim" << std::endl;
	}
};

class MallardDuck : public Duck, Flyable, Quackable
{
	void fly() override
	{
		std::cout << "fly" << std::endl;
	}

	void quack() override
	{
		std::cout << "quack" << std::endl;
	}

	void display() override
	{
		std::cout << "looks like a MallardDuck" << std::endl;
	}
};

class RedheadDuck : public Duck, Flyable, Quackable
{
	void fly() override
	{
		std::cout << "fly" << std::endl;
	}

	void quack() override
	{
		std::cout << "quack" << std::endl;
	}

	void display() override
	{
		std::cout << "looks like a RedheadDuck" << std::endl;
	}
};

class RubberDuck : public Duck, Quackable
{
	void quack() override
	{
		std::cout << "Squeak" << std::endl;
	}

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