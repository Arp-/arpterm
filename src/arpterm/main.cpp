

#include <gtkmm.h>
//#include <sigc++/sigc++.h>
#include <glibmm.h>
#include <memory>
#include "arpterm/main_window.hpp"
#include "arpterm/main_application.hpp"
//#include "arpterm/util.hpp"
//#include "arpterm/pty_handler.hpp"
#include "arpterm/util/hash_map.hpp"
#include <thread>


namespace au = arpterm::util;
//namespace ap = arpterm::pty;


static std::unique_ptr<Gtk::Window> new_window_ref_ { nullptr };

template <typename T, typename ...Args>
inline Glib::RefPtr<T> make_ref (Args&& ...args) {
	return Glib::RefPtr<T>(new T(std::forward<Args>(args)...));
}

//-----------------------------------------------------------------------------//
static bool timeout_handler(int master_fd) {
	write(master_fd, "teszta\n", 7);

	char buf[1000];
	int len = read(master_fd, &buf, sizeof(buf));
	int saved_errno = errno;
	if (len == 0) {
		printf("len was 0\n");
	}
	if (len == -1) {
		errno = saved_errno;
		perror("testzta");
		fprintf(stderr, "closing master_fd\n");
		close(master_fd);
	}
	printf("%.*s\n", len, buf);
	return true;
}
//-----------------------------------------------------------------------------//
static bool close_handler(int master_fd) {
	printf("called close_handler\n");

	char buf[1] = { '\x04' };
	write(master_fd, buf, 1);  // WRITE EOT
	//close(master_fd);

	//ap::stop_all(); // terminate childs
	//close(master_fd);
	return false;
}
////-----------------------------------------------------------------------------//
//static bool make_new_window() {
//	arpterm::MainAppBundle::get().add_n_show_new_window();
//	return false;
//}
////-----------------------------------------------------------------------------//
static void myfunc(std::string str) {
	while (true) {
		std::cout << str << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
int main(int argc, char *argv[]) {
//	char slave_name[100];
//	int master_fd = ap::pty_open();
//	int err = 0;
//	err = ap::get_pts(master_fd, slave_name, sizeof(slave_name));
 
//	printf("slave_name: %s\n", slave_name);
//	printf("master_fd: %d\n", master_fd);

//	while (true); // do some blocking to dunno


	//au::thread_list<10> list;
	//std::cout << "thread_list_size: " << list.size() << std::endl;

	//list.add(&myfunc, std::string{"macska"});
	//list.joinall();


	//int master_fd = ap::start_pt_master_slave();

	using my_hashmap = au::hash_map<int, std::string, 100>;
	my_hashmap h_map;
	h_map.set(5,"macska");
	h_map.set(5,"kacsa");
	h_map.set(4,"teszta");

	auto elem = h_map.get(4);
	if (elem != nullptr) {
		std::cout << "elem1: " << *elem << std::endl;
	} else {
		std::cout << "SOME ERROR OCCURED" << std::endl;
	}
	elem = h_map.get(5);
	std::cout << "elem2: " << *elem << std::endl;

	for (auto elem : h_map) {
		std::cout << elem.key << ":" << elem.val << std::endl;
	}



	//Glib::signal_timeout().connect(sigc::bind(&timeout_handler,master_fd), 2000);

	//Glib::signal_timeout().connect(sigc::bind(&close_handler, master_fd), 10000);

//
//	Glib::signal_timeout().connect(sigc::ptr_fun(&make_new_window),5000);
//
//
//
//
// MAIN APP
//	auto& app = arpterm::MainAppBundle::get();
//	app.init(argc,argv);
//	return app.run();

}

