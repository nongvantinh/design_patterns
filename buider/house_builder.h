#ifndef HOUSE_BUILDER_H
#define HOUSE_BUILDER_H
#include <string>
#include <memory>
#include <vector>
#include <sstream>

namespace house_builder
{
    using String = std::string;
    enum HouseType
    {
        WOOD,
        CLAY,
        GINGERBREAD,
        STONE
    };

    class Roof
    {
    public:
        Roof(String p_material) { m_material = "Roof made out of " + p_material; }
        void set_name(String p_material) { m_material = p_material; }
        String to_string() { return m_material; }
        String material() { return m_material; }

    private:
        String m_material;
    };

    class Window
    {
    public:
        Window(String p_material) { m_material = "Window made out of " + p_material; }
        void set_name(String p_material) { m_material = p_material; }
        String to_string() { return m_material; }
        String material() { return m_material; }

    private:
        String m_material;
    };

    class Wall
    {
    public:
        Wall(String p_material) { m_material = "Wall made out of " + p_material; }
        void set_name(String p_material) { m_material = p_material; }
        String to_string() { return m_material; }
        String material() { return m_material; }

    private:
        String m_material;
    };

    class InteriorWall : public Wall
    {
    public:
        InteriorWall(String p_material) : Wall(p_material) { m_material = "Interior wall out of " + p_material; }
        void set_name(String p_material) { m_material = p_material; }
        String to_string() { return m_material; }
        String material() { return m_material; }

    private:
        String m_material;
    };

    class House
    {
    public:
        House() {}

        House *set_house_type(HouseType p_house_type)
        {
            p_house_type = p_house_type;
            switch (p_house_type)
            {
            case HouseType::WOOD:
                m_material = "My wood house";
                break;
            case HouseType::CLAY:
                m_material = "My clay house";
                break;
            case HouseType::GINGERBREAD:
                m_material = "My holiday gingerbread house";
                break;
            case HouseType::STONE:
                m_material = "My stone house";
                break;
            }
            return this;
        }

        House *add_roof(std::shared_ptr<Roof> p_roof)
        {
            m_roof = p_roof;
            return this;
        }

        House *add_wall(std::shared_ptr<Wall> p_wall)
        {
            m_walls.push_back(p_wall);
            return this;
        }

        House *add_window(std::shared_ptr<Window> p_window)
        {
            m_windows.push_back(p_window);
            return this;
        }

        void set_name(String p_material) { m_material = p_material; }
        String material() { return m_material; }

        String to_string()
        {
            // Use a StringBuilder to build the string :-)
            // Like StringBuffer, but not synchronized
            std::ostringstream display;
            display << "---- " << m_material << " ----\n";
            for (std::shared_ptr<Wall> p_wall : m_walls)
            {
                display << "--- " << p_wall->material() << " ---\n";
            }
            for (std::shared_ptr<Window> window : m_windows)
            {
                display << "--- " << window->material() << " ---\n";
            }
            display << "--- " << m_roof->material() << " ---\n";
            return display.str();

            // There is some difference of opinion about StringBuilder and whether it's using
            // the Builder pattern or not-> Some say yes, some say no->
            // StringBuilder does not provide an abstract API with multiple subclasses for
            //   creating different representations (variations)->
        }

    private:
        String m_material;
        HouseType p_house_type;
        std::shared_ptr<Roof> m_roof;
        std::vector<std::shared_ptr<Wall>> m_walls;
        std::vector<std::shared_ptr<Window>> m_windows;
    };

    class HouseBuilder
    {
    public:
        HouseBuilder() : m_house(std::make_shared<House>()) {}
        void set_house_type(HouseType p_house_type)
        {
            p_house_type = p_house_type;
            m_house->set_house_type(p_house_type);
        }
        // Each method in the Builder returns the Builder so we can use the Fluent Interface Pattern
        virtual HouseBuilder *add_walls() = 0;
        virtual HouseBuilder *add_roof() = 0;
        virtual HouseBuilder *add_windows() = 0;

        std::shared_ptr<House> build()
        {
            // Build the house!

            // Very simple build -- just return the house!
            // We've added all the parts...
            // In a real build, we'd have to nail and screw everything together of course.
            // And add wiring and so on.
            return m_house;
        }

    protected:
        String m_builder_name;
        HouseType p_house_type;
        std::shared_ptr<House> m_house;
    };

    class GingerbreadHouseBuilder : public HouseBuilder
    {
    public:
        GingerbreadHouseBuilder()
        {
            m_builder_name = "Gingerbread House Builder";
            set_house_type(HouseType::GINGERBREAD);
        }

        HouseBuilder *add_walls() override
        {
            // add exterior m_walls
            for (size_t i = 0; i < m_num_walls; ++i)
            {
                // print("Adding p_wall made out of " + m_wall_material);
                m_house->add_wall(std::make_shared<Wall>(m_wall_material));
            }
            return this;
        }

        HouseBuilder *add_windows() override
        {
            for (size_t i = 0; i < m_num_windows; ++i)
            {
                // print("Adding window made out of " + m_window_material);
                m_house->add_window(std::make_shared<Window>(m_window_material));
            }
            return this;
        }

        HouseBuilder *add_roof() override
        {
            m_house->add_roof(std::make_shared<Roof>(m_roof_material));
            return this;
        }

        std::shared_ptr<House> build()
        {
            // print("Stick everything together with icing");
            return m_house;
        }

    private:
        size_t m_num_walls = 4;
        size_t m_num_windows = 4;
        String m_window_material = "Sugar";
        String m_wall_material = "Gingerbread and icing";
        String m_roof_material = "Twizzlers";
    };

    class StoneHouseBuilder : public HouseBuilder
    {
    public:
        StoneHouseBuilder()
        {
            m_builder_name = "Stone House Builder";
            set_house_type(HouseType::STONE);
        }
        HouseBuilder *add_walls() override
        {
            // Add 4 exterior m_walls
            for (size_t i = 0; i < m_num_walls - 1; ++i)
            {
                m_house->add_wall(std::make_shared<Wall>(m_interior_wall_material));
            }
            // Add 1 interior p_wall
            m_house->add_wall(std::make_shared<InteriorWall>(m_wall_material));
            return this;
        }

        HouseBuilder *add_windows() override
        {
            for (size_t i = 0; i < m_num_windows; ++i)
            {
                m_house->add_window(std::make_shared<Window>(m_window_material));
            }
            return this;
        }

        HouseBuilder *add_roof() override
        {
            m_house->add_roof(std::make_shared<Roof>(m_roof_material));
            return this;
        }

        std::shared_ptr<House> build()
        {
            // print("Stick everything together with mortar");
            return m_house;
        }

    private:
        size_t m_num_walls = 5;    // Stone houses have 5 m_walls: 4 exterior, 1 interior
        size_t m_num_windows = 20; // Stone houses have a lot of m_windows
        String m_window_material = "Antique glass";
        String m_wall_material = "Stone, 2 feet thick";
        String m_interior_wall_material = "Stone, 1 foot thick";
        String m_roof_material = "Tile";
    };

    class WoodHouseBuilder : public HouseBuilder
    {
    public:
        WoodHouseBuilder() : m_num_walls(6), m_num_windows(10), m_window_material("Tempered glass"),
                             m_wall_material("Wood, 4x6"), m_interior_wall_material("Wood, 2x4"), m_roof_material("Metal")
        {
            m_builder_name = "Wood House Builder";
            set_house_type(HouseType::WOOD);
        }
        HouseBuilder *add_walls() override
        {
            // add exterior m_walls
            for (size_t i = 0; i < 4; ++i)
            {
                // print("Nailing wood for p_wall made out of " + m_wall_material);
                m_house->add_wall(std::make_shared<Wall>(m_wall_material));
            }
            // add interior m_walls
            for (size_t i = 0; i < m_num_walls - 4; ++i)
            {
                // print("Nailing wood for interior p_wall made out of " + m_interior_wall_material);
                m_house->add_wall(std::make_shared<InteriorWall>(m_interior_wall_material));
            }
            return this;
        }
        HouseBuilder *add_windows() override
        {
            for (size_t i = 0; i < m_num_windows; ++i)
            {
                // print("Adding p_window made out of " + m_window_material);
                m_house->add_window(std::make_shared<Window>(m_window_material));
            }
            return this;
        }
        HouseBuilder *add_roof() override
        {
            m_house->add_roof(std::make_shared<Roof>(m_roof_material));
            return this;
        }

        std::shared_ptr<House> build()
        {
            // print("Nail everything together");
            return m_house;
        }

    private:
        size_t m_num_walls; // 4 exterior walls, 2 interior
        size_t m_num_windows;
        String m_window_material;
        String m_wall_material;
        String m_interior_wall_material;
        String m_roof_material;
    };

}
#endif // !HOUSE_BUILDER_H