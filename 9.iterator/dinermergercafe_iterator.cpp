#include "dinermergercafe_iterator.h"

#include "Catch.hpp"

using namespace dinermergercafe_iterator;
const int DinerMenu::MAX_ITEMS = 6;

UnSupportedOperationException::UnSupportedOperationException() : std::runtime_error(""), m_message("") {}
UnSupportedOperationException::UnSupportedOperationException(String p_message) : std::runtime_error(p_message), m_message(p_message) {}
String UnSupportedOperationException::get_message() { return m_message; }

CafeMenu::CafeMenu()
{
	insert_item("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99);
	insert_item("Soup of the Day", "A cup of the soup of the day, with a side salad", false, 3.69);
	insert_item("Burrito", "A large burrito, with whole pinto beans, salsa, guacamole", true, 4.29);
}

// added the index integer to be the Hashtable key value
void CafeMenu::insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price)
{
	std::shared_ptr<MenuItem> menu_item = std::make_shared<MenuItem>(p_name, p_description, p_is_vegetarian, p_price);
	m_menu_items[p_name] = menu_item;
}

std::map<String, std::shared_ptr<MenuItem>> CafeMenu::get_menu_items() { return m_menu_items; }
std::shared_ptr<Iterator> CafeMenu::create_iterator() { return std::make_shared<CafeMenuIterator>(m_menu_items); }

DinerMenu::DinerMenu() :m_number_of_items(0), m_menu_items(MAX_ITEMS)
{
	insert_item("Vegetarian BLT", "(Fakin') Bacon with lettuce & tomato on whole wheat", true, 2.99);
	insert_item("BLT", "Bacon with lettuce & tomato on whole wheat", false, 2.99);
	insert_item("Soup of the day", "Soup of the day, with a side of potato salad", false, 3.29);
	insert_item("Hotdog", "A hot dog with saurkraut, relish, onions, topped with cheese", false, 3.05);
	insert_item("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99);
	insert_item("Pasta", "Spaghetti with Marina Sauce and a slice of sourdough bread", true, 3.89);
}

void DinerMenu::insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price)
{
	std::shared_ptr<MenuItem> menu_item = std::make_shared<MenuItem>(p_name, p_description, p_is_vegetarian, p_price);
	if (MAX_ITEMS <= m_number_of_items)
	{
		throw std::runtime_error("Sorry, menu is full! Can't add item to menu");
	}
	else
	{
		m_menu_items[m_number_of_items++] = menu_item;
	}
}
std::vector<std::shared_ptr<MenuItem>> DinerMenu::get_menu_items() { return m_menu_items; }

std::shared_ptr<Iterator> DinerMenu::create_iterator() { return std::make_shared<DinerMenuIterator>(m_menu_items); }

PancakeHouseMenu::PancakeHouseMenu()
{
	insert_item("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99);
	insert_item("Regular Pancake Breakfast", "Pancakes with fried eggs, and sausage", false, 2.99);
	insert_item("Blueberry Pancakes", "Pancakes made with fresh blueberries", true, 3.49);
	insert_item("Waffles", "Waffles, with your choice of blueberries or strawberries", true, 3.59);
}

void PancakeHouseMenu::insert_item(String p_name, String p_description, bool p_is_vegetarian, double p_price)
{
	std::shared_ptr<MenuItem> menu_item = std::make_shared<MenuItem>(p_name, p_description, p_is_vegetarian, p_price);
	m_menu_items.push_back(menu_item);
}

std::vector<std::shared_ptr<MenuItem>> PancakeHouseMenu::get_menu_items() { return m_menu_items; }
std::shared_ptr<Iterator> PancakeHouseMenu::create_iterator() { return std::make_shared<PancakeHouseIterator>(m_menu_items); }

String MenuItem::get_name() { return m_name; }
void MenuItem::set_name(String p_name) { m_name = p_name; }

String MenuItem::get_description() { return m_description; }
void MenuItem::set_description(String p_description) { m_description = p_description; }

bool MenuItem::is_vegetarian() { return m_is_vegetarian; }
void MenuItem::set_is_vegetarian(bool p_is_vegetarian) { m_is_vegetarian = p_is_vegetarian; }

double MenuItem::get_price() { return m_price; }
void MenuItem::set_price(double p_price) { m_price = p_price; }

MenuItem::MenuItem(String p_name, String p_description, bool p_is_vegetarian, double p_price)
	: m_name(p_name), m_description(p_description), m_is_vegetarian(p_is_vegetarian), m_price(p_price) {}

CafeMenuIterator::CafeMenuIterator(std::map<String, std::shared_ptr<MenuItem>> p_menu_items)
	: m_menu_items(p_menu_items), m_keys(p_menu_items.size()), m_position(0)
{
	for (auto& item : p_menu_items)
	{
		m_keys[m_position++] = item.first;
	}
	m_position = 0;
}
bool CafeMenuIterator::has_next() const { return m_position < m_menu_items.size(); }
std::shared_ptr<MenuItem> CafeMenuIterator::next() { return m_menu_items[m_keys[m_position++]]; }

DinerMenuIterator::DinerMenuIterator(std::vector<std::shared_ptr<MenuItem>> p_items) : m_items(p_items) {}
bool DinerMenuIterator::has_next() const { return m_position < m_items.size() && m_items[m_position]; }
std::shared_ptr<MenuItem> DinerMenuIterator::next() { return m_items[m_position++]; }
void DinerMenuIterator::remove()
{
	if (m_position <= 0)
	{
		throw UnSupportedOperationException("You can't remove an item until you've done at least one next()");
	}
	if (nullptr != m_items[m_position - 1])
	{
		for (size_t i = m_position - 1; i < (m_items.size() - 1); i++)
		{
			m_items[i] = m_items[i + 1];
		}
		m_items[m_items.size() - 1] = nullptr;
	}
}

PancakeHouseIterator::PancakeHouseIterator(std::vector<std::shared_ptr<MenuItem>> p_menu_items) : m_menu_items(p_menu_items) {}
bool PancakeHouseIterator::has_next() const { return m_position < m_menu_items.size() && m_menu_items[m_position]; }
std::shared_ptr<MenuItem> PancakeHouseIterator::next() { return m_menu_items[m_position++]; }

Waitress::Waitress(std::shared_ptr<Menu> p_pancake_house_menu, std::shared_ptr<Menu> p_dinner_menu, std::shared_ptr<Menu> p_cafe_menu)
	: m_pancake_house_menu(p_pancake_house_menu), m_diner_menu(p_dinner_menu), m_cafe_menu(p_cafe_menu) {}

String Waitress::print_menu()
{
	std::ostringstream oss;

	std::shared_ptr<Iterator> pancake_iterator = m_pancake_house_menu->create_iterator();
	std::shared_ptr<Iterator> dinner_iterator = m_diner_menu->create_iterator();
	std::shared_ptr<Iterator> cafe_iterator = m_cafe_menu->create_iterator();
	oss << "MENU\n----\nBREAKFAST\n";
	oss << print_menu(pancake_iterator);
	oss << "\nLUNCH\n";
	oss << print_menu(dinner_iterator);
	oss << "\nDinner\n";
	oss << print_menu(cafe_iterator);

	return oss.str();
}

String Waitress::print_menu(std::shared_ptr<Iterator> p_iterator)
{
	std::ostringstream oss;

	while (p_iterator->has_next())
	{
		std::shared_ptr<MenuItem> menu_item = p_iterator->next();

		oss << menu_item->get_name() << ", ";
		oss << menu_item->get_price() << " -- ";
		oss << menu_item->get_description() << "\n";
	}

	return oss.str();
}

String Waitress::print_vegetarian_menu()
{
	std::ostringstream oss;
	oss << "\nVEGETARIAN MENU\n---------------";
	oss << print_vegetarian_menu(m_pancake_house_menu->create_iterator());
	oss << print_vegetarian_menu(m_diner_menu->create_iterator());
	oss << print_vegetarian_menu(m_cafe_menu->create_iterator());
	return oss.str();
}

bool Waitress::is_item_vegetarian(String p_name)
{
	std::shared_ptr<Iterator> pancakeIterator = m_pancake_house_menu->create_iterator();
	if (is_vegetarian(p_name, pancakeIterator))
	{
		return true;
	}
	std::shared_ptr<Iterator> dinerIterator = m_diner_menu->create_iterator();
	if (is_vegetarian(p_name, dinerIterator))
	{
		return true;
	}
	std::shared_ptr<Iterator> cafeIterator = m_cafe_menu->create_iterator();
	if (is_vegetarian(p_name, cafeIterator))
	{
		return true;
	}
	return false;
}

String Waitress::print_vegetarian_menu(std::shared_ptr<Iterator> iterator)
{
	std::ostringstream oss;
	while (iterator->has_next())
	{
		std::shared_ptr<MenuItem> menuItem = iterator->next();
		if (menuItem->is_vegetarian())
		{
			oss << menuItem->get_name() << ", ";
			oss << menuItem->get_price() << " -- ";
			oss << menuItem->get_description();
		}
	}
	return oss.str();
}

bool Waitress::is_vegetarian(String p_name, std::shared_ptr<Iterator> iterator)
{
	while (iterator->has_next())
	{
		std::shared_ptr<MenuItem> menuItem = iterator->next();
		if (menuItem->get_name() == p_name)
		{
			if (menuItem->is_vegetarian())
			{
				return true;
			}
		}
	}
	return false;
}
#include <iostream>
TEST_CASE("TestWaitressPrintMenu", "[iterator]")
{
	SECTION("TestWaitressPrintMenu")
	{
		std::shared_ptr<PancakeHouseMenu> pancake_house_menu = std::make_shared<PancakeHouseMenu>();
		std::shared_ptr<DinerMenu> dinner_menu = std::make_shared<DinerMenu>();
		std::shared_ptr<CafeMenu> cafe_menu = std::make_shared<CafeMenu>();

		std::shared_ptr<Waitress> waitress = std::make_shared<Waitress>(pancake_house_menu, dinner_menu, cafe_menu);
		std::ostringstream oss;
		oss << "MENU\n----\nBREAKFAST\n";
		oss << "K&B's Pancake Breakfast, 2.99 -- Pancakes with scrambled eggs, and toast\n";
		oss << "Regular Pancake Breakfast, 2.99 -- Pancakes with fried eggs, and sausage\n";
		oss << "Blueberry Pancakes, 3.49 -- Pancakes made with fresh blueberries\n";
		oss << "Waffles, 3.59 -- Waffles, with your choice of blueberries or strawberries\n";
		oss << "\nLUNCH\n";
		oss << "Vegetarian BLT, 2.99 -- (Fakin') Bacon with lettuce & tomato on whole wheat\n";
		oss << "BLT, 2.99 -- Bacon with lettuce & tomato on whole wheat\n";
		oss << "Soup of the day, 3.29 -- Soup of the day, with a side of potato salad\n";
		oss << "Hotdog, 3.05 -- A hot dog with saurkraut, relish, onions, topped with cheese\n";
		oss << "Steamed Veggies and Brown Rice, 3.99 -- Steamed vegetables over brown rice\n";
		oss << "Pasta, 3.89 -- Spaghetti with Marina Sauce and a slice of sourdough bread\n";
		oss << "\nDinner\n";
		oss << "Burrito, 4.29 -- A large burrito, with whole pinto beans, salsa, guacamole\n";
		oss << "Soup of the Day, 3.69 -- A cup of the soup of the day, with a side salad\n";
		oss << "Veggie Burger and Air Fries, 3.99 -- Veggie burger on a whole wheat bun, ";
		oss << "lettuce, tomato, and fries\n";

		//std::cout << oss.str() << std::endl;
		REQUIRE(oss.str() == waitress->print_menu());
	}
}