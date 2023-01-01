#include "undo.h"

#include "Catch.hpp"

#include <iostream>

using namespace undo;
void print(String v)
{
    std::cout << v << std::endl;
}
TEST_CASE("", "[]")
{
    SECTION("")
    {
        std::shared_ptr<RemoteControlWithUndo> remote_control = std::make_shared<RemoteControlWithUndo>();
        std::shared_ptr<Light> living_room_light = std::make_shared<Light>("Living Room");
        std::shared_ptr<LightOnCommand> living_room_light_on = std::make_shared<LightOnCommand>(living_room_light);
        std::shared_ptr<LightOffCommand> living_room_light_off = std::make_shared<LightOffCommand>(living_room_light);

        remote_control->set_command(0, living_room_light_on, living_room_light_off);

        remote_control->on_button_was_pushed(0);
        remote_control->off_button_was_pushed(0);
        print(remote_control->to_string());
        remote_control->undo_button_was_pushed();
        remote_control->off_button_was_pushed(0);
        remote_control->on_button_was_pushed(0);
        print(remote_control->to_string());
        remote_control->undo_button_was_pushed();

        std::shared_ptr<CeilingFan> m_ceiling_fan = std::make_shared<CeilingFan>("Living Room");
        std::shared_ptr<CeilingFanMediumCommand> ceiling_fan_medium = std::make_shared<CeilingFanMediumCommand>(m_ceiling_fan);
        std::shared_ptr<CeilingFanHighCommand> ceiling_fan_high = std::make_shared<CeilingFanHighCommand>(m_ceiling_fan);
        std::shared_ptr<CeilingFanOffCommand> ceiling_fan_off = std::make_shared<CeilingFanOffCommand>(m_ceiling_fan);

        remote_control->set_command(0, ceiling_fan_medium, ceiling_fan_off);
        remote_control->set_command(1, ceiling_fan_high, ceiling_fan_off);

        remote_control->on_button_was_pushed(0);
        remote_control->off_button_was_pushed(0);
        print(remote_control->to_string());
        remote_control->undo_button_was_pushed();

        remote_control->on_button_was_pushed(1);
        print(remote_control->to_string());
        remote_control->undo_button_was_pushed();
        // REQUIRE(" " == " ");
    }
}