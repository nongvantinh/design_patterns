#ifndef PIZZA_STORE_FACTORY_METHOD_H
#define PIZZA_STORE_FACTORY_METHOD_H
#include <string>
#include <memory>
#include <sstream>
#include <vector>

namespace pizza_store_factory_method
{
	using String = std::string;
	class Pizza
	{
	public:
		Pizza() {}

		String prepare()
		{
			std::ostringstream oss;

			oss << "Preparing " << m_name << "\n";
			oss << "Tossing " << m_dough << "\n";
			oss << "Adding " << m_sauce << "\n";

			oss << "Adding toppings:"
				<< "\n";

			for (String topping : m_toppings)
			{
				oss << "\t" << topping << "\n";
			}

			return oss.str();
		}

		virtual String bake() { return "Bake for 25 minutes at 350\n"; }
		virtual String cut() { return "Cut the pizza into diagonal slices\n"; }
		virtual String box() { return "Place pizza in official PizzaStore box\n"; }
		String get_name() { return m_name; }

	protected:
		String m_name;
		String m_dough;
		String m_sauce;
		std::vector<String> m_toppings;
	};

	class PizzaStore
	{
	public:
		PizzaStore() {}

		std::shared_ptr<Pizza> order_pizza(String p_type)
		{
			std::shared_ptr<Pizza> pizza;

			pizza = create_pizza(p_type);

			pizza->prepare();
			pizza->bake();
			pizza->cut();
			pizza->box();

			return pizza;
		}

	protected:
		virtual std::shared_ptr<Pizza> create_pizza(String p_type) = 0;
	};

	class ChicagoStyleClamPizza : public Pizza
	{
	public:
		ChicagoStyleClamPizza()
		{
			m_name = "Chicago Style Clam Pizza";
			m_dough = "Extra Thick Crust Dough";
			m_sauce = "Plum Tomato Sauce";

			m_toppings.push_back("Shredded Mozzarella Cheese");
			m_toppings.push_back("Frozen Clams from Chesapeake Bay");
		}

		String cut() override { return "Cutting the pizza into square slices\n"; }
	};

	class ChicagoStylePepperoniPizza : public Pizza
	{
	public:
		ChicagoStylePepperoniPizza()
		{
			m_name = "Chicago Style Pepperoni Pizza";
			m_dough = "Extra Thick Crust Dough";
			m_sauce = "Plum Tomato Sauce";

			m_toppings.push_back("Shredded Mozzarella Cheese");
			m_toppings.push_back("Black Olives");
			m_toppings.push_back("Spinach");
			m_toppings.push_back("Eggplant");
			m_toppings.push_back("Sliced Pepperoni");
		}

		String cut() override { return "Cutting the pizza into square slices\n"; }
	};

	class ChicagoStyleVeggiePizza : public Pizza
	{
	public:
		ChicagoStyleVeggiePizza()
		{
			m_name = "Chicago Deep Dish Veggie Pizza";
			m_dough = "Extra Thick Crust Dough";
			m_sauce = "Plum Tomato Sauce";

			m_toppings.push_back("Shredded Mozzarella Cheese");
			m_toppings.push_back("Black Olives");
			m_toppings.push_back("Spinach");
			m_toppings.push_back("Eggplant");
		}

		String cut() override { return "Cutting the pizza into square slices\n"; }
	};

	class ChicagoStyleCheesePizza : public Pizza
	{
	public:
		ChicagoStyleCheesePizza()
		{
			m_name = "Chicago Style Deep Dish Cheese Pizza";
			m_dough = "Extra Thick Crust Dough";
			m_sauce = "Plum Tomato Sauce";

			m_toppings.push_back("Shredded Mozzarella Cheese");
		}

		String cut() override { return "Cutting the pizza into square slices\n"; }
	};

	class NYStyleCheesePizza : public Pizza
	{
	public:
		NYStyleCheesePizza()
		{
			m_name = "NY Style Sauce and Cheese Pizza";
			m_dough = "Thin Crust Dough";
			m_sauce = "Marinara Sauce";

			m_toppings.push_back("Grated Reggiano Cheese");
		}
	};

	class NYStyleClamPizza : public Pizza
	{
	public:
		NYStyleClamPizza()
		{
			m_name = "NY Style Clam Pizza";
			m_dough = "Thin Crust Dough";
			m_sauce = "Marinara Sauce";

			m_toppings.push_back("Grated Reggiano Cheese");
			m_toppings.push_back("Fresh Clams from Long Island Sound");
		}
	};

	class NYStylePepperoniPizza : public Pizza
	{
	public:
		NYStylePepperoniPizza()
		{
			m_name = "NY Style Pepperoni Pizza";
			m_dough = "Thin Crust Dough";
			m_sauce = "Marinara Sauce";

			m_toppings.push_back("Grated Reggiano Cheese");
			m_toppings.push_back("Sliced Pepperoni");
			m_toppings.push_back("Garlic");
			m_toppings.push_back("Onion");
			m_toppings.push_back("Mushrooms");
			m_toppings.push_back("Red Pepper");
		}
	};

	class NYStyleVeggiePizza : public Pizza
	{
	public:
		NYStyleVeggiePizza()
		{
			m_name = "NY Style Veggie Pizza";
			m_dough = "Thin Crust Dough";
			m_sauce = "Marinara Sauce";

			m_toppings.push_back("Grated Reggiano Cheese");
			m_toppings.push_back("Garlic");
			m_toppings.push_back("Onion");
			m_toppings.push_back("Mushrooms");
			m_toppings.push_back("Red Pepper");
		}
	};

	class DependentPizzaStore
	{
	public:
		std::shared_ptr<Pizza> createPizza(String p_style, String p_type)
		{
			std::shared_ptr<Pizza> pizza = nullptr;
			if ("NY" == p_style)
			{
				if ("cheese" == p_type)
				{
					pizza = std::make_shared<NYStyleCheesePizza>();
				}
				else if ("veggie" == p_type)
				{
					pizza = std::make_shared<NYStyleVeggiePizza>();
				}
				else if ("clam" == p_type)
				{
					pizza = std::make_shared<NYStyleClamPizza>();
				}
				else if ("pepperoni" == p_type)
				{
					pizza = std::make_shared<NYStylePepperoniPizza>();
				}
			}
			else if ("Chicago" == p_style)
			{
				if ("cheese" == p_type)
				{
					pizza = std::make_shared<ChicagoStyleCheesePizza>();
				}
				else if ("veggie" == p_type)
				{
					pizza = std::make_shared<ChicagoStyleVeggiePizza>();
				}
				else if ("clam" == p_type)
				{
					pizza = std::make_shared<ChicagoStyleClamPizza>();
				}
				else if ("pepperoni" == p_type)
				{
					pizza = std::make_shared<ChicagoStylePepperoniPizza>();
				}
			}
			else
			{
				// System.out.println("Error: invalid type of pizza");
				return nullptr;
			}
			pizza->prepare();
			pizza->bake();
			pizza->cut();
			pizza->box();
			return pizza;
		}
	};

	class NYPizzaStore : public PizzaStore
	{
	public:
		NYPizzaStore() {}

		std::shared_ptr<Pizza> create_pizza(String p_type) override
		{
			if ("cheese" == p_type)
			{
				return std::make_shared<NYStyleCheesePizza>();
			}
			else if ("veggie" == p_type)
			{
				return std::make_shared<NYStyleVeggiePizza>();
			}
			else if ("clam" == p_type)
			{
				return std::make_shared<NYStyleClamPizza>();
			}
			else if ("pepperoni" == p_type)
			{
				return std::make_shared<NYStylePepperoniPizza>();
			}

			return nullptr;
		}
	};

	class ChicagoPizzaStore : public PizzaStore
	{
	public:
		ChicagoPizzaStore() {}

		std::shared_ptr<Pizza> create_pizza(String p_type) override
		{
			if ("cheese" == p_type)
			{
				return std::make_shared<ChicagoStyleCheesePizza>();
			}
			else if ("veggie" == p_type)
			{
				return std::make_shared<ChicagoStyleVeggiePizza>();
			}
			else if ("clam" == p_type)
			{
				return std::make_shared<ChicagoStyleClamPizza>();
			}
			else if ("pepperoni" == p_type)
			{
				return std::make_shared<ChicagoStylePepperoniPizza>();
			}

			return nullptr;
		}
	};

}
#endif // !PIZZA_STORE_FACTORY_METHOD_H