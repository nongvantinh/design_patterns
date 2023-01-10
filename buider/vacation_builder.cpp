#include "vacation_builder.h"

#include "Catch.hpp"
#include <iostream>

using namespace vacation_builder;
void print(String v)
{
    std::cout << v << std::endl;
}

TEST_CASE("VacationDirector", "[builder]"){

    SECTION(""){
        std::shared_ptr<VacationBuilder> outdoorsy_vacation_builder = std::make_shared<OutdoorsVacationBuilder>();
std::shared_ptr<Vacation> outdoorsy_vacation = outdoorsy_vacation_builder
                                                   ->add_accommodation("Two person tent", 2020, 7, 1, 5, 34)
                                                   ->add_event("Beach")
                                                   ->add_accommodation("Two person tent")
                                                   ->add_event("Mountains")
                                                   ->get_vacation();
print(outdoorsy_vacation->to_string());

std::shared_ptr<VacationBuilder> cityVacationBuilder = std::make_shared<CityVacationBuilder>();
std::shared_ptr<Vacation> city_vacation = cityVacationBuilder
                                              ->add_accommodation("Grand Facadian", 2020, 8, 1, 5, 0)
                                              ->add_accommodation("Hotel Commander", 2020, 8, 6, 2, 0)
                                              ->add_event("Cirque du Soleil")
                                              ->get_vacation();
print(city_vacation->to_string());
}
}
;
