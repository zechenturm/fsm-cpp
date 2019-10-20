#ifndef FSM_FSM_HPP
#define FSM_FSM_HPP

#include <functional>
#include <map>
#include <vector>
#include <algorithm>

template <typename State>
class FSM
{
    public:
//        using TransitionFunc = std::function<void ()>;
        using TransitionFunc = void(*)(void);
//        using GuardFunc = std::function<bool(void)>;
        using GuardFunc = bool (*)();

        FSM(State initial): currentState(initial) {}

        void addTransition(State from, State to, GuardFunc guard, TransitionFunc transition)
        {
            transitions.emplace_back(Transition{from, to, guard, transition});
        }

        bool step()
        {
            const auto transition = std::find_if(begin(transitions), end(transitions), [&](Transition t){ return t.from == currentState && t.guard();});
            if(transition != transitions.end())
            {
                (*transition).transition();
                currentState = (*transition).to;
                return true;
            }
            return false;
        }

        void run()
        {
            while (step());
        }
    private:
        struct Transition
        {
            const State from;
            const State to;
            const GuardFunc guard;
            const TransitionFunc transition;
        };

        State currentState;
        std::vector<Transition> transitions;

};

#endif //FSM_FSM_HPP
