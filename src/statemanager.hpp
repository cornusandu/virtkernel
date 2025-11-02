#pragma once

#include <cstdint>
#include "builtin.hpp"

namespace kernel {
    struct StateManager {
        uint8_t ring;
        char* data;
        uint16_t stacksize;

        StateManager();
        StateManager(uint8_t ring, uint16_t stacksize);
        StateManager(const StateManager&);
    };
}