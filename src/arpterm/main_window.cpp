

#include "arpterm/main_window.hpp"

namespace a = arpterm;


a::MainWindow::MainWindow() {
	init();
}
//-----------------------------------------------------------------------------//
a::MainWindow::~MainWindow() {

}
//-----------------------------------------------------------------------------//
void
a::MainWindow::init() {
	this->set_title("Macska");
	this->add_n_init_text_view();
	this->show_all_children();
}
//-----------------------------------------------------------------------------//
void
a::MainWindow::add_n_init_text_view() {
	this->set_n_init_text_buffer();
	this->text_view_.set_editable(false);
	this->add(this->text_view_);
}
//-----------------------------------------------------------------------------//
void
a::MainWindow::set_n_init_text_buffer() {
	const auto text_buffer = this->text_view_.get_buffer();
	text_buffer->insert_at_cursor("macska");
	text_buffer->insert_at_cursor("\n");
	text_buffer->insert_at_cursor("kacsa");

}
