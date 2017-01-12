

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/textview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/viewport.h>

#include "pty_widget/pty_widget.hpp"


namespace arpterm {

	class MainWindow : public Gtk::Window {

		public: //-- public functions --//

			MainWindow(size_t index);

			virtual ~MainWindow();

		protected: //-- pritected signal handlers --//

			bool on_key_pressed(GdkEventKey* ev_key);

			bool on_event(GdkEvent* ev_key);

			bool on_configure_event(GdkEventConfigure* ev);


		private: //-- private functions --//

			void init();

			void write(const char* msg, size_t len);


		private: //-- private variables --//

			pty_widget::PtyWidget pty_;

			size_t index_;





	};

} // namespace arpterm
