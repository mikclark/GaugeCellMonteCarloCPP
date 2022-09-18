#include "state.h"
#include <iostream>

void test_state(){
    State state(10.0);
    std::cout << "Empty state:" << std::endl;
    std::cout << state.toString() << std::endl;
    state.add(1.0,1.0,1.0,1);
    std::cout << "State with one element:" << std::endl;
    std::cout << state.toString() << std::endl;
    state.add(1.1,1.2,1.3,2);
    std::cout << "State with two elements:" << std::endl;
    std::cout << state.toString() << std::endl;

    State state2(state);
    std::cout << "Copied state from state:" << std::endl;
    std::cout << state2.toString() << std::endl;

    State state3(10.0, state.x, state.y, state.z, state.t);
    std::cout << "Copied state from components:" << std::endl;
    std::cout << state3.toString() << std::endl;
    
    State state4(2.0, state.x, state.y, state.z, state.t);
    std::cout << "Copied state from components, with truncation expected:" << std::endl;
    std::cout << state4.toString() << std::endl;
    
    State stateR1(10.0);
    stateR1.fillRandom({5});
    std::cout << "Random-generated state, one species:" << std::endl;
    std::cout << stateR1.toString() << std::endl;

    State stateR3(10.0);
    stateR3.fillRandom({1, 2, 3});
    std::cout << "Random-generated state, three species:" << std::endl;
    std::cout << stateR3.toString() << std::endl;
}
