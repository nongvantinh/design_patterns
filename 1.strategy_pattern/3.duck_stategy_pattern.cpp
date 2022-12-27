#include "3.duck_stategy_pattern.h"

#include "Catch.hpp"
#include <iostream>

using namespace duck_strategy_pattern;

//---------------------------------------------------IFlyBehavior-----------------------------------------------------//

String FlyWithWings::fly() { return "I\'m flying!"; }
String FlyNoWay::fly() { return "I can\'t fly."; }
String FlyRocketPowered::fly() { return "I\'m flying with a rocket!"; }
//---------------------------------------------------IFlyBehavior-----------------------------------------------------//

//---------------------------------------------------IQuackBehavior-----------------------------------------------------//
String Quack::quack() { return "Quack"; }
String Squeak::quack() { return "Squeak"; }
String MuteQuack::quack() { return "<<silence>>"; }
//---------------------------------------------------IQuackBehavior-----------------------------------------------------//

//---------------------------------------------------Duck-----------------------------------------------------//
Duck::Duck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior)
	: m_fly_behavior(p_fly_behavior), m_quack_behavior(p_quack_behavior) {}

String Duck::perform_fly() const { return m_fly_behavior->fly(); }
String Duck::perform_quack() const { return m_quack_behavior->quack(); }

std::shared_ptr<IFlyBehavior> &Duck::get_fly_behaviour() { return m_fly_behavior; }
std::shared_ptr<IFlyBehavior> Duck::get_fly_behaviour() const { return m_fly_behavior; }
void Duck::set_fly_behaviour(std::shared_ptr<IFlyBehavior> p_fly_behavior) { m_fly_behavior = p_fly_behavior; }

std::shared_ptr<IQuackBehavior> Duck::get_quack_behaviour() { return m_quack_behavior; }
std::shared_ptr<IQuackBehavior> Duck::get_quack_behaviour() const { return m_quack_behavior; }
void Duck::set_quack_behaviour(std::shared_ptr<IQuackBehavior> p_quack_behavior) { m_quack_behavior = p_quack_behavior; }

String Duck::swim() { return "All ducks float, even decoys!"; }
//---------------------------------------------------Duck-----------------------------------------------------//

//---------------------------------------------------MallardDuck-----------------------------------------------------//
MallardDuck::MallardDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}
String MallardDuck::display() { return "I\'m a real Mallard duck"; }
//---------------------------------------------------MallardDuck-----------------------------------------------------//

//---------------------------------------------------RedheadDuck-----------------------------------------------------//
RedheadDuck::RedheadDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}
String RedheadDuck::display() { return "I\'m a real Red Headed duck"; }
//---------------------------------------------------RedheadDuck-----------------------------------------------------//

//---------------------------------------------------RubberDuck-----------------------------------------------------//
RubberDuck::RubberDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Squeak>()) {}
String RubberDuck::display() { return "I\'m a rubber duckie"; }
//---------------------------------------------------RubberDuck-----------------------------------------------------//

//---------------------------------------------------DecoyDuck-----------------------------------------------------//
DecoyDuck::DecoyDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<MuteQuack>()) {}
String DecoyDuck::display() { return "I\'m a duck Decoy"; }
//---------------------------------------------------DecoyDuck-----------------------------------------------------//

//---------------------------------------------------ModelDuck-----------------------------------------------------//
ModelDuck::ModelDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Quack>()) {}
String ModelDuck::display() { return "I\'m a model duck"; }
//---------------------------------------------------ModelDuck-----------------------------------------------------//


TEST_CASE("StrategyDuckFixture", "[strategy]")
{
	SECTION("TestMallardDuck")
	{
		std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
		REQUIRE("Quack" == mallard->perform_quack());
		REQUIRE("I'm flying!" == mallard->perform_fly());
	}

	SECTION("TestRubberDuck")
	{
		std::shared_ptr<Duck> rubber_duck = std::make_shared<RubberDuck>();
		REQUIRE("Squeak" == rubber_duck->perform_quack());
		REQUIRE("I can't fly." == rubber_duck->perform_fly());
	}

	SECTION("TestModelDuck")
	{
		std::shared_ptr<Duck> model_duck = std::make_shared<ModelDuck>();

		REQUIRE("Quack" == model_duck->perform_quack());
		REQUIRE("I can't fly." == model_duck->perform_fly());

		model_duck->set_fly_behaviour(std::make_shared<FlyRocketPowered>());
		REQUIRE("I'm flying with a rocket!" == model_duck->get_fly_behaviour()->fly());
		REQUIRE("I'm flying with a rocket!" == model_duck->perform_fly());

		model_duck->set_quack_behaviour(std::make_shared<MuteQuack>());
		REQUIRE("<<silence>>" == model_duck->get_quack_behaviour()->quack());
		REQUIRE("<<silence>>" == model_duck->perform_quack());
	}
}
