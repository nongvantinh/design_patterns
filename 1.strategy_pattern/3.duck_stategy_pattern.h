#ifndef SIM_U_DUCK_WITH_STRATEGY_PATTERN_H
#define SIM_U_DUCK_WITH_STRATEGY_PATTERN_H

/*
 * The Strategy Pattern defines a family of algorithms, encapsulates each one, and makes them interchangeable.
 * Strategy lets the algorithm vary independently from clients that use it.
 *
 * With this design, other types of objects can reuse our fly() and quack() behaviors because
 * these behaviors are no longer hidden away in our Duck classes!
 *
 * And we can add new behaviors without modifying any of our existing behavior classes or
 * touching any of the Duck classes that use flying behaviors.
 */
#include <memory>
#include <string>
namespace duck_strategy_pattern
{
	using String = std::string;

	//---------------------------------------------------IFlyBehavior-----------------------------------------------------//
	class IFlyBehavior
	{
	public:
		virtual String fly() = 0;
	};

	class FlyWithWings : public IFlyBehavior
	{
		String fly() override;
	};

	class FlyNoWay : public IFlyBehavior
	{
		String fly() override;
	};

	class FlyRocketPowered : public IFlyBehavior
	{
		String fly() override;
	};
	//---------------------------------------------------IFlyBehavior-----------------------------------------------------//

	//---------------------------------------------------IQuackBehavior-----------------------------------------------------//
	class IQuackBehavior
	{
	public:
		virtual String quack() = 0;
	};
	class Quack : public IQuackBehavior
	{
		String quack() override;
	};
	class Squeak : public IQuackBehavior
	{
		String quack() override;
	};

	class MuteQuack : public IQuackBehavior
	{
		String quack() override;
	};
	//---------------------------------------------------IQuackBehavior-----------------------------------------------------//

	//---------------------------------------------------Duck-----------------------------------------------------//
	class Duck
	{
	protected:
		Duck(std::shared_ptr<IFlyBehavior> p_fly_behavior, std::shared_ptr<IQuackBehavior> p_quack_behavior);

	public:
		String perform_fly() const;
		String perform_quack() const;

		std::shared_ptr<IFlyBehavior> &get_fly_behaviour();
		std::shared_ptr<IFlyBehavior> get_fly_behaviour() const;
		void set_fly_behaviour(std::shared_ptr<IFlyBehavior> p_fly_behavior);

		std::shared_ptr<IQuackBehavior> get_quack_behaviour();
		std::shared_ptr<IQuackBehavior> get_quack_behaviour() const;
		void set_quack_behaviour(std::shared_ptr<IQuackBehavior> p_quack_behavior);
		String swim();
		virtual String display() = 0;

	private:
		std::shared_ptr<IFlyBehavior> m_fly_behavior;
		std::shared_ptr<IQuackBehavior> m_quack_behavior;
	};
	//---------------------------------------------------Duck-----------------------------------------------------//

	//---------------------------------------------------MallardDuck-----------------------------------------------------//
	class MallardDuck : public Duck
	{
	public:
		MallardDuck();
		String display() override;
	};
	//---------------------------------------------------MallardDuck-----------------------------------------------------//

	//---------------------------------------------------RedheadDuck-----------------------------------------------------//
	class RedheadDuck : public Duck
	{
	public:
		RedheadDuck();
		String display() override;
	};
	//---------------------------------------------------RedheadDuck-----------------------------------------------------//

	//---------------------------------------------------RubberDuck-----------------------------------------------------//
	class RubberDuck : public Duck
	{
	public:
		RubberDuck();
		String display() override;
	};
	//---------------------------------------------------RubberDuck-----------------------------------------------------//

	//---------------------------------------------------DecoyDuck-----------------------------------------------------//
	class DecoyDuck : public Duck
	{
	public:
		DecoyDuck();
		String display() override;
	};
	//---------------------------------------------------DecoyDuck-----------------------------------------------------//

	//---------------------------------------------------ModelDuck-----------------------------------------------------//
	class ModelDuck : public Duck
	{
	public:
		ModelDuck();
		String display() override;
	};
	//---------------------------------------------------ModelDuck-----------------------------------------------------//
}
#endif // !SIM_U_DUCK_WITH_STRATEGY_PATTERN_H
