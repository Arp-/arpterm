

#include "arpterm/pty_handler.hpp"
#include "arpterm/util/fcntl.hpp"
#include "arpterm/util/errno.hpp"
#include "arpterm/util/unistd.hpp"
#include <cstring>
#include <cstdlib>

namespace ap = arpterm::pty;

inline void errno_save_n_close(int fd) {
	int saved_errno = errno;
	close(fd);
	errno = saved_errno;
}
//-----------------------------------------------------------------------------//
int ap::pty_open() {

	int master_fd = posix_openpt(O_RDWR | O_NOCTTY);
	if (master_fd == -1) {
		return -1;
	}

	if (grantpt(master_fd) == -1) {
		errno_save_n_close(master_fd);
		return -1;
	}

	if (unlockpt(master_fd) == -1) {
		errno_save_n_close(master_fd);
		return -1;
	}
	return master_fd;
}
//-----------------------------------------------------------------------------//
int ap::get_pts(int master_fd, char* slave_name, size_t sn_len) {
	char* p = ptsname(master_fd);
	if (p == nullptr) {
		errno_save_n_close(master_fd);
		return -1;
	}

	if (strlen(p) < sn_len) {
		strncpy(slave_name, p, sn_len);
	} else {
		close(master_fd);
		errno = EOVERFLOW;
		return -1;
	}
	return master_fd;
}
