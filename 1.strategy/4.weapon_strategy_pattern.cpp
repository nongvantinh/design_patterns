#include "4.weapon_strategy_pattern.h"

#include "Catch.hpp"
#include <iostream>

using namespace strategy_weapon;
//---------------------------------------------------IWeaponBehavior-----------------------------------------------------//
String KnifeBehavior::use_weapon() { return "I will knife thee, nave!"; }
String BowAndArrowBehavior::use_weapon() { return "I shot my arrow at thee!"; }
String AxeBehavior::use_weapon() { return "I will chop thine head off!"; }
String SwordBehavior::use_weapon() { return "I swing at thee with this sword!"; }
//---------------------------------------------------IWeaponBehavior-----------------------------------------------------//

//---------------------------------------------------Character-----------------------------------------------------//
String Character::attack() const { return m_weapon->use_weapon(); }
void Character::set_weapon(std::shared_ptr<IWeaponBehavior> p_weapon) { m_weapon = p_weapon; }
Character::Character(std::shared_ptr<IWeaponBehavior> p_weapon) : m_weapon(p_weapon) {}
//---------------------------------------------------Character-----------------------------------------------------//

//---------------------------------------------------King-----------------------------------------------------//
King::King() : Character::Character(std::make_shared<SwordBehavior>()) {}
//---------------------------------------------------King-----------------------------------------------------//

//---------------------------------------------------Queen-----------------------------------------------------//
Queen::Queen() : Character::Character(std::make_shared<KnifeBehavior>()) {}
//---------------------------------------------------Queen-----------------------------------------------------//

//---------------------------------------------------Knight-----------------------------------------------------//
Knight::Knight() : Character::Character(std::make_shared<BowAndArrowBehavior>()) {}
//---------------------------------------------------Knight-----------------------------------------------------//

//---------------------------------------------------Troll-----------------------------------------------------//
Troll::Troll() : Character::Character(std::make_shared<AxeBehavior>()) {}
//---------------------------------------------------Troll-----------------------------------------------------//

TEST_CASE("StrategyFootballFixture", "[strategy")
{
	SECTION("TestKingWeapon")
	{
		std::shared_ptr<King> kings_weapon = std::make_shared<King>();
		REQUIRE("I swing at thee with this sword!" == kings_weapon->attack());
	}
	SECTION("TestQueenWeapon")
	{
		std::shared_ptr<Queen> queens_weapon = std::make_shared<Queen>();
		REQUIRE("I will knife thee, nave!" == queens_weapon->attack());
	}
	SECTION("TestKnightWeapon")
	{
		std::shared_ptr<Knight> knights_weapon = std::make_shared<Knight>();
		REQUIRE("I shot my arrow at thee!" == knights_weapon->attack());
	}
	SECTION("TestTrollWeapon")
	{
		std::shared_ptr<Troll> trolls_weapon = std::make_shared<Troll>();
		REQUIRE("I will chop thine head off!" == trolls_weapon->attack());
	}
}
