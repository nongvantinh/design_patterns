#ifndef DUCK_INTERFACE_H
#define DUCK_INTERFACE_H

#include <string>
using String = std::string;

class IFlyable
{
public:
	virtual String fly() = 0;
};

class IQuackable
{
public:
	virtual String quack() = 0;
};

class Duck
{
public:
	virtual String display() = 0;
	String swim() const;
};

class MallardDuck : public Duck, IFlyable, IQuackable
{
public:
	String fly() override;
	String quack() override;
	String display() override;
};

class RedheadDuck : public Duck, IFlyable, IQuackable
{
public:
	String fly() override;
	String quack() override;
	String display() override;
};

class RubberDuck : public Duck, IQuackable
{
public:
	String quack() override;
	String display() override;
};

class DecoyDuck : public Duck
{
public:
	String display() override;
};
#endif // !DUCK_INTERFACE_H
