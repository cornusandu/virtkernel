#pragma once

#include "builtin.hpp"
#include "statemanager.hpp"
#include "management.hpp"
#include "io.hpp"
#include <iostream>

namespace kstd {
    _i void*(*allocate)(uint64_t, const kernel::StateManager& state) = nullptr;
}

namespace kallocate {
    _i void _setup() {

        auto lib = dlopen("./allocate.so", RTLD_LAZY | RTLD_LOCAL);

        if (!lib) {
            kstd::writeout("dlopen failed.\0", true);
            ksys::exit(1);
        }

        kstd::allocate = (void*(*)(uint64_t, const kernel::StateManager& state)) dlsym(lib, "allocate");

        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            kstd::writeout("dlsym failed: ", true);
            kstd::writeout(dlsym_error, true);
            kstd::writeout("\n\0", true);
            ksys::exit(1);
        }

        if (!kstd::allocate) {
            kstd::writeout("dlsym failed.", true);
            ksys::exit(1);
        }
    }
}
