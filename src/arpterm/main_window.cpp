

#include "arpterm/main_window.hpp"

namespace a = arpterm;


//-----------------------------------------------------------------------------//
static void
set_n_init_text_buffer(Gtk::TextView& view) {
	const auto text_buffer = view.get_buffer();
	text_buffer->insert_at_cursor("macska");
	text_buffer->insert_at_cursor("\n");
	text_buffer->insert_at_cursor("kacsa\n");
	text_buffer->insert_at_cursor("teszta");
}
//-----------------------------------------------------------------------------//
//
//
//-----------------------------------------------------------------------------//
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
	this->init_text_view_list();
	this->notebook_.append_page(*(this->text_view_list_.front()));
	this->add(this->notebook_);
	this->show_all_children();
}
//-----------------------------------------------------------------------------//
//PRIVATES//
//-----------------------------------------------------------------------------//
void
a::MainWindow::init_text_view_list() {
	this->text_view_list_.emplace_back(std::make_shared<Gtk::TextView>());
	for (const auto view : this->text_view_list_) {
		set_n_init_text_buffer(*view);
	}
}
//-----------------------------------------------------------------------------//

