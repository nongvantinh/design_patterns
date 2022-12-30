#ifndef DINERMERGERCAFE_ITERATOR_H
#define DINERMERGERCAFE_ITERATOR_H
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <sstream>
#include <stdexcept>
#include <map>

namespace dinermergercafe_iterator
{
	using String = std::string;
	class Iterator;
	class MenuItem;

	class UnSupportedOperationException : std::runtime_error
	{
	public:
		UnSupportedOperationException();
		UnSupportedOperationException(String p_message);
		String get_message();

	private:
		String m_message;
	};

	class Menu
	{
	public:
		virtual std::shared_ptr<Iterator> create_iterator() = 0;
	};

	class CafeMenu : public Menu
	{
	public:
		CafeMenu();
		// added the index integer to be the Hashtable key value
		void insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price);

		std::map<String, std::shared_ptr<MenuItem>> get_menu_items();
		std::shared_ptr<Iterator> create_iterator() override;

	private:
		std::map<String, std::shared_ptr<MenuItem>> m_menu_items;
	};

	class DinerMenu : public Menu
	{
	public:
		DinerMenu();

		void insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price);
		std::vector<std::shared_ptr<MenuItem>> get_menu_items();
		std::shared_ptr<Iterator> create_iterator();

	private:
		int m_number_of_items;
		static const int MAX_ITEMS;
		std::vector<std::shared_ptr<MenuItem>> m_menu_items;
	};

	class PancakeHouseMenu : public Menu
	{
	public:
		PancakeHouseMenu();
		void insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price);
		std::vector<std::shared_ptr<MenuItem>> get_menu_items();
		std::shared_ptr<Iterator> create_iterator() override;

	private:
		std::vector<std::shared_ptr<MenuItem>> m_menu_items;
	};

	class MenuItem
	{
	public:
		String get_name();
		void set_name(String p_name);

		String get_description();
		void set_description(String p_description);

		bool is_vegetarian();
		void set_is_vegetarian(bool p_is_vegetarian);

		double get_price();
		void set_price(double p_price);

		MenuItem(String p_name, String p_description, bool p_is_vegetarian, double p_price);

	private:
		String m_name;
		String m_description;
		bool m_is_vegetarian;
		double m_price;
	};

	class Iterator
	{
	public:
		virtual bool has_next() const = 0;
		virtual std::shared_ptr<MenuItem> next() = 0;
	};

	class CafeMenuIterator : public Iterator
	{
	public:
		CafeMenuIterator(std::map<String, std::shared_ptr<MenuItem>> p_menu_items);
		bool has_next() const;
		std::shared_ptr<MenuItem> next();

	private:
		std::map<String, std::shared_ptr<MenuItem>> m_menu_items;
		std::vector<String> m_keys;
		size_t m_position;
	};

	class DinerMenuIterator : public Iterator
	{
	public:
		DinerMenuIterator(std::vector<std::shared_ptr<MenuItem>> p_items);
		bool has_next() const;
		std::shared_ptr<MenuItem> next();
		void remove();

	private:
		std::vector<std::shared_ptr<MenuItem>> m_items;
		size_t m_position = 0;
	};

	class PancakeHouseIterator : public Iterator
	{
	public:
		PancakeHouseIterator(std::vector<std::shared_ptr<MenuItem>> p_menu_items);
		bool has_next() const;
		std::shared_ptr<MenuItem> next();

	private:
		std::vector<std::shared_ptr<MenuItem>> m_menu_items;
		size_t m_position = 0;
	};

	class Waitress
	{
	public:
		Waitress(std::shared_ptr<Menu> p_pancake_house_menu, std::shared_ptr<Menu> p_dinner_menu, std::shared_ptr<Menu> p_cafe_menu);

		String print_menu();

		String print_menu(std::shared_ptr<Iterator> p_iterator);
		String print_vegetarian_menu();

		bool is_item_vegetarian(String p_name);

		String print_vegetarian_menu(std::shared_ptr<Iterator> iterator);

		bool is_vegetarian(String p_name, std::shared_ptr<Iterator> iterator);

	private:
		std::shared_ptr<Menu> m_pancake_house_menu;
		std::shared_ptr<Menu> m_diner_menu;
		std::shared_ptr<Menu> m_cafe_menu;
	};
}
#endif // !DINERMERGERCAFE_ITERATOR_H