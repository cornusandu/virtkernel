#include <iostream>
#include "builtin.hpp"

#include "allocate.hpp"

#include "statemanager.hpp"

kernel::StateManager *state = nullptr;

int main();

extern "C" void _boot();

void _boot() {
    kallocate::_setup();
    state = new kernel::StateManager(0, 4096);
    uint8_t exitcode = main();
    syscall(SYS_exit, exitcode);
}

int main() {
    write(1, "Hi, there", strlen("Hi, there") - 2);
}
