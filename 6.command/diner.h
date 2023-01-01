#ifndef DINER_H
#define DINER_H
#include <string>
#include <memory>

namespace diner
{
    using String = std::string;

    class Order
    {
    public:
        Order() {}
        String make_burger() { return "Making a burger"; }
        String make_fries() { return "Making fries"; }
        virtual String order_up() = 0;
    };

    class BurgerAndFriesOrder : public Order
    {
    public:
        BurgerAndFriesOrder(std::shared_ptr<Order> p_order)
        {
            m_order = p_order;
        }

        String order_up() override
        {
            m_order->make_burger();
            m_order->make_fries();
        }

    private:
        std::shared_ptr<Order> m_order;
    };

    class Customer
    {
    private:
        std::shared_ptr<Waitress> m_waitress;
        std::shared_ptr<Order> m_order;

    public:
        Customer(std::shared_ptr<Waitress> p_waitress)
        {
            m_waitress = p_waitress;
        }

        String create_order(std::shared_ptr<Order> p_order)
        {
            m_order = p_order;
        }

        String hungry()
        {
            return m_waitress->take_order(m_order);
        }
    };

    class Waitress
    {
    public:
        Waitress() {}

        String take_order(std::shared_ptr<Order> p_order)
        {
            m_order = p_order;
            m_order->order_up();
        }

    private:
        std::shared_ptr<Order> m_order;
    };
}
#endif // !DINER_H