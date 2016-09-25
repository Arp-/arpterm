

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/textview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/viewport.h>


namespace arpterm {

	class MainWindow : public Gtk::Window {

		public: //-- public functions --//

			MainWindow();

			virtual ~MainWindow();

			void new_tab();

			void close_tab(unsigned index);


		private: //-- private functions --//

			void init();

			void init_text_view_list();


		private: //-- private variables --//

			Gtk::Notebook notebook_;

			std::vector<std::shared_ptr<Gtk::TextView>> text_view_list_;



	};

} // namespace arpterm
