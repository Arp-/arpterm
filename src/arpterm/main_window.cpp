

#include "arpterm/main_window.hpp"
#include "arpterm/unicode.hpp"
#include <cstdint>
#include <cstdlib>
#ifdef DEBUG
#include <iostream>
#endif

namespace a = arpterm;


//-----------------------------------------------------------------------------//
a::MainWindow::MainWindow() {
	init();
}
//-----------------------------------------------------------------------------//
a::MainWindow::~MainWindow() {

}
//-----------------------------------------------------------------------------//
//PRIVATES//
//-----------------------------------------------------------------------------//
void
a::MainWindow::init() {
	this->set_events(
			Gdk::EXPOSURE_MASK | 
			Gdk::KEY_PRESS_MASK);
	this->signal_key_press_event().connect(
			sigc::mem_fun(*this, &a::MainWindow::on_key_pressed));

	this->set_title("arpterm");
	this->add(pty_);
	this->show_all_children();
}
//-----------------------------------------------------------------------------//
//PROTECED//
//-----------------------------------------------------------------------------//
bool
a::MainWindow::on_key_pressed(GdkEventKey* ev_key) {
	using a::unicode::unicode_type;
	uint32_t uc = gdk_keyval_to_unicode(ev_key->keyval);
	this->pty_.on_input_received(uc);
	return false;
}
