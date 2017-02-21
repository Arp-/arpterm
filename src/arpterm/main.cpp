

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
	std::cout << "column_i: " << c.column_index() << std::endl;
	c.move_cur_up(2);
	//c.move_to_line_end();
	std::cout << "index: " << c.index() << std::endl;
	std::cout << str << std::endl;
	printf("frst: %02X\n", str[0]);
	printf("frst: %02X\n", str[1]);
	printf("frst: %02X\n", str[2]);
	printf("frst: %02X\n", str[3]);
	printf("frst: %02X\n", str[4]);
	printf("frst: %02X\n", str[5]);
	//c.move_to_line_beg();
	//std::cout << "index: " << c.index() << std::endl;
	//std::cout << "char: " << str[c.index()] << std::endl;
	//c.move_to_prev_line_end();
	//std::cout << "index: " << c.index() << std::endl;
	//std::cout << "column_i: " << c.column_index() << std::endl;



//	auto& app = arpterm::MainAppBundle::get();
//	app.init(argc,argv);
//	return app.run();

}

