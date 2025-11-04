#include "statemanager.hpp"
#include "allocate.hpp"
#include "io.hpp"

using namespace kernel;

StateManager::StateManager(): stacksize(2), ring(3) {
    data = static_cast<char*>(kstd::allocate(stacksize, *this));

    if (data == nullptr || data == MAP_FAILED) {
        kstd::writeout("alloc failed in default constructor\n\0", true);
        ksys::exit(1);
    }
}

StateManager::StateManager(uint8_t ring, uint16_t stacksize): stacksize(stacksize), ring(ring) {
    data = static_cast<char*>(kstd::allocate(stacksize, *this));

    if (data == nullptr || data == MAP_FAILED) {
        kstd::writeout("alloc failed in default constructor\n\0", true);
        ksys::exit(1);
    }
}

StateManager::StateManager(const StateManager& other) {
    ring=other.ring;
    stacksize=other.stacksize;
    data=(char*)kstd::allocate(stacksize, other);

    if (!data || data == MAP_FAILED) {
        kstd::writeout("alloc failed in copy constructor\n\0", true);
        ksys::exit(1);
    }

    memcpy(data, other.data, stacksize);
}
