#include "../builtin.hpp"
#include <iostream>
#include <linux/seccomp.h>
#include <sys/ioctl.h>
#include <cstring>
#include <cerrno>
#include <cstdio>

_use_C void customsyscall(const struct seccomp_notif &req, struct seccomp_notif_resp &resp);

_use_C void customsyscall(const struct seccomp_notif &req, struct seccomp_notif_resp &resp) {
    // Initialize response
    memset(&resp, 0, sizeof(resp));
    resp.id = req.id;
    resp.flags = 0;

    // Identify the syscall
    if (req.data.nr == SYS_write) {
        // Extract arguments (from the seccomp_notif_data struct)
        // write(int fd, const void *buf, size_t count)
        unsigned long fd     = req.data.args[0];
        unsigned long bufptr = req.data.args[1];
        unsigned long count  = req.data.args[2];

        // For this example, we ignore the fd and read the buffer from the traced process
        // In real life, you’d use process_vm_readv() or similar to copy data from the target
        // For demonstration, we’ll just print a placeholder
        std::cout << "[customsyscall] Intercepted write() for fd " << fd
                  << ", count = " << count << std::endl;

        // Here, you would normally read 'count' bytes from bufptr in the tracee
        // and emulate writing to stdout. Example (pseudo-emulation):
        //
        // char buffer[256];
        // ssize_t copied = process_vm_readv(pid, ...);
        // write(STDOUT_FILENO, buffer, copied);

        // Respond with a fake success (e.g., all bytes "written")
        resp.val = count;  // Number of bytes written
        resp.error = 0;
    } else {
        // Unsupported syscall
        resp.val = -1;
        resp.error = -ENOSYS;
    }
}
