# design_paterns
This project implements various design patterns in an individual program. So, to compile it, you need:

- g++ version: 12.2.0
- Windows OS: 10

### 1.Strategy: 

**_The Strategy Pattern_** *defines a family of algorithms, encapsulates each one, and makes them interchangeable. Strategy lets the algorithm vary independently from clients that use it.*

```
g++ -Wall -Wextra main.cpp 1.strategy\3.sim_u_duck_stategy.cpp -I"D:\design_patterns" -I"D:\design_patterns\1.strategy"
```

### 8.Template method: 

***_The Template Method Pattern_** *defines the skeleton of an algorithm in a method, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm’s structure.*

```
g++ -Wall -Wextra main.cpp 8.template_method\barista_template_method.cpp -I"D:\design_patterns" -I"D:\design_patterns\8.template_method"
```

### 10. State:

***_The State Pattern_** *allows an object to alter its behavior when its internal state changes. The object will appear to change its class.*

```
g++ -Wall -Wextra main.cpp .\10.state\1.gumball_machine.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
g++ -Wall -Wextra main.cpp .\10.state\2.gumball_machine_state.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
g++ -Wall -Wextra main.cpp .\10.state\2.gumball_machine_state_winner.cpp -I"D:\design_patterns" -I"D:\design_patterns\10.state"
 ```
To excute the excutable file:

`.\a.exe --reporter compact`

or with more precise details:

`.\a.exe --reporter compact --success`


