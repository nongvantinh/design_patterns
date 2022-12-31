#ifndef MENU_COMPOSITE_ITERATOR_H
#define MENU_COMPOSITE_ITERATOR_H
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>
#include <stack>
#include <type_traits>

namespace menu_composite_iterator
{

	using String = std::string;

	class UnsupportedOperationException : std::runtime_error
	{
	private:
		String m_message;

	public:
		UnsupportedOperationException() : std::runtime_error("") {}
		UnsupportedOperationException(String p_message) : std::runtime_error(p_message), m_message(p_message) {}
		String message() { return m_message; }
	};

	class MenuComponent
	{
	public:
		virtual String name() { return m_name; }
		virtual void set_name(String p_name) { m_name = p_name; }

		virtual String description() { return m_description; }
		virtual void set_description(String p_description) { m_description = p_description; }

		virtual bool is_vegetarian() { return m_is_vegetarian; }
		virtual void set_is_vegetarian(bool p_is_vegetarian) { m_is_vegetarian = p_is_vegetarian; }

		virtual double price() { return m_price; }
		virtual void set_price(double p_price) { m_price = p_price; }

		virtual void add(std::shared_ptr<MenuComponent> /*p_menu_component*/)
		{
			throw new UnsupportedOperationException();
		}

		virtual void remove(std::shared_ptr<MenuComponent> /*p_menu_component*/)
		{
			throw new UnsupportedOperationException();
		}

		virtual std::shared_ptr<MenuComponent> child(int /*p_index*/)
		{
			throw new UnsupportedOperationException();
		}

		virtual String print()
		{
			throw new UnsupportedOperationException();
		}

		virtual std::vector<std::shared_ptr<MenuComponent>> menu()
		{
			throw new UnsupportedOperationException();
		}

		virtual int count()
		{
			throw new UnsupportedOperationException();
		}

	private:
		String m_name;
		String m_description;
		bool m_is_vegetarian;
		double m_price;
	};

	class Menu : public MenuComponent
	{
	public:
		Menu(String p_name, String p_description)
		{
			m_name = p_name;
			m_description = p_description;
		}

		String name() { return m_name; }
		void set_name(String p_name) { m_name = p_name; }

		String description() { return m_description; }
		void set_description(String p_description) { m_description = p_description; }

		void add(std::shared_ptr<MenuComponent> p_menu_component) override
		{
			m_menu_components.push_back(p_menu_component);
		}

		void remove(std::shared_ptr<MenuComponent> p_menu_component) override
		{
			m_menu_components.erase(std::find(m_menu_components.begin(), m_menu_components.end(), p_menu_component));
		}

		std::shared_ptr<MenuComponent> child(int p_index) override
		{
			return m_menu_components[p_index];
		}

		std::vector<std::shared_ptr<MenuComponent>> menu() override
		{
			return m_menu_components;
		}

		int count() override
		{
			return m_menu_components.size();
		}

		String print() override
		{
			std::ostringstream print_output;
			print_output << "\n" + m_name;
			print_output << ", " + m_description + "\n";
			print_output << "-------------------------\n";

			for (std::shared_ptr<MenuComponent> menu_component : m_menu_components)
			{
				print_output << menu_component->print();
			}

			return print_output.str();
		}

	private:
		std::vector<std::shared_ptr<MenuComponent>> m_menu_components;
		String m_name;
		String m_description;
	};

	class MenuItem : public MenuComponent
	{
	public:
		MenuItem(String p_name, String p_description,
				 bool p_vegetarian, double p_price)
		{
			m_name = p_name;
			m_description = p_description;
			m_is_vegetarian = p_vegetarian;
			m_price = p_price;
		}

		String name() override { return m_name; }
		void set_name(String p_name) override { m_name = p_name; }

		String description() override { return m_description; }
		void set_description(String p_description) override { m_description = p_description; }

		bool is_vegetarian() override { return m_is_vegetarian; }
		void set_is_vegetarian(bool p_is_vegetarian) override { m_is_vegetarian = p_is_vegetarian; }

		double price() override { return m_price; }
		void set_price(double p_price) override { m_price = p_price; }

		String print() override
		{
			std::ostringstream print_output;
			print_output << "\t" << name();
			if (is_vegetarian())
			{
				print_output << " (v) ";
			}
			print_output << ", $" << price() << "\n";
			print_output << "\t\t--" << description() << "\n";

			return print_output.str();
		}

	private:
		String m_name;
		String m_description;
		bool m_is_vegetarian;
		double m_price;
	};

	class Waitress
	{
	public:
		Waitress(std::shared_ptr<MenuComponent> p_all_menus)
		{
			m_all_menus = p_all_menus;
		}

		String print_menu() { return m_all_menus->print(); }

	private:
		std::shared_ptr<MenuComponent> m_all_menus;
	};

	template <typename T>
	class Iterator
	{
	public:
		virtual bool has_next() const = 0;
		virtual std::shared_ptr<T> next() = 0;
	};

	class CompositeIterator : public Iterator<MenuComponent>
	{
		std::stack<Iterator<std::shared_ptr<MenuComponent>>> m_stack;

		CompositeIterator(Iterator<std::shared_ptr<MenuComponent>> p_iterator)
		{
			m_stack.push(p_iterator);
		}

		std::shared_ptr<MenuComponent> next() override
		{
			if (hasNext())
			{
				auto iterator = m_stack.top();
				auto component = iterator.next();
				m_stack.push(component.createIterator());
				return component->;
			}
			else
			{
				return nullptr;
			}
		}

		bool hasNext()
		{
			if (m_stack.empty())
			{
				return false;
			}
			else
			{
				Iterator<std::shared_ptr<MenuComponent>> iterator = m_stack.top();
				if (!iterator->hasNext())
				{
					m_stack.pop();
					return hasNext();
				}
				else
				{
					return true;
				}
			}
		}

		/*
		 * No longer needed as of Java 8
		 *
		 * (non-Javadoc)
		 * @see java.util.Iterator#remove()
		 *
		public void remove() {
			throw new UnsupportedOperationException();
		}
		*/
	}

}
#endif // !MENU_COMPOSITE_ITERATOR_H