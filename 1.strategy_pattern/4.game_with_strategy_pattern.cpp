#include "4.game_with_strategy_pattern.h"

#include <iostream>

void KnifeBehavior::use_weapon() { std::cout << "I\'m cutting with a knife." << std::endl; }
void BowAndArrowBehavior::use_weapon() { std::cout << "I\'m shooting an arrow with a bow!" << std::endl; }
void AxeBehavior::use_weapon() { std::cout << "I\'m choping with an axe!" << std::endl; }
void SwordBehavior::use_weapon() { std::cout << "I\'m swinging a sword!" << std::endl; }

void Character::attack() const { m_weapon->use_weapon(); }
void Character::set_weapon(std::shared_ptr<IWeaponBehavior> p_weapon) { m_weapon = p_weapon; }
Character::Character(std::shared_ptr<IWeaponBehavior> p_weapon) : m_weapon(p_weapon) {}

King::King() : Character::Character(std::make_shared<SwordBehavior>()) {}
Queen::Queen() : Character::Character(std::make_shared<BowAndArrowBehavior>()) {}
Knight::Knight() : Character::Character(std::make_shared<KnifeBehavior>()) {}
Troll::Troll() : Character::Character(std::make_shared<AxeBehavior>()) {}

int main()
{
	std::shared_ptr<Character> king = std::make_shared<King>();
	king->attack();
	king->set_weapon(std::make_shared<BowAndArrowBehavior>());
	king->attack();
}
