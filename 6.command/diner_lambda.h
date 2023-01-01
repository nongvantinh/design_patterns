#ifndef DINER_LAMBDA_H
#define DINER_LAMBDA_H
#include <string>
#include <memory>

namespace diner_lambda
{
	using String = std::string;

	class Order
	{
	public:
		virtual String order_up() = 0;
	};

	class Cook
	{
	public:
		Cook() {}
		String make_burger() { return "Making a burger"; }
		String make_fries() { return "Making fries"; }
	};

	class Customer
	{
	public:
		Customer(std::shared_ptr<Waitress> p_waitress, std::shared_ptr<Cook> p_cook)
		{
			m_waitress = p_waitress;
			m_cook = p_cook;
		}
		String create_order()
		{
			// Order order = ()->
			// {
			// 	m_cook.make_burger();
			// 	m_cook.make_fries();
			// };
		}
		String hungry() { return m_waitress->take_order(m_order); }

	private:
		std::shared_ptr<Waitress> m_waitress;
		std::shared_ptr<Cook> m_cook;
		std::shared_ptr<Order> m_order;
	};

	class Waitress
	{
	public:
		Waitress() {}
		String take_order(std::shared_ptr<Order> p_order)
		{
			m_oder = p_order;
			return m_oder->order_up();
		}

	private:
		std::shared_ptr<Order> m_oder;
	};
}
#endif // !DINER_LAMBDA_H