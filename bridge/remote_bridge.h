#ifndef REMOTE_BRIDGE_H
#define REMOTE_BRIDGE_H
#include <string>
#include <memory>
#include <stdexcept>

namespace remote_bridge
{
    using String = std::string;
    class TV
    {
    public:
        virtual String on() = 0;
        virtual String off() = 0;
        virtual String tune_channel(int p_channel) = 0;
        virtual int get_channel() = 0;
    };

    class LG : public TV
    {
    public:
        LG() : m_channel(1) {}
        String on() override { return "Turning on the LG TV"; }
        String off() override { return "Turning off the LG TV"; }
        String tune_channel(int p_channel) override
        {
            m_channel = p_channel;
            return "Set the LG TV Channel to " + std::to_string(p_channel);
        }

        int get_channel() override { return m_channel; }

    private:
        int m_channel;
    };

    class Sony : public TV
    {
    public:
        Sony() : m_station(0) {}
        String on() override { return "Turning on the Sony TV"; }
        String off() override { return "Turning off the Sony TV"; }
        String tune_channel(int p_channel) override
        {
            m_station = p_channel;
            return "Set the Sony TV m_station to " + m_station;
        }
        int get_channel() override { return m_station; }

    private:
        int m_station;
    };

    class TVFactory
    {
    public:
        std::shared_ptr<TV> get_tv(String p_type)
        {
            if ("LG" == p_type)
            {
                return std::make_shared<LG>();
            }
            else if ("Sony" == p_type)
            {
                return std::make_shared<Sony>();
            }

            throw std::runtime_error("Invalid TV Type");
        }
    };

    class RemoteControl
    {
    public:
        RemoteControl(std::shared_ptr<TVFactory> p_tv_factory) { m_tv_factory = p_tv_factory; }
        String on() { return m_tv->on(); }
        String off() { return m_tv->off(); }
        void setChannel(int p_channel) { m_tv->tune_channel(p_channel); }
        int get_channel() { return m_tv->get_channel(); }
        void setTV(String p_type) { m_tv = m_tv_factory->get_tv(p_type); }

    protected:
        std::shared_ptr<TV> m_tv;
        std::shared_ptr<TVFactory> m_tv_factory;
    };

    class GenericRemote : public RemoteControl
    {
    public:
        GenericRemote(std::shared_ptr<TVFactory> p_tv_factory) : RemoteControl(p_tv_factory) {}
        void next_channel()
        {
            int channel = get_channel();
            setChannel(channel + 1);
        }

        void prev_channel()
        {
            int channel = get_channel();
            setChannel(channel - 1);
        }
    };

    class SpecialRemote : public RemoteControl
    {
    public:
        SpecialRemote(std::shared_ptr<TVFactory> p_tv_factory) : RemoteControl(p_tv_factory) {}
        void up()
        {
            int channel = get_channel();
            setChannel(channel + 1);
        }

        void down()
        {
            int channel = get_channel();
            setChannel(channel - 1);
        }
    };
}
#endif // !REMOTE_BRIDGE_H