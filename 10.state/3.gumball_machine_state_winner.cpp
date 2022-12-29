#include "3.gumball_machine_state_winner.h"

#include "Catch.hpp"
#include <iostream>
#include <sstream>

using namespace gumball_machine_state_winner;

GumballMachine::GumballMachine(int p_number_of_gumballs)
    : m_sold_out_state(std::make_shared<SoldOutState>(*this)),
      m_no_quarter_state(std::make_shared<NoQuarterState>(*this)),
      m_has_quarter_state(std::make_shared<HasQuarterState>(*this)),
      m_sold_state(std::make_shared<SoldState>(*this)),
      m_winner_state(std::make_shared<WinnerState>(*this)),
      m_count(p_number_of_gumballs)
{
    m_state = (0 < p_number_of_gumballs) ? m_no_quarter_state : m_sold_out_state;
}
String GumballMachine::insert_quarter() { return m_state->insert_quarter(); }
String GumballMachine::eject_quarter() { return m_state->eject_quarter(); }
String GumballMachine::turn_crank() { return m_state->turn_crank() + m_state->dispense(); }

String GumballMachine::release_ball()
{
    if (0 != m_count)
    {
        --m_count;
    }

    return "A gumball comes rolling out the slot...";
}

int GumballMachine::get_count() { return m_count; }

String GumballMachine::refill(int p_number_of_gumballs)
{
    m_count += p_number_of_gumballs;
    m_state->refill();
    return "The gumball machine was just refilled; its new count is: " + std::to_string(get_count());
}

std::shared_ptr<State> GumballMachine::get_state() { return m_state; }
void GumballMachine::set_state(std::shared_ptr<State> p_state) { m_state = p_state; }

std::shared_ptr<State> GumballMachine::get_sold_out_state() { return m_sold_out_state; }
std::shared_ptr<State> GumballMachine::get_no_quarter_state() { return m_no_quarter_state; }
std::shared_ptr<State> GumballMachine::get_has_quarter_state() { return m_has_quarter_state; }
std::shared_ptr<State> GumballMachine::get_sold_state() { return m_sold_state; }
std::shared_ptr<State> GumballMachine::get_winner_state() { return m_winner_state; }

String GumballMachine::to_string()
{
    std::ostringstream result;
    result << "\nMighty Gumball, Inc.";
    result << "\nJava-enabled Standing Gumball Model #2004";
    result << "\nInventory: " << std::to_string(get_count()) << " gumball";
    if (1 != get_count())
    {
        result << "s";
    }
    result << "\n";
    result << "Machine is " << m_state->to_string() << "\n";
    return result.str();
}

HasQuarterState::HasQuarterState(GumballMachine &p_gumball_machine) : m_gumball_machine(p_gumball_machine) {}

String HasQuarterState::insert_quarter() { return "You can't insert another quarter"; }
String HasQuarterState::eject_quarter()
{
    m_gumball_machine.set_state(m_gumball_machine.get_no_quarter_state());
    return "Quarter returned";
}

String HasQuarterState::turn_crank()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);
    if (0 == dist(mt) && 1 < m_gumball_machine.get_count())
    {
        m_gumball_machine.set_state(m_gumball_machine.get_winner_state());
    }
    else
    {
        m_gumball_machine.set_state(m_gumball_machine.get_sold_state());
    }
    return "You turned...";
}

String HasQuarterState::dispense() { return "No gumball dispensed"; }
String HasQuarterState::refill() { return ""; }
String HasQuarterState::to_string() { return "waiting for turn of crank"; }

NoQuarterState::NoQuarterState(GumballMachine &p_gumball_machine) : m_gumball_machine(p_gumball_machine) {}

String NoQuarterState::insert_quarter()
{
    m_gumball_machine.set_state(m_gumball_machine.get_has_quarter_state());
    return "You inserted a quarter";
}

String NoQuarterState::eject_quarter() { return "You haven't inserted a quarter"; }
String NoQuarterState::turn_crank() { return "You turned, but there's no quarter"; }

String NoQuarterState::dispense() { return "You need to pay first"; }
String NoQuarterState::refill() { return ""; }
String NoQuarterState::to_string() { return "waiting for quarter"; }

SoldOutState::SoldOutState(GumballMachine &p_gumball_machine) : m_gumball_machine(p_gumball_machine) {}

String SoldOutState::insert_quarter() { return "You can't insert a quarter, the machine is sold out"; }
String SoldOutState::eject_quarter() { return "You can't eject, you haven't inserted a quarter yet"; }
String SoldOutState::turn_crank() { return "You turned, but there are no gumballs"; }
String SoldOutState::dispense() { return "No gumball dispensed"; }
String SoldOutState::refill()
{
    m_gumball_machine.get_no_quarter_state();
    return "";
}
String SoldOutState::to_string() { return "sold out"; }

SoldState::SoldState(GumballMachine &p_gumball_machine) : m_gumball_machine(p_gumball_machine) {}
String SoldState::insert_quarter() { return "Please wait, we're already giving you a gumball"; }
String SoldState::eject_quarter() { return "Sorry, you already turned the crank"; }
String SoldState::turn_crank() { return "Turning twice doesn't get you another gumball!"; }

String SoldState::dispense()
{
    String output = m_gumball_machine.release_ball();
    if (0 < m_gumball_machine.get_count())
    {
        m_gumball_machine.set_state(m_gumball_machine.get_no_quarter_state());
    }
    else
    {
        output += " Oops, out of gumballs!\n";
        m_gumball_machine.set_state(m_gumball_machine.get_sold_out_state());
    }

    return output;
}

String SoldState::refill() { return ""; }
String SoldState::to_string() { return "dispensing a gumball"; }

WinnerState::WinnerState(GumballMachine &p_gumball_machine) : m_gumball_machine(p_gumball_machine) {}
String WinnerState::insert_quarter() { return "Please wait, we're already giving you a Gumball"; }
String WinnerState::eject_quarter() { return "Please wait, we're already giving you a Gumball"; }
String WinnerState::turn_crank() { return "Turning again doesn't get you another gumball!"; }
String WinnerState::dispense()
{
    String output = m_gumball_machine.release_ball();
    if (0 == m_gumball_machine.get_count())
    {
        m_gumball_machine.set_state(m_gumball_machine.get_sold_out_state());
    }
    else
    {
        output += m_gumball_machine.release_ball();
        output += "YOU'RE A WINNER! You got two gumballs for your quarter";
        if (0 < m_gumball_machine.get_count())
        {
            m_gumball_machine.set_state(m_gumball_machine.get_no_quarter_state());
        }
        else
        {
            output += "Oops, out of gumballs!";
            m_gumball_machine.set_state(m_gumball_machine.get_sold_out_state());
        }
    }

    return output;
}

String WinnerState::refill() { return ""; }
String WinnerState::to_string() { return "despensing two gumballs for your quarter, because YOU'RE A WINNER!"; }

void print(String p_value) { std::cout << p_value << std::endl; }
TEST_CASE("TestGumballMachineWinner", "[state]")
{
    int count = 10;
    GumballMachine gumball_machine(count);

    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }

    REQUIRE("You inserted a quarter" == gumball_machine.insert_quarter());
    REQUIRE("You turned...No gumball dispensed" == gumball_machine.turn_crank());
    REQUIRE("Please wait, we're already giving you a gumball" == gumball_machine.insert_quarter());
    REQUIRE("You turned, but there's no quarterA gumball comes rolling out the slot..." == gumball_machine.turn_crank());

    --count;
    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }

    REQUIRE("You inserted a quarter" == gumball_machine.insert_quarter());
    REQUIRE("You turned...No gumball dispensed" == gumball_machine.turn_crank());
    REQUIRE("Please wait, we're already giving you a gumball" == gumball_machine.insert_quarter());
    REQUIRE("You turned, but there's no quarterA gumball comes rolling out the slot..." == gumball_machine.turn_crank());

    --count;
    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }

    REQUIRE("You inserted a quarter" == gumball_machine.insert_quarter());
    REQUIRE("You turned...No gumball dispensed" == gumball_machine.turn_crank());
    REQUIRE("Please wait, we're already giving you a gumball" == gumball_machine.insert_quarter());
    REQUIRE("You turned, but there's no quarterA gumball comes rolling out the slot..." == gumball_machine.turn_crank());

    --count;
    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }

    REQUIRE("You inserted a quarter" == gumball_machine.insert_quarter());
    REQUIRE("You turned...No gumball dispensed" == gumball_machine.turn_crank());
    REQUIRE("Please wait, we're already giving you a gumball" == gumball_machine.insert_quarter());
    REQUIRE("You turned, but there's no quarterA gumball comes rolling out the slot..." == gumball_machine.turn_crank());

    --count;
    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }

    REQUIRE("You inserted a quarter" == gumball_machine.insert_quarter());
    REQUIRE("You turned...No gumball dispensed" == gumball_machine.turn_crank());
    REQUIRE("Please wait, we're already giving you a gumball" == gumball_machine.insert_quarter());
    REQUIRE("You turned, but there's no quarterA gumball comes rolling out the slot..." == gumball_machine.turn_crank());

    --count;
    SECTION("GumballMachineWinner with 10 gumbals")
    {
        std::ostringstream result;
        result << "\nMighty Gumball, Inc.";
        result << "\nJava-enabled Standing Gumball Model #2004\n";
        result << "Inventory: " << std::to_string(count) << " gumball";
        result << "s";
        result << "\nMachine is ";
        result << "waiting for quarter";
        result << "\n";

        REQUIRE(result.str() == gumball_machine.to_string());
    }
}