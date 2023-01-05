#include "duck_compound.h"

#include "Catch.hpp"

using namespace duck_compound;

TEST_CASE("CompoundDuckFixture", "[compound]")
{
    AbstractDuckFactory duckFactory = new CountingDuckFactory();
    IQuackable mallardDuck = duckFactory.CreateMallardDuck();
    IQuackable redheadDuck = duckFactory.CreateRedheadDuck();
    IQuackable duckCall = duckFactory.CreateDuckCall();
    IQuackable rubberDuck = duckFactory.CreateRubberDuck();
    IQuackable gooseDuck = new GooseAdapter(new Goose());
    Flock flockOfDucks = new Flock();
    flockOfDucks.Add(redheadDuck);
    flockOfDucks.Add(duckCall);
    flockOfDucks.Add(rubberDuck);
    flockOfDucks.Add(gooseDuck);

    Flock flockOfMallards = new Flock();
    IQuackable mallardOne = duckFactory.CreateMallardDuck();
    IQuackable mallardTwo = duckFactory.CreateMallardDuck();
    IQuackable mallardThree = duckFactory.CreateMallardDuck();
    IQuackable mallardFour = duckFactory.CreateMallardDuck();
    flockOfMallards.Add(mallardOne);
    flockOfMallards.Add(mallardTwo);
    flockOfMallards.Add(mallardThree);
    flockOfMallards.Add(mallardFour);

    flockOfDucks.Add(flockOfMallards);

    Quackologist quackologist;

    SECTION("DuckSimulator")
    {
        QuackCounter.QuackCount = 0; // set to zero just in case

        Console.WriteLine("Duck Simulator: With Abstract Factory");
        Console.WriteLine("Duck Simulator: Whole Flock Simulation");
        Console.WriteLine(Simulate(flockOfDucks));
        Console.WriteLine("Duck Simulator: Mallard Flock Simulation");
        Console.WriteLine(Simulate(flockOfMallards));

        Console.WriteLine("The ducks quacked " + QuackCounter.QuackCount + " times");

        REQUIRE(" " == " ");
    }
    SECTION("DuckSimulatorObserver")
    {
        QuackCounter.QuackCount = 0; // set to zero just in case

        quackologist = new Quackologist();
        flockOfDucks.RegisterObserver(quackologist);

        Console.WriteLine("Duck Simulator: With Observer");
        Console.WriteLine(Simulate(flockOfDucks));

        Console.WriteLine("The ducks quacked " + QuackCounter.QuackCount + " times");

        REQUIRE(" " == " ");
    }
}

string Simulate(IQuackable duck)
{
    return duck.Quack();
}
