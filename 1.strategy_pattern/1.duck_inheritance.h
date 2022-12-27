#ifndef DUCK_INHERITANCE_H
#define DUCK_INHERITANCE_H

/*
 * When we use inheritance, we generate a lot of duplicate code.
 * What if we make a little change that requires updating all other overridden methods?
 */

/*
 * We know that the the spec will keep changing, and we will need to override all unused methods and
 * It causes the following problems:
 *		- Code is duplicated across subclasses.
 *		- Runtime behavior changes are difficult.
 *		- Hard to gain knowledge of all duck behaviors.
 *		- Changes can unintentionally affect other ducks.
 */

#include <string>
using String = std::string;

class Duck
{
public:
	virtual String display() = 0;
	virtual String quack();
	// By putting fly() in the superclass, we gave flying ability to ALL ducks, including those that shouldn't.
	virtual String fly();
	String swim() const;
};

class MallardDuck : public Duck
{
public:
	String display() override;
};

class RedheadDuck : public Duck
{
public:
	String display() override;
};

// RubberDuck can't fly, so we can just override fly() and do nothing.
class RubberDuck : public Duck
{
public:
	String quack() override;
	String display() override;
	String fly() override;
};

// But the DecoyDuck can't "fly" nor "quack", but it inherit fly() and quack() from the Duck class.
class DecoyDuck : public Duck
{
public:
	String quack() override;
	String display() override;
	String fly() override;
};

#endif // !DUCK_INHERITANCE_H
