

#include "arpterm/main_application.hpp"
#include "arpterm/main_window.hpp"
//#include "arpterm/util.hpp"


#include <cassert>
#include <type_traits>


namespace at = arpterm;

//-----------------------------------------------------------------------------//
at::MainAppBundle& at::MainAppBundle::get() {
	static MainAppBundle main_app_bundle_;
	return main_app_bundle_;
}
//-----------------------------------------------------------------------------//
void
at::MainAppBundle::init(int argc, char* argv[], int master_fd) {
	this->app_ = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");
	this->window_vec_.reserve(1000);
	this->ptm_vec_.reserve(1000);
	this->window_vec_.emplace_back(new at::MainWindow {this->window_vec_.size()});
	this->ptm_vec_.emplace_back(master_fd);
}
//-----------------------------------------------------------------------------//
int
at::MainAppBundle::run() {
	//static_assert(std::is_same<std::remove_reference<
	//	decltype(*(this->window_vec_.back()))>::type, at::MainWindow>::value);

//	printf("type: %s\n", (good_type?"true":"false"));
	printf("%p\n", this->window_vec_.back().get());
	return this->app_->run(*(this->window_vec_.back()));
}
//-----------------------------------------------------------------------------//
Gtk::Window&
at::MainAppBundle::add_new_window() {
	this->window_vec_.emplace_back(new at::MainWindow {this->window_vec_.size()});
	auto& window = *(this->window_vec_.back());
	this->app_->add_window(window);
	return window;
}
//-----------------------------------------------------------------------------//
void
at::MainAppBundle::add_n_show_new_window() {
	this->add_new_window().show();
}
//-----------------------------------------------------------------------------//
void at::MainAppBundle::write(int index, const char* msg, size_t len) {
	write(this->ptm_vec_[index], msg, len);
}


