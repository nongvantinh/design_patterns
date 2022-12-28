#include "3.sim_u_duck_stategy.h"

#include "Catch.hpp"

using namespace sim_u_duck_strategy;

//---------------------------------------------------IFlyBehavior-----------------------------------------------------//

String FlyWithWings::fly() { return "I'm flying!!"; }
String FlyNoWay::fly() { return "I can't fly"; }
String FlyRocketPowered::fly() { return "I'm flying with a rocket"; }
//---------------------------------------------------IFlyBehavior-----------------------------------------------------//

//---------------------------------------------------IQuackBehavior-----------------------------------------------------//
String Quack::quack() { return "Quack"; }
String Squeak::quack() { return "Squeak"; }
String MuteQuack::quack() { return "<< Silence >>"; }
String FakeQuack::quack() { return "Qwak"; }
//---------------------------------------------------IQuackBehavior-----------------------------------------------------//

//---------------------------------------------------Duck-----------------------------------------------------//
Duck::Duck() : m_fly_behavior(nullptr), m_quack_behavior(nullptr) {}
Duck::Duck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior)
	: m_fly_behavior(p_fly_behavior), m_quack_behavior(p_quack_behavior) {}

std::shared_ptr<IFlyBehavior> &Duck::get_fly_behaviour() { return m_fly_behavior; }
void Duck::set_fly_behaviour(std::shared_ptr<IFlyBehavior> p_fly_behavior) { m_fly_behavior = p_fly_behavior; }

std::shared_ptr<IQuackBehavior> Duck::get_quack_behaviour() { return m_quack_behavior; }
void Duck::set_quack_behaviour(std::shared_ptr<IQuackBehavior> p_quack_behavior) { m_quack_behavior = p_quack_behavior; }

String Duck::swim() { return "All ducks float, even decoys!"; }
String Duck::perform_fly() const { return m_fly_behavior->fly(); }
String Duck::perform_quack() const { return m_quack_behavior->quack(); }

//---------------------------------------------------Duck-----------------------------------------------------//

//---------------------------------------------------MallardDuck-----------------------------------------------------//
MallardDuck::MallardDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}
String MallardDuck::display() { return "I'm a real Mallard duck"; }
//---------------------------------------------------MallardDuck-----------------------------------------------------//

//---------------------------------------------------RedHeadDuck-----------------------------------------------------//
RedHeadDuck::RedHeadDuck() : Duck::Duck(std::make_shared<FlyWithWings>(), std::make_shared<Quack>()) {}
String RedHeadDuck::display() { return "I'm a real Red Headed duck"; }
//---------------------------------------------------RedHeadDuck-----------------------------------------------------//

//---------------------------------------------------RubberDuck-----------------------------------------------------//
RubberDuck::RubberDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Squeak>()) {}
RubberDuck::RubberDuck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior)
	: Duck::Duck(p_fly_behavior, p_quack_behavior) {}
String RubberDuck::display() { return "I'm a rubber duckie"; }
//---------------------------------------------------RubberDuck-----------------------------------------------------//

//---------------------------------------------------DecoyDuck-----------------------------------------------------//
DecoyDuck::DecoyDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<MuteQuack>()) {}
String DecoyDuck::display() { return "I'm a duck Decoy"; }
//---------------------------------------------------DecoyDuck-----------------------------------------------------//

//---------------------------------------------------ModelDuck-----------------------------------------------------//
ModelDuck::ModelDuck() : Duck::Duck(std::make_shared<FlyNoWay>(), std::make_shared<Quack>()) {}
String ModelDuck::display() { return "I'm a model duck"; }
//---------------------------------------------------ModelDuck-----------------------------------------------------//

TEST_CASE("StrategyDuckFixture", "[strategy]")
{
	SECTION("TestMallardDuck")
	{
		std::shared_ptr<Duck> mallard = std::make_shared<MallardDuck>();
		REQUIRE("Quack" == mallard->perform_quack());
		REQUIRE("I'm flying!!" == mallard->perform_fly());
	}

	SECTION("TestRubberDuck")
	{
		std::shared_ptr<Duck> rubber_duck = std::make_shared<RubberDuck>(std::make_shared<FlyNoWay>(), std::make_shared<Quack>());
		REQUIRE("Quack" == rubber_duck->perform_quack());
		REQUIRE("I can't fly" == rubber_duck->perform_fly());
	}

	SECTION("TestModelDuck")
	{
		std::shared_ptr<Duck> model_duck = std::make_shared<ModelDuck>();

		REQUIRE("Quack" == model_duck->perform_quack());
		REQUIRE("I can't fly" == model_duck->perform_fly());

		model_duck->set_fly_behaviour(std::make_shared<FlyRocketPowered>());
		REQUIRE("I'm flying with a rocket" == model_duck->get_fly_behaviour()->fly());
		REQUIRE("I'm flying with a rocket" == model_duck->perform_fly());

		model_duck->set_quack_behaviour(std::make_shared<MuteQuack>());
		REQUIRE("<< Silence >>" == model_duck->get_quack_behaviour()->quack());
		REQUIRE("<< Silence >>" == model_duck->perform_quack());
	}
}
