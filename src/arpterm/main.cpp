

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
//#include "arpterm/util.hpp"
#include "arpterm/pty_handler.hpp"
#include "arpterm/util/hash_map.hpp"
#include <thread>


namespace au = arpterm::util;
namespace ap = arpterm::pty;


static std::unique_ptr<Gtk::Window> new_window_ref_ { nullptr };

template <typename T, typename ...Args>
inline Glib::RefPtr<T> make_ref (Args&& ...args) {
	return Glib::RefPtr<T>(new T(std::forward<Args>(args)...));
}

//void signal(int sig) {
//	printf("SALLED SIGGTOU\n");
//}


//-----------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
	//void(*sigttou_handler)(int)
	//signal(SIGTTOU, &signal);



	//Glib::signal_timeout().connect(sigc::bind(&close_handler, master_fd), 1000);

	auto& app = arpterm::MainAppBundle::get();
	app.init(argc,argv);
	return app.run();

}

