
#include "arpterm/pty_widget.hpp"
#include "arpterm/xterm_handler.hpp"
#include "arpterm/util/util.hpp"

#ifdef DEBUG
#include <iostream>
#include "generic_parser/util.hpp"
namespace  gpu = generic_parser::util;
#endif

namespace a = arpterm;
namespace au = arpterm::util;



a::PtyWidget::com_vec_t
a::XtermHandler::in::callback_list() {
	return {
		{ {'\n'}, &a::XtermHandler::in::new_line_handler },
		{ {'\r'}, &a::XtermHandler::in::new_line_handler },
		{ {'\b'}, &a::XtermHandler::in::backspace_handler },
	};
}
//-----------------------------------------------------------------------------//
a::PtyWidget::com_vec_t
a::XtermHandler::out::callback_list() {
	return {
		{ {0xff, 0xbf, 0xbf, 0xbf}, &a::XtermHandler::out::ffbfbfbf_handler},
	};
}
//-----------------------------------------------------------------------------//
// FUNCTIONS FOR IN //
void 
a::XtermHandler::in::trap_handler(a::PtyWidget& pw, 
		const a::PtyWidget::char_vec_t& cv) {
	std::cout << "IN TRAP FUNCTION" << std::endl;
	auto& com_buf = pw.command_buffer_;
	for (const auto& ch : cv) {
		if (ch) {
			com_buf.push_back(ch & 0xff);
		}
	}
	au::print_hex(com_buf.data(), com_buf.bytes());
	if (!com_buf.validate()) {
		puts("INVALID UTF8 INPUT BUFFER!");
	}
}
//-----------------------------------------------------------------------------// void 
void
a::XtermHandler::in::new_line_handler(a::PtyWidget& pw,
		const a::PtyWidget::char_vec_t& cv) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	auto& com_buf = pw.command_buffer_;
	com_buf.push_back('\n');
	for (unsigned i = 0; i < com_buf.bytes(); i++) {
		printf("%08X\n", com_buf.data()[i]);
	}
	std::cout << "BYTES: " << com_buf.bytes() << std::endl;
	au::print_hex(com_buf.data(), com_buf.bytes());
	write(pw.master_fd_, com_buf.data(), com_buf.bytes());
	com_buf.erase();
	gpu::print_vec(cv);
}
//-----------------------------------------------------------------------------//
void 
a::XtermHandler::in::backspace_handler(a::PtyWidget& pw, 
		const a::PtyWidget::char_vec_t& cv) {
	puts(__PRETTY_FUNCTION__);
	auto& com_buf = pw.command_buffer_;
	if (!com_buf.empty()) {
		com_buf.erase(com_buf.size() -1, 1);
	}
}
//-----------------------------------------------------------------------------//
// FUNCTIONS FOR OUT //
void 
a::XtermHandler::out::trap_handler(a::PtyWidget& pw,
		const a::PtyWidget::char_vec_t& cv) {
	//std::cout << "OUT TRAP_FUNCTION" << std::endl;
	auto& recv_buf = pw.recv_buffer_;

	for (const gunichar& ch : cv) {
		// static cast because otherwise it'll be a gunichar overloded one
		recv_buf.push_back(static_cast<char>(ch & 0xff)); 
	}
	if (!recv_buf.validate()) {
		puts("INVALID UTF8 OUTPUT BUFFFER");
		au::print_hex(recv_buf.data(), recv_buf.bytes());
	} else {
		puts("VALID UTF8 OUTPUT BUFFER");
		au::print_hex(recv_buf.data(), recv_buf.bytes());
	}
}
//-----------------------------------------------------------------------------//
void a::XtermHandler::out::ffbfbfbf_handler(a::PtyWidget& pw,
		const a::PtyWidget::char_vec_t& cv) {
	
	puts(__PRETTY_FUNCTION__);
}
