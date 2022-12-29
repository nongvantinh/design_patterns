#ifndef GUMBALL_MACHINE_H
#define GUMBALL_MACHINE_H
#include <string>
#include <sstream>

namespace gumball_machine
{
    using String = std::string;

    class GumballMachine
    {
    public:
        enum class Status
        {
            SOLD_OUT,
            NO_QUARTER,
            HAS_QUARTER,
            SOLD
        };

        GumballMachine() : m_state(Status::SOLD_OUT), m_count(0) {}
        GumballMachine(int p_count) : m_state(Status::SOLD_OUT), m_count(p_count)
        {
            if (0 < p_count)
            {
                m_state = Status::NO_QUARTER;
            }
        }

        String insert_quarter()
        {
            if (Status::HAS_QUARTER == m_state)
            {
                return "You can't insert another quarter";
            }
            else if (Status::NO_QUARTER == m_state)
            {
                m_state = Status::HAS_QUARTER;
                return "You inserted a quarter";
            }
            else if (Status::SOLD_OUT == m_state)
            {
                return "You can't insert a quarter, the machine is sold out";
            }
            else if (Status::SOLD == m_state)
            {
                return "Please wait, we're already giving you a gumball";
            }
            return "";
        }

        String eject_quarter()
        {
            if (Status::HAS_QUARTER == m_state)
            {
                m_state = Status::NO_QUARTER;
                return "Quarter returned";
            }
            else if (Status::NO_QUARTER == m_state)
            {
                return "You haven't inserted a quarter";
            }
            else if (Status::SOLD == m_state)
            {
                return "Sorry, you already turned the crank";
            }
            else if (Status::SOLD_OUT == m_state)
            {
                return "You can't eject, you haven't inserted a quarter yet";
            }
            return "";
        }

        String turn_crank()
        {
            if (Status::SOLD == m_state)
            {
                return "Turning twice doesn't get you another gumball!";
            }
            else if (Status::NO_QUARTER == m_state)
            {
                return "You turned but there's no quarter";
            }
            else if (Status::SOLD_OUT == m_state)
            {
                return "You turned, but there are no gumballs";
            }
            else if (Status::HAS_QUARTER == m_state)
            {
                m_state = Status::SOLD;
                dispense();
                return "You turned...";
            }

            return "";
        }

        String dispense()
        {
            if (Status::SOLD == m_state)
            {
                --m_count;
                if (0 == m_count)
                {
                    m_state = Status::SOLD_OUT;
                }
                else
                {
                    m_state = Status::NO_QUARTER;
                }
                return "A gumball comes rolling out the slot";
            }
            else if (Status::NO_QUARTER == m_state)
            {
                return "You need to pay first";
            }
            else if (Status::SOLD_OUT == m_state)
            {
                return "No gumball dispensed";
            }
            else if (Status::HAS_QUARTER == m_state)
            {
                return "No gumball dispensed";
            }

            return "";
        }

        void refill(int p_num_gum_balls)
        {
            m_count = p_num_gum_balls;
            m_state = Status::NO_QUARTER;
        }

        int get_count() { return m_count; }

        String toString()
        {
            std::ostringstream result;
            result << "\nMighty Gumball, Inc.";
            result << "\nJava-enabled Standing Gumball Model #2004\n";
            result << "Inventory: " << m_count << " gumball";
            if (1 != m_count)
            {
                result << "s";
            }
            result << "\nMachine is ";
            if (Status::SOLD_OUT == m_state)
            {
                result << "sold out";
            }
            else if (Status::NO_QUARTER == m_state)
            {
                result << "waiting for quarter";
            }
            else if (Status::HAS_QUARTER == m_state)
            {
                result << "waiting for turn of crank";
            }
            else if (Status::SOLD == m_state)
            {
                result << "delivering a gumball";
            }
            result << "\n";
            return result.str();
        }

    private:
        Status m_state;
        int m_count;
        State soldOutState;
        State noQuarterState;
        State hasQuarterState;
        State soldState;
    };
}
#endif // !GUMBALL_MACHINE_H