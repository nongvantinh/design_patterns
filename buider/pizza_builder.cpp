#include "pizza_builder.h"

#include "Catch.hpp"
#include <iostream>

using namespace pizza_builder;
void print(String v)
{
    std::cout << v << std::endl;
}

TEST_CASE("PizzaDirector", "[builder]")
{
        // Fluent Interface pattern (return the builder each time so we can string the calls together)
        // Builder pattern (we have two different builders so the "same construction process can create
        //   different representations").
        // Builder is a solution to the telescoping constructor anti-pattern, where we have multiple,
        //   complex constructor methods with various args for all various combinations of options
        //   in construction options.

        // in this example main() is the construct() method
        SECTION("")
        {
            // Could hand builders to PizzaStore which would take the customer's order,
            //   and call appropriate methods for each topping, then call the
            //   pizza methods to prep and return to the customer.
            std::shared_ptr<PizzaBuilder> veggie_builder = std::make_shared<VeggieLoversPizzaBuilder>();
            // The PizzaDirector calls the methods in the correct order to
            // build a veggiePizza.
            std::shared_ptr<Pizza> veggie = veggie_builder->add_sauce()->add_cheese()->add_olives()->add_tomatoes()->add_sausage()->build();
            veggie->prepare();
            veggie->bake();
            veggie->cut();
            veggie->box();
            print(veggie->to_string());

            std::shared_ptr<PizzaBuilder> meat_builder = std::make_shared<MeatLoversPizzaBuilder>();
            // The PizzaDirector calls the methods in the correct order to build
            // a meat lovers Pizza
            std::shared_ptr<Pizza> meat = meat_builder->add_sauce()->add_tomatoes()->add_cheese()->add_sausage()->add_pepperoni()->build();
            meat->prepare();
            meat->bake();
            meat->cut();
            meat->box();
            print(meat->to_string());
        }
}