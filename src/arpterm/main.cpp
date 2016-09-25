

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
#include "arpterm/util.hpp"


namespace au = arpterm::util;


static std::unique_ptr<Gtk::Window> new_window_ref_ { nullptr };

template <typename T, typename ...Args>
inline Glib::RefPtr<T> make_ref (Args&& ...args) {
	return Glib::RefPtr<T>(new T(args...));
}

//-----------------------------------------------------------------------------//
static bool timeout_handler(int num) {
	printf("ASDFGHJKLÉ\n");
	printf("num: %d\n", num);
	fflush(stdout);
	return true;
}
//-----------------------------------------------------------------------------//
static bool make_new_window() {
	arpterm::MainAppBundle::get().add_n_show_new_window();
	return false;
}
//-----------------------------------------------------------------------------//
int main(int argc, char *argv[]) {


	Glib::signal_timeout().connect(sigc::bind(&timeout_handler,5), 2000);

	auto& app = arpterm::MainAppBundle::get();
	app.init(argc,argv);
	Glib::signal_timeout().connect(sigc::ptr_fun(&make_new_window),5000);

	return app.run();
}

