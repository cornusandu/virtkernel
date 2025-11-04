#include "builtin.hpp"
#include <iostream>

namespace ksys {
    extern "C" void __cxa_finalize(void* d);
    extern "C" void (*__fini_array_start[])();
    extern "C" void (*__fini_array_end[])();

    inline void cleanup() noexcept {
        std::cout.flush();
        std::cerr.flush();
        std::clog.flush();

        for (auto f = __fini_array_end; f != __fini_array_start;) {  // Call deconstructors
            (*--f)();
        }
        __cxa_finalize(nullptr);
    }

    [[noreturn]] inline void exit(uint8_t code = 0) noexcept {
        syscall(SYS_exit, static_cast<long>(code));
        __builtin_unreachable();
    }

    [[noreturn]] inline void exit(uint8_t code, const std::string& msg) noexcept {
        std::cerr << msg << std::endl;
        ksys::exit(code);
    }
}
