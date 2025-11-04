#include <iostream>
#include "builtin.hpp"

#include "allocate.hpp"
#include "io.hpp"
#include "statemanager.hpp"
#include "management.hpp"

kernel::StateManager *state = nullptr;

extern "C" void main_(kernel::StateManager& state);
extern "C" [[noreturn]] void _boot();

int main() {_boot(); return 0xFFFF;}  // if 0xFFFF is returned, UB was reached  --  a [[noreturn]] function that shouldn't return has returned.

[[noreturn]] void _boot() {
    kio::_setup();
    kallocate::_setup();
    state = new kernel::StateManager(0, 4096);
    main_(*state);
    exit(0);
    __builtin_unreachable();
}

void main_(kernel::StateManager& state) {
    kstd::writeout("Hello, World!", 0);
}
