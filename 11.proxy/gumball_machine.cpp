#include "pizza_store.h"

#include "Catch.hpp"

using namespace pizza_store_factory;

TEST_CASE("ProxyDynamicFixture", "[proxy]")
{
    SECTION("TestProxyOwner")
    {
        Person person = new Person();
        IPerson personProxy = (IPerson)DynamicProxyFactory.Instance.CreateProxy(person, new InvocationDelegate(OwnerInvocationHandler));

        personProxy.Gender = "Male";
        personProxy.Name = "John Doe";
        personProxy.Interest = "Eating junkfood and watching talkshows";
        REQUIRE("Name: John Doe" == "Name: " + person.Name);
        REQUIRE("Gender: Male" == "Gender: " + person.Gender);
        REQUIRE("Interest: Eating junkfood and watching talkshows" == "Interest: " + person.Interest);

        //			Console.WriteLine("Name: " + person.Name);
        //			Console.WriteLine("Gender: " + person.Gender);
        //			Console.WriteLine("Interest: " + person.Interest);
    }
    SECTION("TestProxyOwnerException")
    {
        Person person = new Person();
        IPerson personProxy = (IPerson)DynamicProxyFactory.Instance.CreateProxy(person, new InvocationDelegate(OwnerInvocationHandler));

        personProxy.Name = "John Doe";
        personProxy.HotOrNot = 10;

        Console.WriteLine("Name: " + person.Name);
        Console.WriteLine("Rating: " + person.HotOrNot);
    }
    SECTION("TestProxyNonOwnerSetRating")
    {
        Person person = new Person();
        person.Name = "John Doe";

        IPerson personProxy = (IPerson)DynamicProxyFactory.Instance.CreateProxy(person, new InvocationDelegate(NonOwnerInvocationHandler));

        personProxy.HotOrNot = 10;
        personProxy.HotOrNot = 5;

        Assert.AreEqual("Name: John Doe", "Name: " + person.Name);
        Assert.AreEqual("Rating: 7", "Rating: " + person.HotOrNot);

        //			Console.WriteLine("Name: " + person.Name);
        //			Console.WriteLine("Rating: " + person.HotOrNot);
    }
    SECTION("TestProxyNonOwnerException")
    {
        Person person = new Person();
        person.Name = "John Doe";

        IPerson personProxy = (IPerson)DynamicProxyFactory.Instance.CreateProxy(person, new InvocationDelegate(NonOwnerInvocationHandler));

        personProxy.Name = "John Doe";
        personProxy.Interest = "This will not display due to exception";

        Console.WriteLine("Name: " + person.Name);
        Console.WriteLine("Interest: " + person.Interest);
    }
}

object OwnerInvocationHandler(object target, MethodBase method, object[] parameters)
{
    object result = null;

    try
    {
        if (!method.Name.Equals("set_HotOrNot"))
        {
            result = method.Invoke(target, parameters);
        }
        else
        {
            throw new UnauthorizedAccessException("You are not permitted to rate yourself");
        }
    }
    catch (ApplicationException ex)
    {
        return ex.StackTrace;
    }

    return result;
}
object NonOwnerInvocationHandler(object target, MethodBase method, object[] parameters)
{
    object result = null;

    try
    {
        if (method.Name.Equals("set_HotOrNot"))
        {
            result = method.Invoke(target, parameters);
        }
        else
        {
            throw new UnauthorizedAccessException("You are not permitted to update another's personal information!");
        }
    }
    catch (ApplicationException ex)
    {
        return ex.StackTrace;
    }

    return result;
}