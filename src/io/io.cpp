#include "../builtin.hpp"

_use_C __attribute__((visibility("default"))) void writeout(const char* const buffer, bool fd) noexcept {
    write(fd + 1, buffer, strlen(buffer));
}
