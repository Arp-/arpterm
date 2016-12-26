

#include <iostream>
#include "pty_widget/pty_widget.hpp"
#include <gtkmm/window.h>
#include <gtkmm/application.h>

namespace pw = pty_widget;

class TestWindow : public Gtk::Window { 

	public: 

		TestWindow(): ptw_() { 
			std::cout << __PRETTY_FUNCTION__ << std::endl;

			this->add(this->ptw_);
			this->show_all_children();
			this->ptw_.show();
		}

		virtual ~TestWindow() {};


	private: 

		pw::PtyWidget ptw_;

};


int main(int argc, char* argv[]) {
	std::cout << "test_main" << std::endl;

	auto app = Gtk::Application::create(argc,argv, "my.app.example");
	// OKAY SO CREATE WINDOW AFTER APPLICATION
	TestWindow w;
	//Gtk::Window w2;
	return app->run(w);

}
