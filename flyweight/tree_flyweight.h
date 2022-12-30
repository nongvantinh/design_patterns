#ifndef TREE_FLYWEIGHT_H
#define TREE_FLYWEIGHT_H

#include <string>
#include <memory>
#include <ctime>
#include <sstream>

namespace tree_flyweight
{
    using String = std::string;
    class Tree
    {
    public:
        virtual String display(int x, int y) = 0;
        bool is_within_range(std::tm *now)
        {
            return ((now->tm_mon + 1) > 2) && ((now->tm_mon + 1) < 11);
        }
    };

    class DeciduousTree : public Tree
    {
    public:
        // complex trunk, branch, leaf graphic data
        String display(int x, int y)
        {
            std::ostringstream oss;
            oss << "Deciduous tree is located at " << x << ", " << y << "\n";
            std::time_t t = std::time(0); // get time now
            std::tm *now = std::localtime(&t);

            if (!is_within_range(now))
            {
                oss << "The tree currently has no leaves\n";
            }
        return oss.str();
        }
    };

    class ConiferTree : public Tree
    {
    public:
        // Complex trunk, branch, needle graphic data
        String display(int x, int y)
        {
            std::ostringstream oss;
            oss << "Conifer tree is located at " << x << ", " << y << "\n";
            return oss.str();
        }
    };

    class TreeFactory
    {
    private:
        std::shared_ptr<Tree> m_deciduous_tree, m_conifer_tree;

    public:
        TreeFactory()
        {
            m_deciduous_tree = std::make_shared<DeciduousTree>();
            m_conifer_tree = std::make_shared<ConiferTree>();
        }

        std::shared_ptr<Tree> get_tree(String p_type)
        {
            if ("deciduous" == p_type)
            {
                return m_deciduous_tree;
            }
            else if ("conifer" == p_type)
            {
                return m_conifer_tree;
            }

            throw std::runtime_error("Invalid kind of tree");
        }
    };
}
#endif // !TREE_FLYWEIGHT_H