

#ifndef ARPTERM_PTY_HANDLER_HPP
#define ARPTERM_PTY_HANDLER_HPP

#include <cstdlib>

namespace arpterm {

	namespace pty {

		// returns the fildescriptor of pty
		int pty_open();

		int get_pts(int pty_master_fd, char* pts_name, size_t pts_len);


	} // namespace pty

} // namespace arpterm


#endif // ARPTERM_PTY_HANDLER_HPP
