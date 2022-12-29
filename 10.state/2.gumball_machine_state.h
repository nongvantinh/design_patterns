#ifndef GUMBALL_MACHINE_STATE_H
#define GUMBALL_MACHINE_STATE_H

#include <string>
#include <memory>
#include <sstream>

namespace gumball_machine_state
{
	using String = std::string;
	class State
	{
	public:
		virtual String insert_quarter() = 0;
		virtual String eject_quarter() = 0;
		virtual String turn_crank() = 0;
		virtual String dispense() = 0;
		virtual String refill() = 0;
		virtual String to_string() = 0;

		virtual ~State() {}
	};

	class GumballMachine
	{
	public:
		GumballMachine(int p_number_of_gumballs);
		String insert_quarter();
		String eject_quarter();
		String turn_crank();
		String release_ball();
		int get_count();
		String refill(int p_number_of_gumballs);
		std::shared_ptr<State> get_state();
		void set_state(std::shared_ptr<State> p_state);
		std::shared_ptr<State> get_sold_out_state();
		std::shared_ptr<State> get_no_quarter_state();
		std::shared_ptr<State> get_has_quarter_state();
		std::shared_ptr<State> get_sold_state();
		String to_string();

	private:
		std::shared_ptr<State> m_sold_out_state;
		std::shared_ptr<State> m_no_quarter_state;
		std::shared_ptr<State> m_has_quarter_state;
		std::shared_ptr<State> m_sold_state;

		std::shared_ptr<State> m_state;
		int m_count = 0;
	};

	class HasQuarterState : public State
	{
	public:
		HasQuarterState(GumballMachine &p_gumball_machine);
		String insert_quarter() override;
		String eject_quarter() override;
		String turn_crank() override;
		String dispense() override;
		String refill() override;
		String to_string() override;

	private:
		GumballMachine &m_gumball_machine;
	};

	class NoQuarterState : public State
	{
	public:
		NoQuarterState(GumballMachine &p_gumball_machine);
		String insert_quarter() override;
		String eject_quarter() override;
		String turn_crank() override;
		String dispense() override;
		String refill() override;
		String to_string() override;

	private:
		GumballMachine &m_gumball_machine;
	};

	class SoldOutState : public State
	{
	public:
		SoldOutState(GumballMachine &p_gumball_machine);

		String insert_quarter() override;
		String eject_quarter() override;
		String turn_crank() override;
		String dispense() override;
		String refill() override;
		String to_string() override;

	private:
		GumballMachine &m_gumball_machine;
	};

	class SoldState : public State
	{
	public:
		SoldState(GumballMachine &p_gumball_machine);
		String insert_quarter() override;
		String eject_quarter() override;
		String turn_crank() override;
		String dispense() override;
		String refill() override;
		String to_string() override;

	private:
		GumballMachine &m_gumball_machine;
	};
}
#endif // !GUMBALL_MACHINE_STATE_H