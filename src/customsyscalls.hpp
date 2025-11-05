#pragma once

#include "builtin.hpp"
#include "statemanager.hpp"
#include "management.hpp"
#include "io.hpp"
#include <iostream>
#include <linux/seccomp.h>
#include <sys/ioctl.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

namespace kcsyscall {
    _i void(*customsyscall)(const struct seccomp_notif &req, struct seccomp_notif_resp &resp) = nullptr;
}

namespace kcsyscall_internal {
    _i void _setup() {

        auto lib = dlopen("./customsyscalls.so", RTLD_LAZY | RTLD_LOCAL);

        if (!lib) {
            kstd::writeout("dlopen failed.\0", true);
            ksys::exit(1);
        }

        kcsyscall::customsyscall = (void(*)(const struct seccomp_notif &req, struct seccomp_notif_resp &resp)) dlsym(lib, "customsyscall");

        const char* dlsym_error = dlerror();
        if (dlsym_error) {
            kstd::writeout("dlsym failed: ", true);
            kstd::writeout(dlsym_error, true);
            kstd::writeout("\n\0", true);
            ksys::exit(1);
        }

        if (!kcsyscall::customsyscall) {
            kstd::writeout("dlsym failed.", true);
            ksys::exit(1);
        }
    }
}
