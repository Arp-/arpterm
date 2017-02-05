
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

using com_parser_t = a::PtyWidget::com_parser_t;
using com_vec_t = com_parser_t::com_vec_t;
using char_vec_t = com_parser_t::char_vec_t;
using param_vec_t = com_parser_t::param_vec_t;

// NOTE avtually due to the uft8 communication, the com_vec_t should be
// equal std::vector<char>, change the static assert if you want 
// some other container
static_assert(std::is_same<std::vector<char>, char_vec_t>::value);


com_vec_t
a::XtermHandler::in::callback_list() {
	return {
	};
}
//-----------------------------------------------------------------------------//
com_vec_t
a::XtermHandler::out::callback_list() {
	return {
		{ {{0x1B,0x5B,0,0},{0x4B,0,0,0} }, &erase_in_line_handler },
		{ {{0x1B,0x5D,0,0},{0x07,0,0,0} }, &set_text_parameters_handler },
		{ {{0x08,0,0,0   },{0,0,0,0   } }, &backspace_handler},
		{ {{0x07,0,0,0   },{0,0,0,0   } }, &bell_handler},
	};
}
//-----------------------------------------------------------------------------//
// FUNCTIONS FOR IN //
void 
a::XtermHandler::in::trap_handler(a::PtyWidget& pw, 
		const char_vec_t& cv) {
	puts("IN_TRAP_FUNCTION");
	write(pw.master_fd_, cv.data(), cv.size());
}
//-----------------------------------------------------------------------------// void 
// FUNCTIONS FOR OUT //
void 
a::XtermHandler::out::trap_handler(a::PtyWidget& pw,
		const char_vec_t& cv) {
	std::cout << "OUT TRAP_FUNCTION" << std::endl;
	auto& recv_buf = pw.recv_buffer_;
	
	for (const auto& ch : cv) {
		// static cast because otherwise it'll be a gunichar overloded one
		recv_buf.push_back(ch); 
	}
}
//-----------------------------------------------------------------------------//
void
a::XtermHandler::out::erase_in_line_handler(a::PtyWidget& pw,
		const param_vec_t& pv) {
	puts("ERASE_IN_LINE_HANDLER");
	for (const auto& elem : pv) {
		std::cout << "vec: " << elem << std::endl;
	}
	auto& buf = pw.recv_buffer_;
	if (!buf.empty()) {
		std::cout << "bef: ";
		au::print_hex(buf.data(), buf.bytes());
		buf.resize(buf.bytes()-1);
	}
	std::cout << "af: ";
	au::print_hex(buf.data(), buf.bytes());
	buf.normalize();
}
//-----------------------------------------------------------------------------//
void a::XtermHandler::out::backspace_handler(a::PtyWidget& pw,
		const param_vec_t& pv) {
		for (const auto& elem : pv) {
			std::cout << "elem: " << elem << "\n";
		}
		std::cout << std::endl;
	// IGNORE CHAR BACKSPACE ERASE IN LINE IS WHAT HANDLES THE ERASURE OF TEXT
	// INSIDE THE BUFFER
}
//-----------------------------------------------------------------------------//
void a::XtermHandler::out::bell_handler(a::PtyWidget& pw,
		const param_vec_t& pv) {
	puts(__PRETTY_FUNCTION__);
	// IGNORE BELL FOR NOW TODO IMPLEMENT
}
//-----------------------------------------------------------------------------//
void a::XtermHandler::out::set_text_parameters_handler(a::PtyWidget& pw, 
		const param_vec_t& pv) {
	puts(__PRETTY_FUNCTION__);
	// TODO parse the parameter and set the title
	for (auto elem : pv) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

