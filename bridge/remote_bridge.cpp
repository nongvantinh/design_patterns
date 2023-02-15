#include "remote_bridge.h"

#include "Catch.hpp"
#include <iostream>

using namespace remote_bridge;
void print(String v)
{
    std::cout << v << std::endl;
}
TEST_CASE("remote_bridge", "[bridge]")
{
    std::shared_ptr<TVFactory> tv_factory = std::make_shared<TVFactory>();
    std::shared_ptr<SpecialRemote> remote_sony = std::make_shared<SpecialRemote>(tv_factory);
    print("Connect your remote to the TV");
    remote_sony->setTV("Sony");
    remote_sony->on();
    remote_sony->up();
    remote_sony->down();
    remote_sony->off();

    std::shared_ptr<GenericRemote> remoteLG = std::make_shared<GenericRemote>(tv_factory);
    print("Connect your remote to the TV");
    remoteLG->setTV("LG");
    remoteLG->on();
    remoteLG->next_channel();
    remoteLG->prev_channel();
    remoteLG->off();
}