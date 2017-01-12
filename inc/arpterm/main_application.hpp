


#ifndef ARPTERM_MAIN_APPLICATION_HPP
#define ARPTERM_MAIN_APPLICATION_HPP

#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/textview.h>
#include <glibmm.h>
#include <vector>
#include <memory>

//#include "arpterm/util.hpp"

namespace arpterm {

	class MainWindow;

	class MainAppBundle { 

		public: //-- public functions --//

			~MainAppBundle() = default;

			static MainAppBundle& get();

			void init(int argc, char* argv[],int master_fd);

			void write(int index, const char* msg, size_t len);

			int run();

			Gtk::Window& add_new_window();

			void add_n_show_new_window();


		private: //-- private functions --//

			MainAppBundle() = default;

		private: //-- private inline functions --//


		private: //-- private variables --//

			Glib::RefPtr<Gtk::Application> app_;

			std::vector<std::unique_ptr<Gtk::Window>> window_vec_;

			std::vector<int> ptm_vec_;


	};

} // namespace arpterm

#endif // ARPTERM_MAIN_APPLICATION_HPP
