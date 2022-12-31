#ifndef PIZZA__DECORATOR_H
#define PIZZA__DECORATOR_H
#include <string>
#include <memory>

namespace pizza_decorator
{
    using String = std::string;

    class Pizza
    {
    public:
        virtual String description() { return "Basic Pizza"; }
        virtual double cost() = 0;
    };

    class ThincrustPizza : public Pizza
    {
    public:
        String description() override { return "Thin crust pizza, with tomato sauce"; }
        double cost() { return 7.99; }
    };

    class ToppingDecorator : public Pizza
    {
    public:
        ToppingDecorator(std::shared_ptr<Pizza> p_pizza) : m_pizza(p_pizza) {}
        virtual String description() = 0;

    protected:
        std::shared_ptr<Pizza> m_pizza;
    };

    class Cheese : public ToppingDecorator
    {
    public:
        Cheese(std::shared_ptr<Pizza> p_pizza) : ToppingDecorator(p_pizza) {}
        String description() { return m_pizza->description() + ", Cheese"; }
        double cost() { return m_pizza->cost(); /* cheese is free  */ }
    };

    class Olives : public ToppingDecorator
    {
    public:
        Olives(std::shared_ptr<Pizza> p_pizza) : ToppingDecorator(p_pizza) {}
        String description() { return m_pizza->description() + ", Olives"; }
        double cost() { return m_pizza->cost() + .30; }
    };
}
#endif // !PIZZA__DECORATOR_H