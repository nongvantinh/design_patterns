#ifndef STARBUZZ_WITH_SIZE_DECORATOR_H
#define STARBUZZ_WITH_SIZE_DECORATOR_H
#include <string>
#include <memory>

using String = std::string;

namespace starbuzz_with_size_decorator
{
    enum class BeverageSize
    {
        TALL,
        GRANDE,
        VENTI
    };

    class Beverage
    {
    public:
        Beverage() : m_size(BeverageSize::TALL) {}
        Beverage(BeverageSize p_size) : m_size(p_size) {}
        BeverageSize size() { return m_size; }
        void set_size(BeverageSize p_size) { m_size = p_size; }

        virtual double cost() = 0;
        virtual String description() { return "Unknown Beverage"; }

    private:
        BeverageSize m_size;
    };

    class DarkRoast : public Beverage
    {
    public:
        DarkRoast() : Beverage() {}
        DarkRoast(BeverageSize p_size) : Beverage(p_size) {}
        double cost() override { return 0.99; }
        String description() override { return "Dark Roast Coffee"; }
    };

    class Decaf : public Beverage
    {
    public:
        Decaf() : Beverage() {}
        Decaf(BeverageSize p_size) : Beverage(p_size) {}
        double cost() override { return 1.05; }
        String description() override { return "Decaf Coffee"; }
    };

    class Espresso : public Beverage
    {
    public:
        Espresso() : Beverage() {}
        Espresso(BeverageSize p_size) : Beverage(p_size) {}
        double cost() override { return 1.99; }
        String description() override { return "Espresso"; }
    };

    class HouseBlend : public Beverage
    {
    public:
        HouseBlend() : Beverage() {}
        HouseBlend(BeverageSize p_size) : Beverage(p_size) {}
        double cost() override { return 0.89; }
        String description() override { return "House Blend Coffee"; }
    };

    class CondimentDecorator : public Beverage
    {
    public:
        String description() override = 0;
        double cost() override = 0;

    protected:
        CondimentDecorator() : Beverage(), m_beverage(nullptr) {}
        CondimentDecorator(std::shared_ptr<Beverage> p_beverage) : Beverage(p_beverage->size()), m_beverage(p_beverage) {}
        CondimentDecorator(std::shared_ptr<Beverage> p_beverage, BeverageSize p_size) : Beverage(p_size), m_beverage(p_beverage) {}

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
        double cost() override { return price(size()) + m_beverage->cost(); }

    private:
        double price(BeverageSize p_size)
        {
            switch (p_size)
            {
            case BeverageSize::TALL:
                return 0.10;
            case BeverageSize::GRANDE:
                return 0.15;
            case BeverageSize::VENTI:
                return 0.20;
            default:
                return 0.20;
            }
        }
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
#endif // !STARBUZZ_WITH_SIZE_DECORATOR_H