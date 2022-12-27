#include "5.football_strategy_pattern.h"

#include "Catch.hpp"
#include <iostream>
using namespace strategy_football;
String BananaPassPlay::movement() { return "I am running a banana pass pattern"; }
String BlockingBackPlay::movement() { return "I am blocking any rushers that the line does not get"; }
String PullingBlockPlay::movement() { return "I am pulling to block"; }

Player::Player(std::shared_ptr<IPlay> p_pattern_to_run) : m_pattern_to_run(p_pattern_to_run) {}
String Player::pattern() { return m_pattern_to_run->movement(); }

Guard::Guard() : Player(std::make_shared<PullingBlockPlay>()) {}
RunningBack::RunningBack() : Player(std::make_shared<BlockingBackPlay>()) {}
WideReceiver::WideReceiver() : Player(std::make_shared<BananaPassPlay>()) {}

TEST_CASE("StrategyFootballFixture", "[strategy")
{
    SECTION("TestPullingGuard")
    {
        std::shared_ptr<Guard> pulling_guard = std::make_shared<Guard>();
        REQUIRE("I am pulling to block" == pulling_guard->pattern());
    }
    SECTION("TestWideReceiver")
    {
        std::shared_ptr<WideReceiver> widereceiver_pass_pattern = std::make_shared<WideReceiver>();

        REQUIRE("I am running a banana pass pattern" == widereceiver_pass_pattern->pattern());
    }
    SECTION("TestRunningBack")
    {
        std::shared_ptr<RunningBack> runnering_back_pattern = std::make_shared<RunningBack>();

        REQUIRE("I am blocking any rushers that the line does not get" == runnering_back_pattern->pattern());
    }
}