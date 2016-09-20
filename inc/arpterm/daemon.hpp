

/**
 * Description:
 * The purpose of this daemon is to open pty-slaves, in a memorable way, that
 * i'm able to send specific commands to the specific slave
 */
#ifndef ARPTERM_DAEMON_HPP
#define ARPTERM_DAEMON_HPP

#include "arpterm/type.hpp"

namespace arpterm {

	namespace daemon {

		int init();

		int shutdown();

		arpterm::type::pty_t pty();


	}

} // namespace arpterm


#endif // ARPTERM_DAEMON_HPP


