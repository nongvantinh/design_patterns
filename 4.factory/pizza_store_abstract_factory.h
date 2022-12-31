#ifndef PIZZA_STORE_ABSTRACT_FACTORY_H
#define PIZZA_STORE_ABSTRACT_FACTORY_H
#include <string>
#include <memory>
#include <sstream>
#include <vector>

namespace pizza_store_abstract_factory
{
	using String = std::string;

	class Dough
	{
	public:
		virtual String to_string() = 0;
	};

	class ThickCrustDough : public Dough
	{
	public:
		String to_string() { return "ThickCrust style extra thick crust dough"; }
	};

	class ThinCrustDough : public Dough
	{
	public:
		String to_string() { return "Thin Crust Dough"; }
	};

	class Sauce
	{
	public:
		virtual String to_string() = 0;
	};

	class MarinaraSauce : public Sauce
	{
	public:
		String to_string() { return "Marinara Sauce"; }
	};

	class PlumTomatoSauce : public Sauce
	{
	public:
		String to_string() { return "Tomato sauce with plum tomatoes"; }
	};

	class Cheese
	{
	public:
		virtual String to_string() = 0;
	};

	class MozzarellaCheese : public Cheese
	{
	public:
		String to_string() { return "Shredded Mozzarella"; }
	};

	class ParmesanCheese : public Cheese
	{
	public:
		String to_string() { return "Shredded Parmesan"; }
	};

	class ReggianoCheese : public Cheese
	{
	public:
		String to_string() { return "Reggiano Cheese"; }
	};

	class Veggies
	{
	public:
		virtual String to_string() = 0;
	};

	class BlackOlives : public Veggies
	{
	public:
		String to_string() { return "Black Olives"; }
	};

	class Eggplant : public Veggies
	{
	public:
		String to_string() { return "Eggplant"; }
	};

	class Garlic : public Veggies
	{
	public:
		String to_string() { return "Garlic"; }
	};

	class Mushroom : public Veggies
	{
	public:
		String to_string() { return "Mushrooms"; }
	};

	class Onion : public Veggies
	{
	public:
		String to_string() { return "Onion"; }
	};

	class RedPepper : public Veggies
	{
	public:
		String to_string() { return "Red Pepper"; }
	};

	class Spinach : public Veggies
	{
	public:
		String to_string() { return "Spinach"; }
	};

	class Pepperoni
	{
	public:
		virtual String to_string() = 0;
	};

	class SlicedPepperoni : public Pepperoni
	{
	public:
		String to_string() { return "Sliced Pepperoni"; }
	};

	class Clams
	{
	public:
		virtual String to_string() = 0;
	};

	class FreshClams : public Clams
	{
	public:
		String to_string() { return "Fresh Clams from Long Island Sound"; }
	};

	class FrozenClams : public Clams
	{
	public:
		String to_string() { return "Frozen Clams from Chesapeake Bay"; }
	};

	class PizzaIngredientFactory
	{
	public:
		virtual std::shared_ptr<Dough> create_dough() = 0;
		virtual std::shared_ptr<Sauce> create_sauce() = 0;
		virtual std::shared_ptr<Cheese> create_cheese() = 0;
		virtual std::vector<std::shared_ptr<Veggies>> create_veggies() = 0;
		virtual std::shared_ptr<Pepperoni> create_pepperoni() = 0;
		virtual std::shared_ptr<Clams> create_clam() = 0;
	};

	class NYPizzaIngredientFactory : public PizzaIngredientFactory
	{
	public:
		std::shared_ptr<Dough> create_dough() { return std::make_shared<ThinCrustDough>(); }
		std::shared_ptr<Sauce> create_sauce() { return std::make_shared<MarinaraSauce>(); }
		std::shared_ptr<Cheese> create_cheese() { return std::make_shared<ReggianoCheese>(); }

		std::vector<std::shared_ptr<Veggies>> create_veggies()
		{
			std::vector<std::shared_ptr<Veggies>> veggies{std::make_shared<Garlic>(),
														  std::make_shared<Onion>(),
														  std::make_shared<Mushroom>(),
														  std::make_shared<RedPepper>()};
			return veggies;
		}

		std::shared_ptr<Pepperoni> create_pepperoni() { return std::make_shared<SlicedPepperoni>(); }
		std::shared_ptr<Clams> create_clam() { return std::make_shared<FreshClams>(); }
	};

	class ChicagoPizzaIngredientFactory : public PizzaIngredientFactory
	{
	public:
		std::shared_ptr<Dough> create_dough() { return std::make_shared<ThickCrustDough>(); }
		std::shared_ptr<Sauce> create_sauce() { return std::make_shared<PlumTomatoSauce>(); }
		std::shared_ptr<Cheese> create_cheese() { return std::make_shared<MozzarellaCheese>(); }

		std::vector<std::shared_ptr<Veggies>> create_veggies()
		{
			std::vector<std::shared_ptr<Veggies>> veggies = {std::make_shared<BlackOlives>(),
															 std::make_shared<Spinach>(),
															 std::make_shared<Eggplant>()};
			return veggies;
		}

		std::shared_ptr<Pepperoni> create_pepperoni() { return std::make_shared<SlicedPepperoni>(); }
		std::shared_ptr<Clams> create_clam() { return std::make_shared<FrozenClams>(); }
	};

	class Pizza
	{
	public:
		virtual String prepare() = 0;

		String bake() { return "Bake for 25 minutes at 350"; }
		String cut() { return "Cutting the pizza into diagonal slices"; }
		String box() { return "Place pizza in official PizzaStore box"; }
		void set_name(String p_name) { m_name = p_name; }
		String get_name() { return m_name; }

		String to_string()
		{
			std::ostringstream oss;
			oss << "---- " + m_name + " ----\n";
			if (nullptr != m_dough)
			{
				oss << m_dough->to_string();
				oss << "\n";
			}
			if (nullptr != m_sauce)
			{
				oss << m_sauce->to_string();
				oss << "\n";
			}
			if (nullptr != m_cheese)
			{
				oss << m_cheese->to_string();
				oss << "\n";
			}
			if (m_veggies.size())
			{
				for (size_t i = 0; i < m_veggies.size(); i++)
				{
					oss << m_veggies[i]->to_string();
					if (i < m_veggies.size() - 1)
					{
						oss << ", ";
					}
				}
				oss << "\n";
			}
			if (nullptr != m_clam)
			{
				oss << m_clam->to_string();
				oss << "\n";
			}
			if (nullptr != m_pepperoni)
			{
				oss << m_pepperoni->to_string();
				oss << "\n";
			}
			return oss.str();
		}

	protected:
		String m_name;

		std::shared_ptr<Dough> m_dough;
		std::shared_ptr<Sauce> m_sauce;
		std::vector<std::shared_ptr<Veggies>> m_veggies;
		std::shared_ptr<Cheese> m_cheese;
		std::shared_ptr<Pepperoni> m_pepperoni;
		std::shared_ptr<Clams> m_clam;
	};

	class CheesePizza : public Pizza
	{
	public:
		CheesePizza(std::shared_ptr<PizzaIngredientFactory> p_ingredient_factory)
		{
			m_ingredient_factory = p_ingredient_factory;
		}

		String prepare()
		{
			m_dough = m_ingredient_factory->create_dough();
			m_sauce = m_ingredient_factory->create_sauce();
			m_cheese = m_ingredient_factory->create_cheese();
			return "Preparing " + m_name;
		}

	private:
		std::shared_ptr<PizzaIngredientFactory> m_ingredient_factory;
	};

	class VeggiePizza : public Pizza
	{
	public:
		VeggiePizza(std::shared_ptr<PizzaIngredientFactory> p_ingredient_factory)
		{
			m_ingredient_factory = p_ingredient_factory;
		}

		String prepare()
		{
			m_dough = m_ingredient_factory->create_dough();
			m_sauce = m_ingredient_factory->create_sauce();
			m_cheese = m_ingredient_factory->create_cheese();
			m_veggies = m_ingredient_factory->create_veggies();
			return "Preparing " + m_name;
		}

	private:
		std::shared_ptr<PizzaIngredientFactory> m_ingredient_factory;
	};

	class PepperoniPizza : public Pizza
	{
	public:
		PepperoniPizza(std::shared_ptr<PizzaIngredientFactory> p_ingredient_factory)
		{
			m_ingredient_factory = p_ingredient_factory;
		}

		String prepare()
		{
			m_dough = m_ingredient_factory->create_dough();
			m_sauce = m_ingredient_factory->create_sauce();
			m_cheese = m_ingredient_factory->create_cheese();
			m_veggies = m_ingredient_factory->create_veggies();
			m_pepperoni = m_ingredient_factory->create_pepperoni();
			return "Preparing " + m_name;
		}

	private:
		std::shared_ptr<PizzaIngredientFactory> m_ingredient_factory;
	};

	class ClamPizza : public Pizza
	{
	public:
		ClamPizza(std::shared_ptr<PizzaIngredientFactory> p_ingredient_factory)
		{
			m_ingredient_factory = p_ingredient_factory;
		}

		String prepare()
		{
			m_dough = m_ingredient_factory->create_dough();
			m_sauce = m_ingredient_factory->create_sauce();
			m_cheese = m_ingredient_factory->create_cheese();
			m_clam = m_ingredient_factory->create_clam();
			return "Preparing " + m_name;
		}

	private:
		std::shared_ptr<PizzaIngredientFactory> m_ingredient_factory;
	};

	class PizzaStore
	{
	public:
		virtual std::shared_ptr<Pizza> create_pizza(String p_item) = 0;

		std::shared_ptr<Pizza> order_pizza(String type)
		{
			std::shared_ptr<Pizza> pizza = create_pizza(type);
			// oss << "--- Making a " + pizza->get_name() + " ---");
			pizza->prepare();
			pizza->bake();
			pizza->cut();
			pizza->box();
			return pizza;
		}
	};

	class NYPizzaStore : public PizzaStore
	{
	protected:
		std::shared_ptr<Pizza> create_pizza(String p_item)
		{
			std::shared_ptr<Pizza> pizza = nullptr;
			std::shared_ptr<PizzaIngredientFactory> ingredient_factory =
				std::make_shared<NYPizzaIngredientFactory>();

			if ("cheese" == p_item)
			{

				pizza = std::make_shared<CheesePizza>(ingredient_factory);
				pizza->set_name("New York Style Cheese Pizza");
			}
			else if ("veggie" == p_item)
			{

				pizza = std::make_shared<VeggiePizza>(ingredient_factory);
				pizza->set_name("New York Style Veggie Pizza");
			}
			else if ("clam" == p_item)
			{

				pizza = std::make_shared<ClamPizza>(ingredient_factory);
				pizza->set_name("New York Style Clam Pizza");
			}
			else if ("pepperoni" == p_item)
			{

				pizza = std::make_shared<PepperoniPizza>(ingredient_factory);
				pizza->set_name("New York Style Pepperoni Pizza");
			}
			return pizza;
		}
	};

	class ChicagoPizzaStore : public PizzaStore
	{
	public:
		std::shared_ptr<Pizza> create_pizza(String p_item)
		{
			std::shared_ptr<Pizza> pizza = nullptr;
			std::shared_ptr<PizzaIngredientFactory> ingredient_factory =
				std::make_shared<ChicagoPizzaIngredientFactory>();

			if ("cheese" == p_item)
			{

				pizza = std::make_shared<CheesePizza>(ingredient_factory);
				pizza->set_name("Chicago Style Cheese Pizza");
			}
			else if ("veggie" == p_item)
			{

				pizza = std::make_shared<VeggiePizza>(ingredient_factory);
				pizza->set_name("Chicago Style Veggie Pizza");
			}
			else if ("clam" == p_item)
			{

				pizza = std::make_shared<ClamPizza>(ingredient_factory);
				pizza->set_name("Chicago Style Clam Pizza");
			}
			else if ("pepperoni" == p_item)
			{

				pizza = std::make_shared<PepperoniPizza>(ingredient_factory);
				pizza->set_name("Chicago Style Pepperoni Pizza");
			}
			return pizza;
		}
	};
}
#endif // !PIZZA_STORE_ABSTRACT_FACTORY_H