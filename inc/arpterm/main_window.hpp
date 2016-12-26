

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/textview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/viewport.h>

#include "pty_widget/pty_widget.hpp"


namespace arpterm {

	class MainWindow : public Gtk::Window {

		public: //-- public functions --//

			MainWindow();

			virtual ~MainWindow();

		protected: //-- pritected signal handlers --//

			bool on_key_pressed(GdkEventKey* ev_key);


		private: //-- private functions --//

			void init();


		private: //-- private variables --//

			pty_widget::PtyWidget pty_;



	};

} // namespace arpterm
