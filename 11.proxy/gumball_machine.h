#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H
#include <string>
#include <memory>

namespace pizza_store_factory	
{
	using String = std::string;
	class GumballMachine
	{
		std::shared_ptr<State> m_sold_out_state;
		std::shared_ptr<State> m_no_quarter_state;
		std::shared_ptr<State> m_has_quarter_state;
		std::shared_ptr<State> m_sold_state;
		std::shared_ptr<State> m_state;
		String m_location;

		int m_count = 0;

		String Location
		{
			get { return m_location; }
			set { m_location = value; }
		}

		std::shared_ptr<State> StateOfMachine
		{
			get { return m_state; }
			set { m_state = value; }
		}

		int Count
		{
			get { return m_count; }
			set { m_count = value; }
		}

		Properties

		GumballMachine(String m_location, int p_number_of_gumballs)
		{
			m_sold_out_state = new SoldOutState(this);
			m_no_quarter_state = new NoQuarterState(this);
			m_has_quarter_state = new HasQuarterState(this);
			m_sold_state = new SoldState(this);
			m_count = p_number_of_gumballs;
			m_location = m_location;
			if (p_number_of_gumballs > 0)
			{
				m_state = m_no_quarter_state;
			}
			else
			{
				m_state = m_sold_out_state;
			}
		}

		String insert_quarter()
		{
			return m_state.insert_quarter();
		}
		InsertQuarter

			String
			eject_quarter()
		{
			return m_state.eject_quarter();
		}

		String turn_crank()
		{
			return m_state.turn_crank() +
				   m_state.dispense();
		}

		String release_ball()
		{
			if (m_count != 0)
			{
				m_count -= 1;
			}

			return "A gumball comes rolling out the slot...\n";
		}
		ReleaseBall

			String
			refill(int p_number_of_gumballs)
		{
			m_count += p_number_of_gumballs;
			m_state = m_no_quarter_state;

			return "\nRefill: " + p_number_of_gumballs + " gumballs were added. " +
				   "The gumball m_count in now: " + m_count + "\n";
		}
		Refill

			String
			machine_state_header()
		{
			StringBuilder result = new StringBuilder();
			result.Append("Mighty Gumball, Inc.");
			result.Append("\nC# Enabled Standing Gumball Model #2005\n");
			result.Append("Inventory: " + m_count + " gumball");
			if (m_count != 1)
			{
				result.Append("s");
			}
			result.Append("\nMachine is " + m_state.ToString());

			return result.ToString();
		}
		MachineStateHeader
	};
	class GumballMonitor
	{
		GumballMachine m_machine;

		GumballMonitor(GumballMachine m_machine)
		{
			m_machine = m_machine;
		}

		String Report()
		{
			StringBuilder sb = new StringBuilder();

			sb.Append("Gumball Machine: " + m_machine.Location + "\n");
			sb.Append("Current Inventory: " + m_machine.Count + "\n");
			sb.Append("Current std::shared_ptr<State>: " + m_machine.StateOfMachine + "\n");

			return sb.ToString();
		}
	};
	class HasQuarterState : State
	{
		GumballMachine m_gumball_m_machine;
		Random m_random_winner = new Random(System.DateTime.Now.Millisecond);
		// When I was using the winnerState and m_sold_state instance variables I was
		// getting "An unhandled exception of p_type 'System.StackOverflowException'
		// occurred in mscorlib.dll" error?
		//		std::shared_ptr<State> winnerState;
		//		std::shared_ptr<State> m_sold_state;

		HasQuarterState(GumballMachine m_gumball_m_machine)
		{
			m_gumball_m_machine = m_gumball_m_machine;
			//			winnerState = new WinnerState(m_gumball_m_machine);
			//			m_sold_state = new SoldState(m_gumball_m_machine);
		}

		String insert_quarter()
		{
			return "You can't insert another quarter\n";
		}

		String eject_quarter()
		{
			return "Quarter returned\n";
		}

		String turn_crank()
		{
			String outPut;
			outPut = "You turned...\n";

			int winner = m_random_winner.Next(10);
			if (winner == 0 && m_gumball_m_machine.Count > 1)
			{
				m_gumball_m_machine.StateOfMachine = new WinnerState(m_gumball_m_machine);
				//				m_gumball_m_machine.StateOfMachine = winnerState;
			}
			else
			{
				m_gumball_m_machine.StateOfMachine = new SoldState(m_gumball_m_machine);
				//				m_gumball_m_machine.StateOfMachine = m_sold_state;
			}

			return outPut;
		}

		String dispense()
		{
			String outPut;

			outPut = m_gumball_m_machine.release_ball();
			outPut += "No gumball dispensed\n";

			return outPut;
		}

		override String ToString()
		{
			return "waiting for turn of crank";
		}
	};

	class NoQuarterState : State
	{
		GumballMachine m_gumball_m_machine;
		std::shared_ptr<State> m_has_quarter_state;

		NoQuarterState(GumballMachine m_gumball_m_machine)
		{
			m_gumball_m_machine = m_gumball_m_machine;
			m_has_quarter_state = new HasQuarterState(m_gumball_m_machine);
		}

		String insert_quarter()
		{
			m_gumball_m_machine.StateOfMachine = m_has_quarter_state;
			return "You inserted a quarter\n";
		}

		String eject_quarter()
		{
			return "You haven't inserted a quarter\n";
		}

		String turn_crank()
		{
			return "You turned but there's no quarter\n";
		}

		String dispense()
		{
			String outPut;

			outPut = m_gumball_m_machine.release_ball();
			outPut += "You need to pay first\n";

			return outPut;
		}

		override String ToString()
		{
			return "waiting for quarter";
		}
	};

	class SoldOutState : State
	{
		GumballMachine m_gumball_m_machine;

		SoldOutState(GumballMachine m_gumball_m_machine)
		{
			m_gumball_m_machine = m_gumball_m_machine;
		}

		String insert_quarter()
		{
			return "You can't insert a quarter, the m_machine is sold out\n";
		}

		String eject_quarter()
		{
			return "You can't eject, you haven't inserted a quarter yet\n";
		}

		String turn_crank()
		{
			return "Sorry, you already turned the crank\n";
		}

		String dispense()
		{
			String outPut;

			outPut = m_gumball_m_machine.release_ball();
			outPut += "You turned, but there are no gumballs\n";

			return outPut;
		}

		override String ToString()
		{
			return "sold out";
		}
	};
	class SoldState : State
	{
		GumballMachine m_gumball_m_machine;
		std::shared_ptr<State> m_no_quarter_state;
		std::shared_ptr<State> m_sold_out_state;

		SoldState(GumballMachine m_gumball_m_machine)
		{
			m_gumball_m_machine = m_gumball_m_machine;
			m_no_quarter_state = new NoQuarterState(m_gumball_m_machine);
			m_sold_out_state = new SoldOutState(m_gumball_m_machine);
		}

		String insert_quarter()
		{
			return "Please wait, we're already giving you a gumball\n";
		}

		String eject_quarter()
		{
			return "Sorry, you already turned the crank\n";
		}

		String turn_crank()
		{
			return "Turning twice doesn't get you another gumball!\n";
		}

		String dispense()
		{
			String outPut;
			outPut = m_gumball_m_machine.release_ball();
			if (m_gumball_m_machine.Count > 0)
			{
				m_gumball_m_machine.StateOfMachine = m_no_quarter_state;
			}
			else
			{
				m_gumball_m_machine.StateOfMachine = m_sold_out_state;
				outPut += "Oops, out of gumballs!\n";
			}

			return outPut;
		}

		override String ToString()
		{
			return "delivering a gumball";
		}
	};

	interface State
	{
		String insert_quarter();
		String eject_quarter();
		String turn_crank();
		String dispense();
	};

	class WinnerState : State
	{

		GumballMachine m_gumball_m_machine;
		std::shared_ptr<State> m_sold_out_state;
		std::shared_ptr<State> m_no_quarter_state;

		WinnerState(GumballMachine m_gumball_m_machine)
		{
			m_gumball_m_machine = m_gumball_m_machine;
			m_sold_out_state = new SoldOutState(m_gumball_m_machine);
			m_no_quarter_state = new NoQuarterState(m_gumball_m_machine);
		}

		String insert_quarter()
		{
			return "Please wait, we're already giving you a gumball\n";
		}

		String eject_quarter()
		{
			return "Sorry, you already turned the crank\n";
		}

		String turn_crank()
		{
			return "Turning twice doesn't get you another gumball!\n";
		}

		String dispense()
		{
			String outPut;
			outPut = "YOUR A WINNER! You get two gumballs for your quarter\n";
			outPut += m_gumball_m_machine.release_ball();
			if (m_gumball_m_machine.Count == 0)
			{
				m_gumball_m_machine.StateOfMachine = m_sold_out_state;
			}
			else
			{
				outPut += m_gumball_m_machine.release_ball();
				if (m_gumball_m_machine.Count > 0)
				{
					m_gumball_m_machine.StateOfMachine = m_no_quarter_state;
				}
				else
				{
					outPut += "Oops, out of gumballs!\n";
					m_gumball_m_machine.StateOfMachine = m_sold_out_state;
				}
			}
			return outPut;
		}

		override String ToString()
		{
			return "";
		}
	};
}
#endif // !GUMBALL_MACHINE_H