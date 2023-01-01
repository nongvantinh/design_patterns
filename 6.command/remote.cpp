#include "remote.h"

#include "Catch.hpp"

using namespace remote;

TEST_CASE("", "[]")
{
    SECTION("")
    {
        std::shared_ptr<RemoteControl> remote_control = std::make_shared<RemoteControl>();

        std::shared_ptr<Light> living_room_light = std::make_shared<Light>("Living Room");
        std::shared_ptr<Light> kitchen_light = std::make_shared<Light>("Kitchen");
        std::shared_ptr<CeilingFan> ceiling_fan = std::make_shared<CeilingFan>("Living Room");
        std::shared_ptr<GarageDoor> garage_door = std::make_shared<GarageDoor>("Garage");
        std::shared_ptr<Stereo> stereo = std::make_shared<Stereo>("Living Room");
        std::shared_ptr<LightOnCommand> living_room_light_on = std::make_shared<LightOnCommand>(living_room_light);
        std::shared_ptr<LightOffCommand> living_room_light_off = std::make_shared<LightOffCommand>(living_room_light);
        std::shared_ptr<LightOnCommand> kitchen_light_on = std::make_shared<LightOnCommand>(kitchen_light);
        std::shared_ptr<LightOffCommand> kitchen_light_off = std::make_shared<LightOffCommand>(kitchen_light);
        std::shared_ptr<CeilingFanOnCommand> ceiling_fan_on = std::make_shared<CeilingFanOnCommand>(ceiling_fan);
        std::shared_ptr<CeilingFanOffCommand> ceiling_fan_off = std::make_shared<CeilingFanOffCommand>(ceiling_fan);
        std::shared_ptr<GarageDoorUpCommand> garage_door_up = std::make_shared<GarageDoorUpCommand>(garage_door);
        std::shared_ptr<GarageDoorDownCommand> garage_door_down = std::make_shared<GarageDoorDownCommand>(garage_door);
        std::shared_ptr<StereoOnWithCDCommand> stereo_on_with_cd = std::make_shared<StereoOnWithCDCommand>(stereo);
        std::shared_ptr<StereoOffCommand> stereo_off = std::make_shared<StereoOffCommand>(stereo);
        remote_control->set_command(0, living_room_light_on, living_room_light_off);
        remote_control->set_command(1, kitchen_light_on, kitchen_light_off);
        remote_control->set_command(2, ceiling_fan_on, ceiling_fan_off);
        remote_control->set_command(3, stereo_on_with_cd, stereo_off);

        // REQUIRE(" " == remote_control->to_string());

        remote_control->on_button_was_pushed(0);
        remote_control->off_button_was_pushed(0);
        remote_control->on_button_was_pushed(1);
        remote_control->off_button_was_pushed(1);
        remote_control->on_button_was_pushed(2);
        remote_control->off_button_was_pushed(2);
        remote_control->on_button_was_pushed(3);
        remote_control->off_button_was_pushed(3);
    }
}