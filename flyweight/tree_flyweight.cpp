#include "tree_flyweight.h"

#include "Catch.hpp"
#include <iostream>

using namespace tree_flyweight;
void print(String p_value)
{
    std::cout << p_value << std::endl;
}
TEST_CASE("Test_tree_flyweight", "[flywight]")
{
    SECTION("tree_flyweight")
    {
        std::vector<std::vector<int>> deciduousLocations = {{1, 1}, {33, 50}, {100, 90}};
        std::vector<std::vector<int>> coniferLocations = {{10, 87}, {24, 76}, {2, 64}};
        TreeFactory treeFactory; // creates the two flyweights
        std::shared_ptr<Tree> deciduous_tree, conifer_tree;
        try
        {
            deciduous_tree = treeFactory.get_tree("deciduous");
            conifer_tree = treeFactory.get_tree("conifer");
            std::time_t t = std::time(0); // get time now
            std::tm *now = std::localtime(&t);
            String s = deciduous_tree->is_within_range(now) ? "" : "The tree currently has no leaves\n";
            std::vector<String> deciduous_tree_output{"Deciduous tree is located at 1, 1\n" + s,
                                                      "Deciduous tree is located at 33, 50\n" + s,
                                                      "Deciduous tree is located at 100, 90\n" + s};
            std::vector<String> conifer_tree_output{"Conifer tree is located at 10, 87\n",
                                                    "Conifer tree is located at 24, 76\n",
                                                    "Conifer tree is located at 2, 64\n"};
            for (size_t i = 0; i != deciduousLocations.size(); ++i)
            {
                REQUIRE(deciduous_tree_output[i] == deciduous_tree->display(deciduousLocations[i][0], deciduousLocations[i][1]));
            }
            for (size_t i = 0; i != coniferLocations.size(); ++i)
            {
                REQUIRE(conifer_tree_output[i] == conifer_tree->display(coniferLocations[i][0], coniferLocations[i][1]));
            }
        }
        catch (...)
        {
        }
    }
}