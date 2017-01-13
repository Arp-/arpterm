
#include "arpterm/pty_widget.hpp"
#include "arpterm/pty_handler.hpp"
#include "generic_parser/util.hpp"
#include <utility>
#include <glibmm.h>

#ifdef DEBUG
#	include <iostream>
#endif

namespace a = arpterm;
namespace ap = arpterm::pty;
namespace gpu = generic_parser::util;

//-----------------------------------------------------------------------------//
void 
a::PtyWidget::new_line_handler(a::PtyWidget& pw,
		const a::PtyWidget::char_vec_t& cv) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	auto& com_buf = pw.command_buffer_;
	com_buf.push_back('\n');
	write(pw.master_fd_, com_buf.data(), com_buf.size());
	com_buf.erase();
	gpu::print_vec(cv);
}
//-----------------------------------------------------------------------------//
void 
a::PtyWidget::backspace_handler(a::PtyWidget& pw, 
		const a::PtyWidget::char_vec_t& cv) {
	auto& com_buf = pw.command_buffer_;
	if (!com_buf.empty()) {
		com_buf.erase(com_buf.size() -1, 1);
	}
}
//-----------------------------------------------------------------------------//
void 
a::PtyWidget::trap_handler(a::PtyWidget& pw, 
		const a::PtyWidget::char_vec_t& cv) {
	std::cout << "TRAP FUNCTION" << std::endl;
	gpu::print_vec(cv);
	auto& com_buf = pw.command_buffer_;
	for (const auto& ch : cv) {
		if (ch) {
			com_buf.push_back(ch);
		}
	}
}
//-----------------------------------------------------------------------------//
a::PtyWidget::PtyWidget() :
		Glib::ObjectBase("PtyWidget"),
		Gtk::Widget(),
		recv_buffer_(),
		command_buffer_(),
		xterm_stm_(*this),
		master_fd_(0) { 
	this->set_has_window(false); // this is important!!!
	this->xterm_stm_.add_command({'\n'}, &new_line_handler);
	this->xterm_stm_.add_command({'\r'}, &new_line_handler);
	this->xterm_stm_.add_command({'\b'}, &backspace_handler);
	//this->xterm_stm_.add_command({'m', 'a', 'c', 's', 'k', 'a'}, &macska_handler);
	//this->xterm_stm_.add_command({'a'}, &char_a_handler);
	this->xterm_stm_.set_trap(&trap_handler);
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

	//cr->set_source_rgb(0.9,0.0,0.0);
	background->render_background(cr, x, y, width, height);
	cr->set_source_rgb(0.5,0.9,0.5);
	Pango::FontDescription font;
	font.set_family("Monospace");
	//font.set_weight(Pango::WEIGHT_BOLD);
	auto layout = create_pango_layout(this->recv_buffer_ + this->command_buffer_);
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
	this->recv_buffer_.append(static_cast<const char*>(buf), len);
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
a::PtyWidget::on_input_received(uint32_t unichar) {
	this->xterm_stm_.parse(unichar);

	print_buffer(this->command_buffer_);
	this->queue_draw();
}
//-----------------------------------------------------------------------------//

