

#ifndef ARPTERM_PTY_HANDLER_HPP
#define ARPTERM_PTY_HANDLER_HPP

#include <cstdlib>

namespace arpterm {

	namespace pty {

		// returns the fildescriptor of pty
//		int pty_open();
//
//		int get_pts(int pty_master_fd, char* pts_name, size_t pts_len);

		// returns master-fd, for gtkmm
		int start_pt_master_slave();

		int stop_all();



	} // namespace pty

} // namespace arpterm


#endif // ARPTERM_PTY_HANDLER_HPP
