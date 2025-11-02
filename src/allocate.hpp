#include "builtin.hpp"
#include "statemanager.hpp"
#include <iostream>

namespace kstd {
    _i void*(*allocate)(uint64_t, const kernel::StateManager& state) = nullptr;
}

namespace kallocate {
    _i void _setup() {
        auto lib = dlopen("./allocate.so", RTLD_LAZY | RTLD_GLOBAL);

        if (!lib) {
            std::cerr << "dlopen failed: " << dlerror() << "\n";
            fflush(stdout);
            syscall(SYS_exit, 1);
        }

        kstd::allocate = (void*(*)(uint64_t, const kernel::StateManager& state)) dlsym(lib, "allocate");

        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            write(2, "dlsym failed: ", 14);
            write(2, dlsym_error, strlen(dlsym_error));
            write(2, "\n", 1);
            syscall(SYS_exit, 1);
        }

        if (!kstd::allocate) {
            std::cerr << "dlsym failed: " << dlerror() << "\n";
            fflush(stdout);
            syscall(SYS_exit, 1);
        }
    }
}
