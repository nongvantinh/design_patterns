#ifndef BARISTA_TEMPLATE_METHOD_H
#define BARISTA_TEMPLATE_METHOD_H
#include <string>
#include <sstream>

namespace barista_template_method
{
	using String = std::string;
	// TODO: will need to copy this project to the laptop, the new test fixture file and the DeveloperTest.dll.config file in the bin/debug folder
	class CaffeineBeverage
	{
	public:
		String prepare_recipe()
		{
			std::ostringstream oss;
			oss << boil_water();
			oss << brew();
			oss << pour_in_cup();
			oss << add_condiments();

			return oss.str();
		}

		virtual String brew() = 0;
		virtual String add_condiments() = 0;
		String boil_water() { return "Boiling water\n"; }
		String pour_in_cup() { return "Pouring into cup\n"; }
	};

	class CaffeineBeverageWithHook
	{
	public:
		String prepare_recipe()
		{
			std::ostringstream oss;

			oss << boil_water();
			oss << brew();
			oss << pour_in_cup();
			if (customer_wants_condiments())
			{
				oss << add_condiments();
			}

			return oss.str();
		}

		virtual String brew() = 0;
		virtual String add_condiments() = 0;
		String boil_water() { return "Boiling water\n"; }
		String pour_in_cup() { return "Pouring into cup\n"; }

		virtual bool customer_wants_condiments() { return true; }
	};

	class Coffee : public CaffeineBeverage
	{
	public:
		String brew() override { return "Dripping coffee through filter\n"; }
		String add_condiments() override { return "Adding sugar and milk\n"; }
	};

	class CoffeeWithHook : public CaffeineBeverageWithHook
	{
	public:
		String brew() override { return "Dripping coffee through filter\n"; }
		String add_condiments() override { return "Adding sugar and milk\n"; }
		bool customer_wants_condiments() override { return true; }
	};

	class Tea : public CaffeineBeverage
	{
	public:
		String brew() override { return "Steeping the tea\n"; }
		String add_condiments() override { return "Adding lemon\n"; }
	};

	class TeaWithHook : public CaffeineBeverageWithHook
	{
	public:
		String brew() override { return "Steeping the tea\n"; }
		String add_condiments() override { return "Adding lemon\n"; }
		bool customer_wants_condiments() override { return true; }
	};
}
#endif // !BARISTA_TEMPLATE_METHOD_H