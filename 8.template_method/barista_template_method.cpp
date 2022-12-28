#include "barista_template_method.h"

#include "Catch.hpp"

using namespace barista_template_method;

TEST_CASE("TemplateMethodCaffeineFixture", "[template_method]")
{
    Tea tea;
    Coffee coffee;
    TeaWithHook tea_with_hook;
    CoffeeWithHook coffee_with_hook;

    std::ostringstream tea_result;
    std::ostringstream coffee_result;
    std::ostringstream coffee_with_hook_yes_result;
    std::ostringstream coffee_with_hook_no_result;
    std::ostringstream tea_with_hook_yes_result;
    std::ostringstream tea_with_hook_no_result;

    SECTION("TestTea")
    {
        tea_result << "Boiling water\n";
        tea_result << "Steeping the tea\n";
        tea_result << "Pouring into cup\n";
        tea_result << "Adding lemon\n";
        REQUIRE(tea_result.str() == tea.prepare_recipe());
    }

    SECTION("TestCoffee")
    {
        coffee_result << "Boiling water\n";
        coffee_result << "Dripping coffee through filter\n";
        coffee_result << "Pouring into cup\n";
        coffee_result << "Adding sugar and milk\n";
        REQUIRE(coffee_result.str() == coffee.prepare_recipe());
    }

    SECTION("TestCoffeeWithHook")
    {
        if (coffee_with_hook.customer_wants_condiments())
        {
            coffee_with_hook_yes_result << "Boiling water\n";
            coffee_with_hook_yes_result << "Dripping coffee through filter\n";
            coffee_with_hook_yes_result << "Pouring into cup\n";
            coffee_with_hook_yes_result << "Adding sugar and milk\n";
            REQUIRE(coffee_with_hook_yes_result.str() == coffee_with_hook.prepare_recipe());
        }
        else
        {
            coffee_with_hook_no_result << "Boiling water\n";
            coffee_with_hook_no_result << "Dripping coffee through filter\n";
            coffee_with_hook_no_result << "Pouring into cup\n";
            REQUIRE(coffee_with_hook_no_result.str() == coffee_with_hook.prepare_recipe());
        }
    }

    SECTION("TestTeaWithHook")
    {
        if (tea_with_hook.customer_wants_condiments())
        {
            tea_with_hook_yes_result << "Boiling water\n";
            tea_with_hook_yes_result << "Steeping the tea\n";
            tea_with_hook_yes_result << "Pouring into cup\n";
            tea_with_hook_yes_result << "Adding lemon\n";
            REQUIRE(tea_with_hook_yes_result.str() == tea_with_hook.prepare_recipe());
        }
        else
        {
            tea_with_hook_no_result << "Boiling water\n";
            tea_with_hook_no_result << "Steeping the tea\n";
            tea_with_hook_no_result << "Pouring into cup\n";
            REQUIRE(tea_with_hook_no_result.str() == tea_with_hook.prepare_recipe());
        }
    }
}