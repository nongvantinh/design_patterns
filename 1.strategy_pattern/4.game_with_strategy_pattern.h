#ifndef GAME_WITH_STRATEGY_PATTERN_H
#define GAME_WITH_STRATEGY_PATTERN_H
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

class IWeaponBehavior
{
public:
	virtual void use_weapon() = 0;
};

class KnifeBehavior : public IWeaponBehavior
{
	void use_weapon() override;
};

class BowAndArrowBehavior : public IWeaponBehavior
{
	void use_weapon() override;
};

class AxeBehavior : public IWeaponBehavior
{
	void use_weapon() override;
};

class SwordBehavior : public IWeaponBehavior
{
	void use_weapon() override;
};

class Character
{
protected:
	Character(std::shared_ptr<IWeaponBehavior> p_weapon);

public:
	void attack() const;
	void set_weapon(std::shared_ptr<IWeaponBehavior> p_weapon);

private:
	std::shared_ptr<IWeaponBehavior> m_weapon;
};

class King : public Character
{
public:
	King();
};

class Queen : public Character
{
public:
	Queen();
};

class Knight : public Character
{
public:
	Knight();
};

class Troll : public Character
{
public:
	Troll();
};
#endif // !GAME_WITH_STRATEGY_PATTERN_H
