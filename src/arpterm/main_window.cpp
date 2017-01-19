// アイカン ヂグラフ

#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
#include "arpterm/control_character_layer.hpp"
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
a::MainWindow::~MainWindow() { }
//-----------------------------------------------------------------------------//
//PRIVATES//
//-----------------------------------------------------------------------------//
void
a::MainWindow::init() {
	this->set_events(
			Gdk::EXPOSURE_MASK | 
			Gdk::STRUCTURE_MASK |
			Gdk::KEY_PRESS_MASK);
	this->signal_event().connect(
			sigc::mem_fun(*this, &a::MainWindow::on_event));
	//this->signal_configure_event().connect(
	//		sigc::mem_fun(*this, &a::MainWindow::on_configure_event));

	this->set_title("arpterm");
	this->add(pty_);
	this->show_all_children();
}
//-----------------------------------------------------------------------------//
//PROTECED//
//-----------------------------------------------------------------------------//
bool
a::MainWindow::on_key_pressed(GdkEventKey* ev_key) {
	gunichar uc = gdk_keyval_to_unicode(ev_key->keyval);
	const auto& st = ev_key->state;
	// TODO make a ctrl-c,d etc. --> to ascii conversation layer
	this->pty_.on_input_received(a::control_character_layer(st, uc));
	return false;
}
//-----------------------------------------------------------------------------//
bool
a::MainWindow::on_event(GdkEvent* ev_key) {
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	if (ev_key->type == Gdk::EventType::KEY_PRESS) {
		this->on_key_pressed(reinterpret_cast<GdkEventKey*>(ev_key));
	} else if (ev_key->type == Gdk::EventType::EXPOSE) {
		this->queue_draw();
		this->show_all_children();
	} else if (ev_key->type == Gdk::EventType::CONFIGURE) {
		this->on_configure_event(reinterpret_cast<GdkEventConfigure*>(ev_key));
	}
	return true;
}
//-----------------------------------------------------------------------------//
bool
a::MainWindow::on_configure_event(GdkEventConfigure* ev) {
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	this->queue_allocate();
	this->queue_draw();
	return true;
}
