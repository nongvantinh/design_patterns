#include "remote_control_command.h"

#include "Catch.hpp"

using namespace remote_control_command;

TEST_CASE("CommandReoteControlFixture", "[cmmand]")
{
    SECTION("TestTurningSimpleOn")
    {
        // Command Pattern Invoker
        std::shared_ptr<SimpleRemoteControl> remote = std::make_shared<SimpleRemoteControl>();

        // Command Pattern Receivers
        std::shared_ptr<Light> light = std::make_shared<Light>("Kitchen");
        std::shared_ptr<GarageDoor> garageDoor = std::make_shared<GarageDoor>("");

        // Commands for the receivers
        std::shared_ptr<LightOnCommand> light_on = std::make_shared<LightOnCommand>(light);
        std::shared_ptr<GarageDoorUpCommand> garageDoorOpen = std::make_shared<GarageDoorUpCommand>(garageDoor);

        // Passing the light on command to the invoker
        remote->set_command(light_on);
        // Simulate the button being pressed on the invoker
        REQUIRE("Kitchen light is on" == remote->button_was_pressed());

        // Passing the garage door open command to the invoker
        remote->set_command(garageDoorOpen);
        // Simulate the button being pressed on the invoker
        REQUIRE("Garage door is up" == remote->button_was_pressed());
    }
}