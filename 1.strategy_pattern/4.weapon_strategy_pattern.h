#ifndef GAME_WITH_STRATEGY_PATTERN_H
#define GAME_WITH_STRATEGY_PATTERN_H

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

#include <memory>
#include <string>
namespace strategy_weapon
{

	using String = std::string;

	//---------------------------------------------------IWeaponBehavior-----------------------------------------------------//
	class IWeaponBehavior
	{
	public:
		virtual String use_weapon() = 0;
	};

	class KnifeBehavior : public IWeaponBehavior
	{
		String use_weapon() override;
	};

	class BowAndArrowBehavior : public IWeaponBehavior
	{
		String use_weapon() override;
	};

	class AxeBehavior : public IWeaponBehavior
	{
		String use_weapon() override;
	};

	class SwordBehavior : public IWeaponBehavior
	{
		String use_weapon() override;
	};
	//---------------------------------------------------IWeaponBehavior-----------------------------------------------------//

	//---------------------------------------------------Character-----------------------------------------------------//
	class Character
	{
	protected:
		Character(std::shared_ptr<IWeaponBehavior> p_weapon);

	public:
		String attack() const;
		void set_weapon(std::shared_ptr<IWeaponBehavior> p_weapon);

	private:
		std::shared_ptr<IWeaponBehavior> m_weapon;
	};
	//---------------------------------------------------Character-----------------------------------------------------//

	//---------------------------------------------------King-----------------------------------------------------//
	class King : public Character
	{
	public:
		King();
	};
	//---------------------------------------------------King-----------------------------------------------------//

	//---------------------------------------------------Queen-----------------------------------------------------//
	class Queen : public Character
	{
	public:
		Queen();
	};
	//---------------------------------------------------Queen-----------------------------------------------------//

	//---------------------------------------------------Knight-----------------------------------------------------//
	class Knight : public Character
	{
	public:
		Knight();
	};
	//---------------------------------------------------Knight-----------------------------------------------------//

	//---------------------------------------------------Troll-----------------------------------------------------//
	class Troll : public Character
	{
	public:
		Troll();
	};
}
//---------------------------------------------------Troll-----------------------------------------------------//
#endif // !GAME_WITH_STRATEGY_PATTERN_H
