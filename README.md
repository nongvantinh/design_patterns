# design_paterns
This project implements various design patterns in an individual program. So, to compile it, you need:

- g++ version: 12.2.0
- Windows OS: 10

## Principles

### OO Basics

    - Abstraction
    - Encapsulation
    - Polymorphism
    - Inheritance

### OO Principles

    - Encapsulate what varies
    - Favor Composition over inheritance
    - Program to Interfaces, not implementations
    - Strive for loosely coupled designs between objects that interact

### Design principles:
    1. Identify the aspects of the application that vary and separate them from what stays the same.
    2. Program to an interface, not an implementation.
    3. Favor composition over inheritance.

### 1.Strategy: 

**_The Strategy Pattern_** *defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.*

```
g++ -Wall -Wextra main.cpp 1.strategy\3.sim_u_duck_stategy.cpp -I"D:\design_patterns" -I"D:\design_patterns\1.strategy"
```

### 2.Observer: 

**_The Observer Pattern_** *defines a one-to-many dependency between objects so that when one object changes state, all of its dependents are notified and updated automatically.*

```
g++ -Wall -Wextra main.cpp 2.observer\2.weather_station_observer.cpp -I"D:\design_patterns" -I"D:\design_patterns\2.observer"
```

### 3.Decorator: 

**_The Decorator Pattern_** *attaches additional responsibilities to an object dynamically. Decorators provide a fl exible alternative to subclassing for extending functionality.*

```
g++ -Wall -Wextra main.cpp .\3.decorator\pizza_decorator.cpp -I"D:\design_patterns" -I"D:\design_patterns\3.decorator"
g++ -Wall -Wextra main.cpp .\3.decorator\starbuzz_decorator.cpp -I"D:\design_patterns" -I"D:\design_patterns\3.decorator"
g++ -Wall -Wextra main.cpp .\3.decorator\starbuzz_with_size_decorator.cpp -I"D:\design_patterns" -I"D:\design_patterns\3.decorator"
```

### 4.Factory: 

**_The Factory Method Pattern_** *defines an interface for creating an object, but lets subclasses decide which class to instantiate. Factory Method lets a class defer instantiation to subclasses.*

```

 g++ -Wall -Wextra main.cpp .\4.factory\pizza_store_factory_method.cpp -I"D:\design_patterns" -I"D:\design_patterns\4.factory"

```

**_The Abstract Factory Pattern_** *provides an interface for creating families of related or dependent objects without specifying their concrete classes*.

```

 g++ -Wall -Wextra main.cpp .\4.factory\pizza_store_abstract_factory.cpp -I"D:\design_patterns" -I"D:\design_patterns\4.factory"


```

### 5.Singleton: 

**_The Singleton Pattern_** *ensures a class has only one instance, and provides a global point of access to it.*

```
g++ -Wall -Wextra main.cpp 5.singleton\chocolate_boiler.cpp -I"D:\design_patterns" -I"D:\design_patterns\5.singleton"
g++ -Wall -Wextra main.cpp 5.singleton\singleton.cpp -I"D:\design_patterns" -I"D:\design_patterns\5.singleton"
```

### 6.Command: 

**_The Command Pattern_** *encapsulates a request as an object, thereby letting you parameterize other objects with different requests, queue or log requests, and support undoable operations.*
```
g++ -Wall -Wextra main.cpp .\6.command\remote_wl.cpp -I"D:\design_patterns" -I"D:\design_patterns\6.command"
g++ -Wall -Wextra main.cpp .\6.command\undo.cpp -I"D:\design_patterns" -I"D:\design_patterns\6.command"
```

### 7.Adapter: 

**_The Adapter Pattern_** *converts the interface of a class into another interface the clients expect. Adapter lets classes work together that couldn’t otherwise because of incompatible interfaces.*

```
 g++ -Wall -Wextra main.cpp .\7.adapter\ducks_adapter.cpp -I"D:\design_patterns" -I"D:\design_patterns\7.adapter"
```

### 7.Facade: 

**_The Facade Pattern_** *provides a unified interface to a set of interfaces in a subsytem. Facade defines a higher level interface that makes the subsystem easier to use.*

```
g++ -Wall -Wextra main.cpp .\7.facade\home_theather_facade.cpp -I"D:\design_patterns" -I"D:\design_patterns\7.facade"
```

### 8.Template method: 

***_The Template Method Pattern_** *defines the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure.*

```
g++ -Wall -Wextra main.cpp 8.template_method\barista_template_method.cpp -I"D:\design_patterns" -I"D:\design_patterns\8.template_method"
```

### 9.Iterator: 

**_The Iterator Pattern_** "provides a way to access the elements of an aggregate object sequentially without exposing its underlying representation."

```
g++ -Wall -Wextra main.cpp 9.iterator\dinermergercafe_iterator.cpp -I"D:\design_patterns" -I"D:\design_patterns\9.iterator"
```

### 9.Composite: 

**_The Composite Pattern_** *allows you to compose objects into tree structures to represent part-whole hierarchies. Composite lets clients treat individual objects and compositions of objects uniformly.*

```
 g++ -Wall -Wextra main.cpp .\9.composite\menu_composite.cpp -I"D:\design_patterns" -I"D:\design_patterns\9.composite"
```

### 10. State:

***_The State Pattern_** *allows an object to alter its behavior when its internal state changes. The object will appear to change its class.*

```
g++ -Wall -Wextra main.cpp .\10.state\1.gumball_machine.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
g++ -Wall -Wextra main.cpp .\10.state\2.gumball_machine_state.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
g++ -Wall -Wextra main.cpp .\10.state\2.gumball_machine_state_winner.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
 ```

 
### 10.Proxy: 

**_The Proxy Pattern_** *provides a surrogate or placeholder for another object to control access to it.*

```
 g++ -Wall -Wextra main.cpp .\9.composite\menu_composite.cpp -I"D:\design_patterns" -I"D:\design_patterns\9.composite"
```


To excute the excutable file:

`.\a.exe --reporter compact`

or with more precise details:

`.\a.exe --reporter compact --success`


