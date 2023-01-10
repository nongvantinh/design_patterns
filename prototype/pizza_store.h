#ifndef PIZZA_STORE_H
#define PIZZA_STORE_H
#include <string>
#include <memory>
#include <sstream>

namespace pizza_store_factory
{
    using String = std::string;
    class Monster
    {
    public:
        Monster(String p_name) : m_eats_children(true), m_has_wings(false), m_num_heads(1), m_can_breathe_fire(false), m_name(p_name) {}
        void spit_poison() {} // default is do nothing
        void set_name(String p_name) { m_name = p_name; }

        String to_string()
        {
            std::ostringstream oss;
            oss << "I'm a monster named " << m_name << " with " << m_num_heads << " head(s). ";
            if (m_can_breathe_fire)
            {
                oss << "I can breathe fire. ";
            }
            if (m_eats_children)
            {
                oss << "I eat children. ";
            }
            if (m_has_wings)
            {
                oss << "I have wings. ";
            }
            return oss.str();
        }

    protected:
        bool m_eats_children;
        bool m_has_wings;
        int m_num_heads;
        bool m_can_breathe_fire;
        String m_name;
    };

    class Drakon : public Monster
    {
        Drakon(String p_name, int p_num_heads, bool p_can_breathe_fire)
            : Monster(p_name)
        {
            m_num_heads = p_num_heads;
            m_can_breathe_fire = p_can_breathe_fire;
        }

        String spit_poison() { return m_name + " spits poison"; }
    };

    class Dragon : public Monster
    {
        Dragon(String p_name, bool p_has_wings)
            : Monster(p_name)
        {
            m_has_wings = p_has_wings;
            m_can_breathe_fire = true;
        }

        // Each concrete monster could determine how best to clone itself
    };

    class Client
    {
        static void main(String[] args)
        {
            Prototype p1 = new ConcretePrototype1();
            Prototype p2 = new ConcretePrototype2();

            // ... later ...
            operation(p1);
            operation(p2);
        }

        static Prototype operation(Prototype p)
        {
            // This code doesn't know or care what the concrete type of p is
            Prototype pCopy = null;
            try
            {
                pCopy = p.copy();
                // do something useful with pCopy
                return "Operating with pCopy!";
            }
            catch (CloneNotSupportedException e)
            {
                e.printStackTrace();
            }
            return pCopy;
        }
    };
}
#endif // !PIZZA_STORE_H