
#include "pty_widget/pty_widget.hpp"
#include "generic_parser/util.hpp"
#include <utility>

#ifdef DEBUG
#	include <iostream>
#endif

namespace pw = pty_widget;
namespace gpu = generic_parser::util;

//-----------------------------------------------------------------------------//
void 
pw::PtyWidget::new_line_handler(pw::PtyWidget& pw,
		const pw::PtyWidget::char_vec_t& cv) {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	pw.buffer_.push_back('\n');
	gpu::print_vec(cv);

}
//-----------------------------------------------------------------------------//
void 
pw::PtyWidget::backspace_handler(pw::PtyWidget& pw, 
		const pw::PtyWidget::char_vec_t& cv) {
	if (!pw.buffer_.empty()) {
		pw.buffer_.erase(pw.buffer_.size() -1, 1);
	}
}
//-----------------------------------------------------------------------------//
void 
pw::PtyWidget::trap_handler(pw::PtyWidget& pw, 
		const pw::PtyWidget::char_vec_t& cv) {
	std::cout << "TRAP FUNCTION" << std::endl;
	gpu::print_vec(cv);
	for (const auto& ch : cv) {
		if (ch) {
			pw.push_back(ch);
		}
	}
}
//-----------------------------------------------------------------------------//
pw::PtyWidget::PtyWidget() :
		Glib::ObjectBase("PtyWidget"),
		Gtk::Widget(),
		buffer_(),
		xterm_stm_(*this) { 
	this->set_has_window(false); // this is important!!!
	this->xterm_stm_.add_command({'\n'}, &new_line_handler);
	this->xterm_stm_.add_command({'\r'}, &new_line_handler);
	this->xterm_stm_.add_command({'\b'}, &backspace_handler);
	//this->xterm_stm_.add_command({'m', 'a', 'c', 's', 'k', 'a'}, &macska_handler);
	//this->xterm_stm_.add_command({'a'}, &char_a_handler);
	this->xterm_stm_.set_trap(&trap_handler);

}
//-----------------------------------------------------------------------------//
pw::PtyWidget::~PtyWidget() {

}
//-----------------------------------------------------------------------------//
Gtk::SizeRequestMode
pw::PtyWidget::get_request_mode_vfunc() const {
	return Gtk::Widget::get_request_mode_vfunc();
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_width_vfunc(
		int& min_width, int& nat_width) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_width = 10;
	nat_width = 800;

}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_height_vfunc(
		int& min_height, int& nat_height) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_height = 10;
	nat_height = 600;

}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_width_for_height_vfunc(
		int height, int& min_width, int& nat_width) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_width = 10;
	nat_width = 800;

}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_height_for_width_vfunc(
		int width, int& min_height, int& nat_height) const {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	min_height = 10;
	nat_height = 600;

}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_size_allocate(Gtk::Allocation& allocation) {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	this->set_allocation(allocation);

}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_map() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_map();
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_unmap() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_unmap();
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_realize() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_realize();
	//this->set_realized();
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_unrealize() {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Gtk::Widget::on_unrealize();
}
//-----------------------------------------------------------------------------//
bool
pw::PtyWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

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
	auto layout = create_pango_layout(this->buffer_);

	layout->set_font_description(font);
	layout->show_in_cairo_context(cr);

	return true;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_output_received(const std::string& str) {
	std::cout << "output: " << str << std::endl;
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
pw::PtyWidget::on_input_received(uint32_t unichar) {
	this->xterm_stm_.parse(unichar);

	print_buffer(this->buffer_);
	this->queue_draw();
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::push_back(uint32_t unichar) {
	this->buffer_.push_back(unichar);
}
