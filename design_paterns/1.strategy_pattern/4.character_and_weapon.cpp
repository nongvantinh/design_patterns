#include "Catch.hpp"

#include <iostream>
#include <memory>

/*
* The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
* Strategy lets the algorithm vary independently from clients that use it.
*
* With this design, other types of objects can reuse our use_weapon() behavior because
* these behaviors are no longer hidden away in our Character classes!
*
* And we can add new behaviors without modifying any of our existing behavior classes or
* touching any of the Character classes that use flying behaviors.
*/

class WeaponBehavior
{
public:
	virtual void use_weapon() = 0;
};

class KnifeBehavior : public WeaponBehavior
{
	void use_weapon() override
	{
		std::cout << "I\'m cutting with a knife." << std::endl;
	}
};

class BowAndArrowBehavior : public WeaponBehavior
{
	void use_weapon() override
	{
		std::cout << "I\m shooting an arrow with a bow!" << std::endl;
	}
};

class AxeBehavior : public WeaponBehavior
{
	void use_weapon() override
	{
		std::cout << "I\'m choping with an axe!" << std::endl;
	}
};

class SwordBehavior : public WeaponBehavior
{
	void use_weapon() override
	{
		std::cout << "I\'m swinging a sword!" << std::endl;
	}
};

class Character
{
public:
	void attack() const { m_weapon->use_weapon(); }
	void set_weapon(std::shared_ptr<WeaponBehavior> p_weapon) { m_weapon = p_weapon; }

protected:
	Character(std::shared_ptr<WeaponBehavior> p_weapon) : m_weapon(p_weapon) {}
private:
	std::shared_ptr<WeaponBehavior> m_weapon;
};

class King : public Character
{
public:
	King() : Character::Character(std::make_shared<SwordBehavior>()) {}
};

class Queen : public Character
{
public:
	Queen() : Character::Character(std::make_shared<BowAndArrowBehavior>()) {}
};

class Knight : public Character
{
public:
	Knight() : Character::Character(std::make_shared<KnifeBehavior>()) {}
};

class Troll : public Character
{
public:
	Troll() : Character::Character(std::make_shared<AxeBehavior>()) {}
};
//
//TEST_CASE("Character behaviour design, Separate things change with unchange", "[strategy_pattern]")
//{
//	std::shared_ptr<Character> king = std::make_shared<King>();
//	king->attack();
//	king->set_weapon(std::make_shared<BowAndArrowBehavior>());
//	king->attack();
//}