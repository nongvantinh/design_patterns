#include "remote_wl.h"

#include "Catch.hpp"

using namespace remote_wl;

TEST_CASE("Test Remote loader", "[]")
{
    SECTION("")
    {
        std::shared_ptr<RemoteControl> remoteControl = std::make_shared<RemoteControl>();

        std::shared_ptr<Light> livingRoomLight = std::make_shared<Light>("Living Room");
        std::shared_ptr<Light> kitchenLight = std::make_shared<Light>("Kitchen");
        std::shared_ptr<CeilingFan> ceilingFan = std::make_shared<CeilingFan>("Living Room");
        std::shared_ptr<GarageDoor> garageDoor = std::make_shared<GarageDoor>("Main house");
        std::shared_ptr<Stereo> stereo = std::make_shared<Stereo>("Living Room");

        remoteControl->set_command(0, livingRoomLight::on, livingRoomLight::off);
        remoteControl->set_command(1, kitchenLight::on, kitchenLight::off);
        remoteControl->set_command(2, ceilingFan::high, ceilingFan::off);

        Command stereoOnWithCD = ()->
        {
            stereo->on();
            stereo->set_cd();
            stereo->set_volume(11);
        };

        remoteControl->set_command(3, stereoOnWithCD, stereo::off);
        remoteControl->set_command(4, garageDoor::up, garageDoor::down);

        REQUIRE(" " == remoteControl->to_string());

        remoteControl->on_button_was_pushed(0);
        remoteControl->off_button_was_pushed(0);
        remoteControl->on_button_was_pushed(1);
        remoteControl->off_button_was_pushed(1);
        remoteControl->on_button_was_pushed(2);
        remoteControl->off_button_was_pushed(2);
        remoteControl->on_button_was_pushed(3);
        remoteControl->off_button_was_pushed(3);
        remoteControl->on_button_was_pushed(4);
        remoteControl->off_button_was_pushed(4);
        remoteControl->on_button_was_pushed(5);
    }
}