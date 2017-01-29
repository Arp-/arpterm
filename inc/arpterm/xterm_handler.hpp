#ifndef ARPTERM_XTERM_HANDLER_HPP
#define ARPTERM_XTERM_HANDLER_HPP

#include "arpterm/pty_widget.hpp"

namespace arpterm {

	struct XtermHandler {

		private: //-- private types --//
			using com_parser_t = PtyWidget::com_parser_t;
			using com_vec_t = com_parser_t::com_vec_t;
			using char_vec_t = com_parser_t::char_vec_t;
			using param_vec_t = com_parser_t::param_vec_t;

		public: //-- public stuff --//

		struct in {
			static com_vec_t callback_list();
			static void trap_handler(PtyWidget&, const char_vec_t&);
		};

		struct out {
			static com_vec_t callback_list();
			static void trap_handler(PtyWidget&, const char_vec_t&);
			static void erase_in_line_handler(PtyWidget&, const param_vec_t&);
		};

	};

}

#endif // ARPTERM_XTERM_HANDLER_HPP
