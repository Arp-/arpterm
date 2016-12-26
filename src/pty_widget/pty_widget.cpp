

#include "pty_widget/pty_widget.hpp"
#include <utility>

#ifdef DEBUG
#include <iostream>
#endif

namespace pw = pty_widget;

//-----------------------------------------------------------------------------//
pw::PtyWidget::PtyWidget() :
		Glib::ObjectBase("PtyWidget"),
		Gtk::Widget() { 
	this->set_has_window(false); // this is important!!!
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
pw::PtyWidget::~PtyWidget() {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
Gtk::SizeRequestMode
pw::PtyWidget::get_request_mode_vfunc() const {
	std::cout << __PRETTY_FUNCTION__ << std::endl;
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

	min_height = 10;
	nat_height = 600;

	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_width_for_height_vfunc(
		int height, int& min_width, int& nat_width) const {

	min_width = 10;
	nat_width = 800;

	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::get_preferred_height_for_width_vfunc(
		int width, int& min_height, int& nat_height) const {

	min_height = 10;
	nat_height = 600;

	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_size_allocate(Gtk::Allocation& allocation) {

	this->set_allocation(allocation);

	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_map() {
	Gtk::Widget::on_map();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_unmap() {
	Gtk::Widget::on_unmap();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_realize() {
	Gtk::Widget::on_realize();
	//this->set_realized();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_unrealize() {
	Gtk::Widget::on_unrealize();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}
//-----------------------------------------------------------------------------//
bool
pw::PtyWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {

	std::cout << __PRETTY_FUNCTION__ << std::endl;
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
		std::cout << ustr;
	}
	std::cout << std::endl;
}
//-----------------------------------------------------------------------------//
void
pw::PtyWidget::on_input_received(gunichar unichar) {
this->buffer_.push_back(unichar);
print_buffer(this->buffer_);
this->queue_draw();
}
//-----------------------------------------------------------------------------//
