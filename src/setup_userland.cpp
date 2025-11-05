// --------------------  IN WORK  ---------------------
//
//
//
// Should set up seccomp notif for userland syscall implementation,
//   which will allow this 'kernel' to intercept program syscalls
//   and reinterpret them with custom implementations
//
// Please ignore this file as it is not finished yet.
//
//


#include "builtin.hpp"
#include <linux/seccomp.h>
#include <sys/ioctl.h>
#include <cstring>
#include <cerrno>
#include <cstdio>
#include "customsyscalls.hpp"

void seccomp_notify_loop(int listener_fd) {
    for (;;) {
        struct seccomp_notif req;
        struct seccomp_notif_resp resp;
        std::memset(&req, 0, sizeof(req));
        std::memset(&resp, 0, sizeof(resp));

        if (ioctl(listener_fd, SECCOMP_IOCTL_NOTIF_RECV, &req) == -1) {
            if (errno == EINTR) continue;
            perror("SECCOMP_IOCTL_NOTIF_RECV");
            break;
        }

        // let user code decide what to do; it must fill `resp`
        int rc = ksyscall::customsyscall(req, resp);
        if (rc != 0) {
            // If user handler failed, reply with -ENOSYS to the tracee
            resp.id = req.id;
            resp.val = -1;
            resp.error = ENOSYS;
            resp.flags = 0;
        } else {
            resp.id = req.id; // ensure id matches
        }

        if (ioctl(listener_fd, SECCOMP_IOCTL_NOTIF_SEND, &resp) == -1) {
            perror("SECCOMP_IOCTL_NOTIF_SEND");
            break;
        }
    }
}