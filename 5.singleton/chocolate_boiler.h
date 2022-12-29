#ifndef CHOCOLATE_BOILER_H
#define CHOCOLATE_BOILER_H
#include <string>
#include <memory>

namespace chocolate_boiler
{
    using String = std::string;
    class ChocolateBoiler
    {
    public:
        ChocolateBoiler() : m_is_empty(true), m_is_boiled(false)
        {
            m_unique_instance = nullptr;
        }

        static std::shared_ptr<ChocolateBoiler> get_instance()
        {
            if (nullptr == m_unique_instance)
            {
                // Creating unique instance of Chocolate Boiler
                m_unique_instance = std::make_shared<ChocolateBoiler>();
            }

            // Returning instance of Chocolate Boiler
            return m_unique_instance;
        }

        void fill()
        {
            if (is_empty())
            {
                m_is_empty = false;
                m_is_boiled = false;
                // fill the boiler with a milk/chocolate mixture
            }
        }

        void drain()
        {
            if (!is_empty() && is_boiled())
            {
                // drain the m_is_boiled milk and chocolate
                m_is_empty = true;
            }
        }

        void boil()
        {
            if (!is_empty() && !is_boiled())
            {
                // bring the contents to a boil
                m_is_boiled = true;
            }
        }

        bool is_empty()
        {
            return m_is_empty;
        }

        bool is_boiled()
        {
            return m_is_boiled;
        }

    private:
        bool m_is_empty;
        bool m_is_boiled;
        static std::shared_ptr<ChocolateBoiler> m_unique_instance;
    };
}
#endif // !CHOCOLATE_BOILER_H