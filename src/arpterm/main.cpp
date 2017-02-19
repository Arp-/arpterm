

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
//#include "arpterm/util.hpp"
#include "arpterm/pty_handler.hpp"
#include "arpterm/util/hash_map.hpp"
#include "arpterm/cursor.hpp"
#include <thread>


namespace au = arpterm::util;
namespace ap = arpterm::pty;
namespace a = arpterm;


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
	std::string str = "macska\r\nteszta";
	a::cursor<std::string> c(str);
	std::cout << str << std::endl;
	std::cout << "index: " << c.index() << std::endl;
	c.move_cur_up(1);
	std::cout << "index: " << c.index() << std::endl;
	std::cout << "str[i]: " << str[c.index()] << std::endl;
	str[c.index()] = 'p';
	std::cout << str << std::endl;
	std::cout << "strlen: " << str.size() << std::endl;



//	auto& app = arpterm::MainAppBundle::get();
//	app.init(argc,argv);
//	return app.run();

}

