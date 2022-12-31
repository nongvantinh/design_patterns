#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H
#include <string>
#include <sstream>
#include <memory>
#include <vector>

namespace pizza_store
{
    using String = std::string;

    class Pizza
    {
    public:
        String get_name() { return m_name; }
        String prepare() { return "Preparing " + m_name + "\n"; }
        String bake() { return "Baking " + m_name + "\n"; }
        String cut() { return "Cutting " + m_name + "\n"; }
        String box() { return "Boxing " + m_name + "\n"; }
        String to_string()
        {
            // code to display pizza m_name and ingredients
            std::ostringstream display;
            display << "---- " << m_name << " ----\n";
            display << m_dough << "\n";
            display << m_sauce << "\n";
            for (String topping : m_toppings)
            {
                display << topping << "\n";
            }
            return display.str();
        }

    protected:
        String m_name;
        String m_dough;
        String m_sauce;
        std::vector<String> m_toppings;
    };

    class CheesePizza : public Pizza
    {
    public:
        CheesePizza()
        {
            m_name = "Cheese Pizza";
            m_dough = "Regular Crust";
            m_sauce = "Marinara Pizza Sauce";
            m_toppings.push_back("Fresh Mozzarella");
            m_toppings.push_back("Parmesan");
        }
    };

    class ClamPizza : public Pizza
    {
    public:
        ClamPizza()
        {
            m_name = "Clam Pizza";
            m_dough = "Thin crust";
            m_sauce = "White garlic m_sauce";
            m_toppings.push_back("Clams");
            m_toppings.push_back("Grated parmesan cheese");
        }
    };

    class PepperoniPizza : public Pizza
    {
    public:
        PepperoniPizza()
        {
            m_name = "Pepperoni Pizza";
            m_dough = "Crust";
            m_sauce = "Marinara sauce";
            m_toppings.push_back("Sliced Pepperoni");
            m_toppings.push_back("Sliced Onion");
            m_toppings.push_back("Grated parmesan cheese");
        }
    };

    class SimplePizzaFactory
    {
    public:
        std::shared_ptr<Pizza> create_pizza(String p_type);
    };

    class PizzaStore
    {
    public:
        PizzaStore(SimplePizzaFactory &p_factory)
            : m_factory(p_factory) {}

        std::shared_ptr<Pizza> order_pizza(String p_type)
        {
            std::shared_ptr<Pizza> pizza;
            pizza = m_factory.create_pizza(p_type);

            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();

            return pizza;
        }

    private:
        SimplePizzaFactory &m_factory;
    };

    class VeggiePizza : public Pizza
    {
    public:
        VeggiePizza()
        {
            m_name = "Veggie Pizza";
            m_dough = "Crust";
            m_sauce = "Marinara sauce";
            m_toppings.push_back("Shredded mozzarella");
            m_toppings.push_back("Grated parmesan");
            m_toppings.push_back("Diced onion");
            m_toppings.push_back("Sliced mushrooms");
            m_toppings.push_back("Sliced red pepper");
            m_toppings.push_back("Sliced black olives");
        }
    };

    std::shared_ptr<Pizza> SimplePizzaFactory::create_pizza(String p_type)
    {
        std::shared_ptr<Pizza> pizza = nullptr;

        if ("cheese" == p_type)
        {
            pizza = std::make_shared<CheesePizza>();
        }
        else if ("pepperoni" == p_type)
        {
            pizza = std::make_shared<PepperoniPizza>();
        }
        else if ("clam" == p_type)
        {
            pizza = std::make_shared<ClamPizza>();
        }
        else if ("veggie" == p_type)
        {
            pizza = std::make_shared<VeggiePizza>();
        }
        return pizza;
    }
}
#endif // !PIZZA_STORE_H