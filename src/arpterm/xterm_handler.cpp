
#include "arpterm/pty_widget.hpp"
#include "arpterm/xterm_handler.hpp"
#include "arpterm/util/util.hpp"
#include <type_traits>

#ifdef DEBUG
#include <iostream>
#include "generic_parser/util.hpp"
namespace  gpu = generic_parser::util;
#endif

namespace a = arpterm;
namespace au = arpterm::util;
using pw_char_vec_t = a::PtyWidget::char_vec_t;


// NOTE avtually due to the uft8 communication, the com_vec_t should be
// equal std::vector<char>, change the static assert if you want 
// some other container
static_assert(std::is_same<std::vector<char>, pw_char_vec_t>::value);


a::PtyWidget::com_vec_t 

a::XtermHandler::in::callback_list() {
	return {
		{ {'\n'}, &a::XtermHandler::in::new_line_handler },
		{ {'\r'}, &a::XtermHandler::in::new_line_handler },
		{ {'\b'}, &a::XtermHandler::in::backspace_handler },
		//{ {0x03}, &a::XtermHandler::in::ctrl_c_handler },
		//{ {0x04}, &a::XtermHandler::in::ctrl_d_handler }
	};
}
//-----------------------------------------------------------------------------//
a::PtyWidget::com_vec_t
a::XtermHandler::out::callback_list() {
	return {
		{ { 0x1B, 0x5B, 0x4B }, &a::XtermHandler::out::erase_in_line_to_rigth },
		{ { 0x1B, 0x5B, 0x00, 0x4B }, &a::XtermHandler::out::erase_in_line_to_rigth }
	};
}
//-----------------------------------------------------------------------------//
// FUNCTIONS FOR IN //
void 
a::XtermHandler::in::trap_handler(a::PtyWidget& pw, 
		const pw_char_vec_t& cv) {
	write(pw.master_fd_, cv.data(), cv.size());
}
//-----------------------------------------------------------------------------// void 
void
a::XtermHandler::in::new_line_handler(a::PtyWidget& pw,
		const pw_char_vec_t& cv) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	write(pw.master_fd_, "\n", 1);
}
//-----------------------------------------------------------------------------//
void 
a::XtermHandler::in::backspace_handler(a::PtyWidget& pw, 
		const pw_char_vec_t& cv) {
	puts(__PRETTY_FUNCTION__);
	write(pw.master_fd_,"\b", 1);
}
//-----------------------------------------------------------------------------//
void
a::XtermHandler::in::ctrl_c_handler(PtyWidget& pw,
		const pw_char_vec_t& cv) {
	puts(__PRETTY_FUNCTION__);

}
//-----------------------------------------------------------------------------//
void
a::XtermHandler::in::ctrl_d_handler(PtyWidget& pw,
		const pw_char_vec_t& cv) {
	puts(__PRETTY_FUNCTION__);

}
//-----------------------------------------------------------------------------//
// FUNCTIONS FOR OUT //
void 
a::XtermHandler::out::trap_handler(a::PtyWidget& pw,
		const pw_char_vec_t& cv) {
	//std::cout << "OUT TRAP_FUNCTION" << std::endl;
	auto& recv_buf = pw.recv_buffer_;

	for (const auto& ch : cv) {
		// static cast because otherwise it'll be a gunichar overloded one
		recv_buf.push_back(ch); 
	}
}
//-----------------------------------------------------------------------------//
void
a::XtermHandler::out::erase_in_line_to_rigth(a::PtyWidget& pw,
		const pw_char_vec_t& cv) {
	const auto& recv_buf = pw.recv_buffer_;
	pw.recv_buffer_.erase(recv_buf.size()-2);
}
