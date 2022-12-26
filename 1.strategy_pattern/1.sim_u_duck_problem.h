#ifndef SIM_U_DUCK_PROBLEM_H
#define SIM_U_DUCK_PROBLEM_H

/*
 * We know that the the spec will keep changing, and we will need to override all unused methods and
 * It causes the following problems:
 *		- Code is duplicated across subclasses.
 *		- Runtime behavior changes are difficult.
 *		- Hard to gain knowledge of all duck behaviors.
 *		- Changes can unintentionally affect other ducks.
 */

class Duck
{
public:
	virtual void display() = 0;
	virtual void quack();
	virtual void swim();
	// By putting fly() in the superclass, we gave flying ability to ALL ducks, including those that shouldn't.
	virtual void fly();
};

class MallardDuck : public Duck
{
public:
	void display() override;
};

class RedheadDuck : public Duck
{
public:
	void display() override;
};

// RubberDuck can't fly, so we can just override fly() and do nothing.
class RubberDuck : public Duck
{
public:
	void quack() override;
	void display() override;
	void fly() override;
};

// But the DecoyDuck can't "fly" nor "quack", but it inherit fly() and quack() from the Duck class.
class DecoyDuck : public Duck
{
public:
	void display() override;
};

#endif // !SIM_U_DUCK_PROBLEM_H
