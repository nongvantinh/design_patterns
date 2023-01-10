#ifndef PIZZA_BUILDER_H
#define PIZZA_BUILDER_H
#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace pizza_builder
{
    using String = std::string;

    class Pizza
    {
    public:
        void addToppings(std::vector<String> p_toppings)
        {
            m_toppings = p_toppings;
        }

        String prepare()
        {
            std::ostringstream oss;
            oss << "Prepare " + m_name << "\n";
            oss << "Tossing dough..."
                << "\n";
            oss << "Adding sauce..."
                << "\n";
            oss << "Adding m_toppings: "
                << "\n";
            for (String topping : m_toppings)
            {
                oss << "   " << topping << "\n";
            }

            return oss.str();
        }

        String bake() { return "Bake for 25 minutes at 350"; }
        String cut() { return "Cut the pizza into diagonal slices"; }
        String box() { return "Place pizza in official PizzaStore box"; }

        void set_name(String p_name)
        {
            m_name = p_name;
        }

        String to_string()
        {
            std::ostringstream display;
            display << "---- " << m_name << " ----\n";
            for (String topping : m_toppings)
            {
                display << topping << "\n";
            }
            return display.str();
        }

    private:
        String m_name;
        std::vector<String> m_toppings;
    };

    class PizzaBuilder
    {
    public:
        virtual PizzaBuilder *add_cheese() = 0;
        virtual PizzaBuilder *add_sauce() = 0;
        virtual PizzaBuilder *add_tomatoes() = 0;
        virtual PizzaBuilder *add_garlic() = 0;
        virtual PizzaBuilder *add_olives() = 0;
        virtual PizzaBuilder *add_spinach() = 0;
        virtual PizzaBuilder *add_pepperoni() = 0;
        virtual PizzaBuilder *add_sausage() = 0;

        std::shared_ptr<Pizza> build()
        {
            std::shared_ptr<Pizza> pizza = std::make_shared<Pizza>();
            pizza->set_name(m_name);
            pizza->addToppings(m_toppings);
            return pizza;
        }

    protected:
        String m_name;
        std::vector<String> m_toppings;
    };

    class MeatLoversPizzaBuilder : public PizzaBuilder
    {
    public:
        MeatLoversPizzaBuilder()
        {
            m_name = "Meat Lovers Pizza";
        }

        PizzaBuilder *add_cheese() override
        {
            // meat lovers like moz
            m_toppings.push_back("mozzerella");
            return this;
        }

        PizzaBuilder *add_sauce() override
        {
            m_toppings.push_back("NY style sauce");
            return this;
        }

        PizzaBuilder *add_tomatoes() override
        {
            m_toppings.push_back("sliced tomatoes");
            return this;
        }

        PizzaBuilder *add_garlic() override
        {
            m_toppings.push_back("garlic");
            return this;
        }

        PizzaBuilder *add_olives() override
        {
            // never add olives to meat lovers pizza
            return this;
        }

        PizzaBuilder *add_spinach() override
        {
            // never add spinach to meat lovers pizza
            return this;
        }

        PizzaBuilder *add_pepperoni() override
        {
            m_toppings.push_back("pepperoni");
            return this;
        }

        PizzaBuilder *add_sausage() override
        {
            m_toppings.push_back("sausage");
            return this;
        }
    };

    class VeggieLoversPizzaBuilder : public PizzaBuilder
    {
    public:
        VeggieLoversPizzaBuilder()
        {
            m_name = "Veggie Lovers Pizza";
        }
        PizzaBuilder *add_cheese() override
        {
            // veggie lovers like parm
            m_toppings.push_back("parmesan");
            return this;
        }
        PizzaBuilder *add_sauce() override
        {
            m_toppings.push_back("sauce");
            return this;
        }
        PizzaBuilder *add_tomatoes() override
        {
            m_toppings.push_back("chopped tomatoes");
            return this;
        }
        PizzaBuilder *add_garlic() override
        {
            m_toppings.push_back("garlic");
            return this;
        }
        PizzaBuilder *add_olives() override
        {
            m_toppings.push_back("green olives");
            return this;
        }
        PizzaBuilder *add_spinach() override
        {
            m_toppings.push_back("spinach");
            return this;
        }
        PizzaBuilder *add_pepperoni() override
        {
            // never EVER add Pepperoni to veggie lovers pizza
            return this;
        }
        PizzaBuilder *add_sausage() override
        {
            // never EVER add Sausage to veggie lovers pizza
            return this;
        }
    };

}
#endif // !PIZZA_BUILDER_H