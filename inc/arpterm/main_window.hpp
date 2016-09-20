

#include <gtkmm/window.h>
#include <gtkmm/textview.h>


namespace arpterm {

	class MainWindow : public Gtk::Window {

		public: //-- public functions --//

			MainWindow();

			~MainWindow();


		private: //-- private functions --//

			void init();

			void add_n_init_text_view();

			void set_n_init_text_buffer();


		private: //-- private variables --//

			Gtk::TextView text_view_;

	};

} // namespace arpterm
