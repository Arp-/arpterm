

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
//#include "arpterm/util.hpp"
#include "arpterm/pty_handler.hpp"
#include "arpterm/util/hash_map.hpp"
//#include "arpterm/cursor.hpp"
#include <thread>
#include <cstdio>


namespace au = arpterm::util;
namespace ap = arpterm::pty;
namespace a = arpterm;


static std::unique_ptr<Gtk::Window> new_window_ref_ { nullptr };

template <typename T, typename ...Args>
inline Glib::RefPtr<T> make_ref (Args&& ...args) {
	return Glib::RefPtr<T>(new T(std::forward<Args>(args)...));
}

std::string newlinify(const std::string& str) {
	std::string copy = str;
	for (auto it = copy.begin(); it != copy.end(); ++it) {
		if (*it == '\r' && *(it+1) == '\n') {
			copy.erase(it);
		} else if (*it == '\r') {
			*it = '\n';
		} 
	}
	return copy;
}

void print_by_char(const std::string& str) {
	for (const auto& ch : str) {
		if (ch == 0x20) {
			printf(" ");
		} else if (ch == '\r') {
			printf("\n");
		} else {
			printf("%c", ch & 0xff);
		}
	}
}

//-----------------------------------------------------------------------------//
int main(int argc, char *argv[]) {
	//void(*sigttou_handler)(int)
	//signal(SIGTTOU, &signal);



	//Glib::signal_timeout().connect(sigc::bind(&close_handler, master_fd), 1000);
//	std::string str = "macska\r\nteszta";
//	a::cursor<std::string> c(str);
//	std::cout << "----" << std::endl;
//	std::cout << str << std::endl;
//	std::cout << "index: " << c.index() << std::endl;
//	std::cout << "column_i: " << c.column_distance() << std::endl;
//	c.move_cur_up(2);
//	//c.move_to_line_end();
//	std::cout << "index: " << c.index() << std::endl;
//	std::cout << "----" << std::endl;
//	std::cout << str << std::endl;
//	std::cout << newlinify(str) << std::endl;
//	c.move_cur_right(20);
//	str[c.index()] = 'c';
//	std::cout << "----" << std::endl;
//	std::cout << newlinify(str) << std::endl;
//	std::cout << c.column_distance() << std::endl;
	//c.move_to_line_beg();
	//std::cout << "index: " << c.index() << std::endl;
	//std::cout << "char: " << str[c.index()] << std::endl;
	//c.move_to_prev_line_end();
	//std::cout << "index: " << c.index() << std::endl;
	//std::cout << "column_i: " << c.column_distance() << std::endl;



	auto& app = arpterm::MainAppBundle::get();
	app.init(argc,argv);
	return app.run();

}

