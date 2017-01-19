#ifndef ARPTERM_XTERM_HANDLER_HPP
#define ARPTERM_XTERM_HANDLER_HPP

#include "arpterm/pty_widget.hpp"

namespace arpterm {

	struct XtermHandler {

		struct in {
			static PtyWidget::com_vec_t callback_list();
			static void trap_handler(PtyWidget&, const PtyWidget::char_vec_t&);

			static void new_line_handler(PtyWidget&, const PtyWidget::char_vec_t&);
			static void backspace_handler(PtyWidget&, const PtyWidget::char_vec_t&);
			static void ctrl_c_handler(PtyWidget&, const PtyWidget::char_vec_t&);
			static void ctrl_d_handler(PtyWidget&, const PtyWidget::char_vec_t&);
		};

		struct out {
			static PtyWidget::com_vec_t callback_list();
			static void trap_handler(PtyWidget&, const PtyWidget::char_vec_t&);
		};

	};

}

#endif // ARPTERM_XTERM_HANDLER_HPP
