#ifndef DUCKS_ADAPTER_H
#define DUCKS_ADAPTER_H
#include <string>
#include <memory>
#include <sstream>

namespace ducks_adapter
{
	using String = std::string;
	class Duck
	{
	public:
		virtual String quack() = 0;
		virtual String fly() = 0;
	};

	class MallardDuck : public Duck
	{
	public:
		MallardDuck() {}
		String quack() override { return "Quack"; }
		String fly() override { return "I'm flying"; }
	};
	
	class Turkey
	{
	public:
		virtual String gobble() = 0;
		virtual String fly() = 0;
	};

	class WildTurkey : public Turkey
	{
	public:
		WildTurkey() {}
		String gobble() override { return "Gooble, gooble"; }
		String fly() override { return "I'm flying a short distance"; }
	};

	class DuckAdapter : public Turkey
	{
	public:
		DuckAdapter(std::shared_ptr<Duck> p_duck) : m_duck(p_duck) {}
		String gobble() override { return m_duck->quack(); }
		String fly() override { return m_duck->fly(); }

	private:
		std::shared_ptr<Duck> m_duck;
	};

	class TurkeyAdapter : public Duck
	{
	public:
		TurkeyAdapter(std::shared_ptr<Turkey> p_turkey) : m_turkey(p_turkey) {}
		String quack() override { return m_turkey->gobble(); }

		String fly() override
		{
			std::ostringstream oss;

			for (int i = 0; i < 5; ++i)
			{
				oss << m_turkey->fly();
				oss << "\n";
			}
			return oss.str();
		}

	private:
		std::shared_ptr<Turkey> m_turkey;
	};

}
#endif // !DUCKS_ADAPTER_H