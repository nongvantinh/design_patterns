#ifndef STARBUZZ_DECORATOR_H
#define STARBUZZ_DECORATOR_H
#include <string>
#include <memory>

using String = std::string;

namespace starbuzz_decorator
{
    class Beverage
    {
    public:
        virtual double cost() = 0;
        virtual String description() { return "Unknown Beverage"; }
    };

    class DarkRoast : public Beverage
    {
    public:
        DarkRoast() : Beverage() {}
        double cost() override { return 0.99; }
        String description() override { return "Dark Roast Coffee"; }
    };

    class Decaf : public Beverage
    {
    public:
        Decaf() : Beverage() {}
        double cost() override { return 1.05; }
        String description() override { return "Decaf Coffee"; }
    };

    class Espresso : public Beverage
    {
    public:
        Espresso() : Beverage() {}
        double cost() override { return 1.99; }
        String description() override { return "Espresso"; }
    };

    class HouseBlend : public Beverage
    {
    public:
        HouseBlend() : Beverage() {}
        double cost() override { return 0.89; }
        String description() override { return "House Blend Coffee"; }
    };

    class CondimentDecorator : public Beverage
    {
    public:
        String description() override = 0;
        double cost() override = 0;

    protected:
        CondimentDecorator() : m_beverage(nullptr) {}
        CondimentDecorator(std::shared_ptr<Beverage> p_beverage) : m_beverage(p_beverage) {}

        std::shared_ptr<Beverage> m_beverage;
    };

    class Mocha : public CondimentDecorator
    {
    public:
        Mocha(std::shared_ptr<Beverage> p_beverage) : CondimentDecorator(p_beverage) {}
        String description() override { return m_beverage->description() + ", Mocha"; }
        double cost() override { return 0.20 + m_beverage->cost(); }
    };

    class Soy : public CondimentDecorator
    {
    public:
        Soy(std::shared_ptr<Beverage> p_beverage) : CondimentDecorator(p_beverage) {}
        String description() override { return m_beverage->description() + ", Soy"; }
        double cost() override { return 0.15 + m_beverage->cost(); }
    };

    class Milk : public CondimentDecorator
    {
    public:
        Milk(std::shared_ptr<Beverage> p_beverage) : CondimentDecorator(p_beverage) {}
        String description() override { return m_beverage->description() + ", Milk"; }
        double cost() override { return 0.10 + m_beverage->cost(); }
    };

    class Whip : public CondimentDecorator
    {
    public:
        Whip(std::shared_ptr<Beverage> p_beverage) : CondimentDecorator(p_beverage) {}
        String description() override { return m_beverage->description() + ", Whip"; }
        double cost() override { return 0.10 + m_beverage->cost(); }
    };
}
#endif // !STARBUZZ_DECORATOR_H