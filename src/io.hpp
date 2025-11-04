#pragma once

#include "builtin.hpp"
#include "statemanager.hpp"
#include "management.hpp"
#include <iostream>

namespace {
    void output_write(const char* const message, bool fd = false) noexcept {
        write(fd + 1, message, strlen(message));
    }
}

namespace kstd {
    _i void(*writeout)(const char *const buffer, bool fd) = nullptr;
}

namespace kio {
    _i void _setup() {

        auto lib = dlopen("./io.so", RTLD_LAZY | RTLD_LOCAL);

        if (!lib) {
            output_write("[HOST FAILURE] dlopen failed.\0", 1);
            ksys::exit(1);
        }

        kstd::writeout = (void(*)(const char *const buffer, bool fd)) dlsym(lib, "writeout");

        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            output_write("[HOST FAILURE] dlsym failed:\0", 1);
            write(2, dlsym_error, strlen(dlsym_error));
            write(2, "\n", 1);
            ksys::exit(1);
        }

        if (!kstd::writeout) {
            output_write("[HOST FAILURE] dlsym failed.\0", 1);
            ksys::exit(1);
        }
    }
}
