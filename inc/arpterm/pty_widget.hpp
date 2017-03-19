
#ifndef ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP
#define ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP

#include <gtkmm/widget.h>
#include <gdkmm/color.h>
#include "generic_parser/command.hpp"
#include "generic_parser/xterm.hpp"
#include "arpterm/util/type.hpp"
#include "arpterm/default.hpp"
#include "arpterm/util/rgba_t.hpp"
//#include "arpterm/cursor.hpp"

namespace arpterm {


	class PtyWidget : public Gtk::Widget {

		friend class XtermHandler;

		// Stores the state fo the widget, like
		// colors etc
		// NOTE for bg_color use style_context??
		//
		struct state {
			state();
			~state() = default;
			arpterm::util::rgba_t font_color;
			arpterm::util::rgba_t bg_color;
		};

		public: //-- private typedefs --//
			
			using sig_cb_t = sigc::slot<void(const std::string&)>;
			using sigh_t = sigc::signal<void(const std::string&)>;
			using com_parser_t = 
				generic_parser::xterm<PtyWidget, char>;

		public: //-- public functions --//

			PtyWidget();

			virtual ~PtyWidget();


		protected: //-- protected gtkmm stuff --//

			Gtk::SizeRequestMode get_request_mode_vfunc() const override;

			void get_preferred_width_vfunc(
					int& min_width, int& nat_width) const override;

			void get_preferred_height_vfunc(
					int& min_height, int& nat_height) const override;

			void get_preferred_width_for_height_vfunc(
					int height, int& min_width, int& nat_width) const override;

			void get_preferred_height_for_width_vfunc(
					int width, int& min_height, int& nat_height) const override;

			void on_size_allocate(Gtk::Allocation& allocation) override;

			void on_map() override;

			void on_unmap() override;

			void on_realize() override;

			void on_unrealize() override;

			bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;


		protected: //-- proctected fd_signal_reader --//

			bool do_fd_read();


		public: //-- io handlers --//

			void on_input_received(uint32_t unichar);


		private: //-- private members --//

			Glib::ustring recv_buffer_;

			com_parser_t xterm_in_stm_;

			com_parser_t xterm_out_stm_;

			arpterm::util::type::fd_t master_fd_;

			//arpterm::cursor<decltype(recv_buffer_)> cursor_;

			state state_;











	};

} // namespace PtyWidget

#endif // ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP

