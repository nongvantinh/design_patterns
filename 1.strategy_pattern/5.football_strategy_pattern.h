#ifndef FOOTBALL_STRATEGY_PATTERN_H
#define FOOTBALL_STRATEGY_PATTERN_H

#include <memory>
#include <string>
namespace strategy_football
{

    using String = std::string;

    class IPlay
    {
    public:
        virtual String movement() = 0;
    };
    class BananaPassPlay : public IPlay
    {
    public:
        String movement() override;
    };

    class BlockingBackPlay : public IPlay
    {
    public:
        String movement() override;
    };

    class PullingBlockPlay : public IPlay
    {
    public:
        String movement() override;
    };

    class Player
    {
    public:
        Player(std::shared_ptr<IPlay> p_pattern_to_run);
        String pattern();

    protected:
        std::shared_ptr<IPlay> m_pattern_to_run;
    };

    class Guard : public Player
    {
    public:
        Guard();
    };

    class RunningBack : public Player
    {
    public:
        RunningBack();
    };

    class WideReceiver : public Player
    {
    public:
        WideReceiver();
    };
}
#endif // !FOOTBALL_STRATEGY_PATTERN_H