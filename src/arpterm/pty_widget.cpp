
#include "arpterm/pty_widget.hpp"
#include "arpterm/pty_handler.hpp"
#include "generic_parser/util.hpp"
#include "arpterm/xterm_handler.hpp"
#include "arpterm/util/util.hpp"
#include "arpterm/util/rgba_t.hpp"
#include "arpterm/util/termios.hpp"
#include "arpterm/util/sys/ioctl.hpp"
#include <utility>
#include <glibmm.h>

#ifdef DEBUG
#	include <iostream>
#endif

namespace a = arpterm;
namespace ap = arpterm::pty;
namespace au = arpterm::util;
namespace gpu = generic_parser::util;

a::PtyWidget::PtyWidget() :
		Glib::ObjectBase("PtyWidget"),
		Gtk::Widget(),
		recv_buffer_(),
		xterm_in_stm_(*this,
				XtermHandler::in::callback_list(), &XtermHandler::in::trap_handler),
		xterm_out_stm_(*this,
				XtermHandler::out::callback_list(), &XtermHandler::out::trap_handler),
		master_fd_(0),
		state_() { 
	this->set_has_window(false); // this is important!!!
	this->master_fd_ = ap::start_pt_master_slave();

	Glib::signal_timeout().connect(
			sigc::mem_fun(this, &a::PtyWidget::do_fd_read), 100);
}
//-----------------------------------------------------------------------------//
a::PtyWidget::~PtyWidget() {

}
//-----------------------------------------------------------------------------//
Gtk::SizeRequestMode
a::PtyWidget::get_request_mode_vfunc() const {
	return Gtk::Widget::get_request_mode_vfunc();
}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::get_preferred_width_vfunc(
		int& min_width, int& nat_width) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_width = 10;
	nat_width = 800;

}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::get_preferred_height_vfunc(
		int& min_height, int& nat_height) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_height = 10;
	nat_height = 600;

}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::get_preferred_width_for_height_vfunc(
		int height, int& min_width, int& nat_width) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_width = 10;
	nat_width = 800;

}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::get_preferred_height_for_width_vfunc(
		int width, int& min_height, int& nat_height) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_height = 10;
	nat_height = 600;

}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_size_allocate(Gtk::Allocation& allocation) {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	this->set_allocation(allocation);

}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_map() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_map();
}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_unmap() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_unmap();
}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_realize() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	struct winsize wsz = { 0, 0, 800, 600 };
	ioctl(this->master_fd_, TIOCSWINSZ, &wsz );
	Gtk::Widget::on_realize();
	//this->set_realized();
}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_unrealize() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_unrealize();
}
//-----------------------------------------------------------------------------//
bool
a::PtyWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	const Gtk::Allocation alloc = this->get_allocation();
	const auto& width  = alloc.get_width();
	const auto& height = alloc.get_height();
	const auto& x = alloc.get_x();
	const auto& y = alloc.get_y();

	auto background = get_style_context();
	printf("allocation: %d %d\n", width, height);

	cr->set_source_rgb(0.9,0.0,0.0);
	background->render_background(cr, x, y, width, height);
	au::set_cairo_color(cr,this->state_.font_color);
	Pango::FontDescription font;
	font.set_family("Monospace");
	//font.set_weight(Pango::WEIGHT_BOLD);
	auto layout = create_pango_layout(this->recv_buffer_);
	layout->set_font_description(font);
	layout->show_in_cairo_context(cr);

	return true;
}
//-----------------------------------------------------------------------------//
bool
a::PtyWidget::do_fd_read() {
	char buf[1000];
	int len = read(this->master_fd_, buf, sizeof(buf));
	if (len < 0) {
		if (errno == EAGAIN) {
			return true;
		}
		printf("GOT ERROR CLOSE\n");
		close(this->master_fd_);
		ap::stop(this->master_fd_);
		// TODO close parent
		return false;
	} else if (len == 0) {
		printf("GOT EOF CLOSE\n");
		close(this->master_fd_);
		ap::stop(this->master_fd_);
		// TODO close parent
		return false;
	}
	printf("buffer: \n");
	au::print_hex(buf, len);
	for (int i = 0; i < len; i++) {
		this->xterm_out_stm_.parse(buf[i] & 0xff);
		//this->recv_buffer_.push_back(buf[i]);
	}
	//this->recv_buffer_.append(static_cast<const char*>(buf), len);
	this->queue_draw();
	return true;
}
//-----------------------------------------------------------------------------//
static void print_buffer(const Glib::ustring ustr) {
	for (const auto& uc : ustr) {
		std::cout << (char)uc;
	}
	std::cout << std::endl;
}
//-----------------------------------------------------------------------------//
void
a::PtyWidget::on_input_received(gunichar unichar) {
	Glib::ustring repr;
	repr.push_back(unichar);
	const char* utf8_char_seq = repr.data();
	for (unsigned i = 0; i < repr.bytes(); i++) {
		this->xterm_in_stm_.parse(utf8_char_seq[i]);
	}

	//this->queue_draw();
}
//-----------------------------------------------------------------------------//

