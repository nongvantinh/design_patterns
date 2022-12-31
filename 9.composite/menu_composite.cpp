#include "menu_composite.h"

#include "Catch.hpp"

using namespace menu_composite;

TEST_CASE("CompositeMenuFixture", "[composite]")
{
    std::shared_ptr<MenuComponent> pancake_house_menu = std::make_shared<Menu>("PANCAKE HOUSE MENU", "Breakfast");
    std::shared_ptr<MenuComponent> dinner_menu = std::make_shared<Menu>("DINNER MENU", "Lunch");
    std::shared_ptr<MenuComponent> cafe_menu = std::make_shared<Menu>("CAFE MENU", "Dinner");
    std::shared_ptr<MenuComponent> dessert_menu = std::make_shared<Menu>("DESSERT MENU", "Dessert of course");
    // create the all menus to act as the container for the menus
    std::shared_ptr<MenuComponent> all_menus = std::make_shared<Menu>("ALL MENUS", "All menus combined");
    // instantiate the waitress passing in all the menus
    std::shared_ptr<Waitress> waitress = std::make_shared<Waitress>(all_menus);

    {
        // add the menus to the All Menus menu
        all_menus->add(pancake_house_menu);
        all_menus->add(dinner_menu);
        all_menus->add(cafe_menu);

        // breakfast menu
        pancake_house_menu->add(std::make_shared<MenuItem>("K&B's Pancake Breakfast",
                                                         "Pancakes with scrambled eggs, and toast",
                                                         true,
                                                         2.99));
        pancake_house_menu->add(std::make_shared<MenuItem>("Regular Pancake Breakfast",
                                                         "Pancakes with fried eggs, and sausage",
                                                         false,
                                                         2.99));
        pancake_house_menu->add(std::make_shared<MenuItem>("Blueberry Pancakes",
                                                         "Pancakes made with fresh blueberries",
                                                         true,
                                                         3.49));
        pancake_house_menu->add(std::make_shared<MenuItem>("Waffles",
                                                         "Waffles, with your choice of blueberries or strawberries",
                                                         true,
                                                         3.59));

        // dinner menu
        dinner_menu->add(std::make_shared<MenuItem>("Vegetarian BLT",
                                                   "(Fakin') Bacon with lettuce & tomato on whole wheat",
                                                   true,
                                                   2.99));
        dinner_menu->add(std::make_shared<MenuItem>("Soup of the day",
                                                   "Soup of the day, with a side of potato salad",
                                                   false,
                                                   3.29));
        dinner_menu->add(std::make_shared<MenuItem>("Hotdog",
                                                   "A hot dog with saurkraut, relish, onions, topped with cheese",
                                                   false,
                                                   3.05));
        dinner_menu->add(std::make_shared<MenuItem>("Steamed Veggies and Brown Rice",
                                                   "Steamed vegetables over brown rice",
                                                   true,
                                                   3.99));

        // cafe menu
        cafe_menu->add(std::make_shared<MenuItem>("Veggie Burger and Air Fries",
                                                 "Veggie burger on a whole wheat bun, lettuce, tomato, and fries",
                                                 true, 3.99));
        cafe_menu->add(std::make_shared<MenuItem>("Soup of the Day",
                                                 "A cup of the soup of the day, with a side salad",
                                                 false, 3.69));
        cafe_menu->add(std::make_shared<MenuItem>("Burrito",
                                                 "A large burrito, with whole pinto beans, salsa, guacamole",
                                                 true, 4.29));

        // add the dessert as a child node off the dinner menu
        dinner_menu->add(dessert_menu);

        // dinner menu
        dessert_menu->add(std::make_shared<MenuItem>("Apple Pie",
                                                    "Apple pie with a flakey crust, topped with vanilla icecream",
                                                    true, 1.59));
        dessert_menu->add(std::make_shared<MenuItem>("Chocolate Cake",
                                                    "Creamy chololate cake with caramel icing",
                                                    true, 2.59));
        dessert_menu->add(std::make_shared<MenuItem>("Icecream Pie",
                                                    "Icecream pie with crunchy crust",
                                                    true, 1.50));
    }

    SECTION("TestWaitressPrint")
    {
        std::ostringstream test_output;

        test_output << "\nALL MENUS, All menus combined\n";
        test_output << "-------------------------\n";
        test_output << "\nPANCAKE HOUSE MENU, Breakfast\n";
        test_output << "-------------------------\n";
        test_output << "\tK&B's Pancake Breakfast (v) , $2.99\n";
        test_output << "\t\t--Pancakes with scrambled eggs, and toast\n";
        test_output << "\tRegular Pancake Breakfast, $2.99\n";
        test_output << "\t\t--Pancakes with fried eggs, and sausage\n";
        test_output << "\tBlueberry Pancakes (v) , $3.49\n";
        test_output << "\t\t--Pancakes made with fresh blueberries\n";
        test_output << "\tWaffles (v) , $3.59\n";
        test_output << "\t\t--Waffles, with your choice of blueberries or strawberries\n";
        test_output << "\nDINNER MENU, Lunch\n";
        test_output << "-------------------------\n";
        test_output << "\tVegetarian BLT (v) , $2.99\n";
        test_output << "\t\t--(Fakin') Bacon with lettuce & tomato on whole wheat\n";
        test_output << "\tSoup of the day, $3.29\n";
        test_output << "\t\t--Soup of the day, with a side of potato salad\n";
        test_output << "\tHotdog, $3.05\n";
        test_output << "\t\t--A hot dog with saurkraut, relish, onions, topped with cheese\n";
        test_output << "\tSteamed Veggies and Brown Rice (v) , $3.99\n";
        test_output << "\t\t--Steamed vegetables over brown rice\n";
        test_output << "\nDESSERT MENU, Dessert of course\n";
        test_output << "-------------------------\n";
        test_output << "\tApple Pie (v) , $1.59\n";
        test_output << "\t\t--Apple pie with a flakey crust, topped with vanilla icecream\n";
        test_output << "\tChocolate Cake (v) , $2.59\n";
        test_output << "\t\t--Creamy chololate cake with caramel icing\n";
        test_output << "\tIcecream Pie (v) , $1.5\n";
        test_output << "\t\t--Icecream pie with crunchy crust\n";
        test_output << "\nCAFE MENU, Dinner\n";
        test_output << "-------------------------\n";
        test_output << "\tVeggie Burger and Air Fries (v) , $3.99\n";
        test_output << "\t\t--Veggie burger on a whole wheat bun, lettuce, tomato, and fries\n";
        test_output << "\tSoup of the Day, $3.69\n";
        test_output << "\t\t--A cup of the soup of the day, with a side salad\n";
        test_output << "\tBurrito (v) , $4.29\n";
        test_output << "\t\t--A large burrito, with whole pinto beans, salsa, guacamole\n";

        REQUIRE(test_output.str() == waitress->print_menu());
    }
}
