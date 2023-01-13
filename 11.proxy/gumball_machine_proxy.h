#ifndef GUMBALL_MACHINE_PROXY_H
#define GUMBALL_MACHINE_PROXY_H
#include <string>
#include <memory>
#include <sstream>
#include <random>

namespace gumball_machine_proxy
{
	using String = std::string;

	class GumballMachine
	{
	public:
		GumballMachine(String p_location, int p_size) : m_location(p_location), m_size(p_size) {}
		String location() { return m_location; }
		int size() { return m_size; }

	private:
		String m_location;
		int m_size = 0;
	};

	class GumballMonitor
	{
	public:
		GumballMonitor(GumballMachine &p_machine) : m_machine(p_machine) {}
		String report()
		{
			std::ostringstream oss;
			oss << "Gumball machine: " << m_machine.location() << "\n";
			oss << "Current Inventory: " << std::to_string(m_machine.size()) + "\n";
			// Other method here...

			return oss.str();
		}

	private:
		GumballMachine &m_machine;
	};
}
#endif // !GUMBALL_MACHINE_PROXY_H