# fsm-cpp
Simple generic Sate Machine implementation in C++11

## example

```
#include <iostream>
#include "fsm.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;

    enum States {INIT, DONE, EXIT};
    auto fsm = FSM<States>{INIT};
    fsm.addTransition(INIT, DONE, [](){return true;}, []()
    {
        std::cout << "Init!\n";
    });

    fsm.addTransition(DONE, EXIT, [](){return true;}, []()
    {
        std::cout << "Done!\n";
    });

    fsm.run();
    return 0;
}
```


## Guards

The first lambda serves as a guard: the transition is only executed if it returns true.

```
int main() {
    std::cout << "Hello, World!" << std::endl;

    enum States {INIT, DONE, EXIT};
    auto fsm = FSM<States>{INIT};
    fsm.addTransition(INIT, DONE, [](){return false;}, []()
    {
        std::cout << "Init!\n";
    });

    fsm.addTransition(INIT, DONE, [](){return true;}, []()
    {
        std::cout << "Init2!\n";
    });

    fsm.addTransition(DONE, EXIT, [](){return true;}, []()
    {
        std::cout << "Done!\n";
    });

    fsm.run();
    return 0;
}
```

Here, only "Init false" will be printed, since the first transitions guard returns false. Note that transitions are considered in the order they are added.
