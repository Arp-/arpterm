

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/textview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/viewport.h>

#include "arpterm/pty_widget.hpp"


namespace arpterm {

	class MainWindow : public Gtk::Window {

		public: //-- public functions --//

			MainWindow();

			virtual ~MainWindow();

		protected: //-- pritected signal handlers --//

			bool on_key_pressed(GdkEventKey* ev_key);

			bool on_event(GdkEvent* ev_key);

			bool on_configure_event(GdkEventConfigure* ev);


		private: //-- private functions --//

			void init();


		private: //-- private variables --//

			arpterm::PtyWidget pty_;





	};

} // namespace arpterm
