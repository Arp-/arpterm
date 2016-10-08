

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
#include "arpterm/util.hpp"
#include "arpterm/pty_handler.hpp"


namespace au = arpterm::util;


static std::unique_ptr<Gtk::Window> new_window_ref_ { nullptr };

template <typename T, typename ...Args>
inline Glib::RefPtr<T> make_ref (Args&& ...args) {
	return Glib::RefPtr<T>(new T(args...));
}

//-----------------------------------------------------------------------------//
//static bool timeout_handler(int num) {
//	printf("ASDFGHJKLÉ\n");
//	printf("num: %d\n", num);
//	fflush(stdout);
//	return true;
//}
////-----------------------------------------------------------------------------//
//static bool make_new_window() {
//	arpterm::MainAppBundle::get().add_n_show_new_window();
//	return false;
//}
////-----------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
	namespace ap = arpterm::pty;
	char slave_name[100];
	int master_fd = ap::get_pts(ap::pty_open(), slave_name, sizeof(slave_name));
 
	printf("master_fd: %d\n", master_fd);
	printf("slave_name: %s\n", slave_name);

	while (true); // do some blocking to dunno







//	Glib::signal_timeout().connect(sigc::bind(&timeout_handler,5), 2000);
//
//	auto& app = arpterm::MainAppBundle::get();
//	app.init(argc,argv);
//	Glib::signal_timeout().connect(sigc::ptr_fun(&make_new_window),5000);
//
//	return app.run();

}

