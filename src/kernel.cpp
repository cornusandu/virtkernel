#include <iostream>
#include "builtin.hpp"

#include "allocate.hpp"

#include "statemanager.hpp"

#include "management.hpp"

kernel::StateManager *state = nullptr;

extern "C" void main_();
extern "C" [[noreturn]] void _boot();

int main() {_boot();}

[[noreturn]] void _boot() {
    kallocate::_setup();
    state = new kernel::StateManager(0, 4096);
    main_(*state);
    ksys::exit(0);
    __builtin_unreachable();
}

void main_(kernel::StateManager& state) {
    std::cout << "Hello, World!" << std::endl;

    write(1, "Hi, there", strlen("Hi, there") - 2);
}
