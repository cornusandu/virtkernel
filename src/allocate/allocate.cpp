#include "../builtin.hpp"
#include <cstdint>
#include "../statemanager.hpp"
#include <iostream>

extern "C" void* allocate(uint64_t size, const kernel::StateManager& state) {
    auto prot = state.ring == 3 ? PROT_READ | PROT_WRITE : PROT_READ | PROT_WRITE | PROT_EXEC;
    auto _ = mmap(nullptr, size, prot, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (_ == MAP_FAILED || _ == nullptr) {
        std::cerr << "mmap failed: " << strerror(errno) << "\n";
        fflush(stdout);
        syscall(SYS_exit, 1);
    }
    return _;
}
