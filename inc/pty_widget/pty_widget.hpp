
#ifndef ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP
#define ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP

#include <gtkmm/widget.h>
#include "arpterm/unicode.hpp"
#include "generic_parser/command.hpp"

namespace au = arpterm::unicode;

namespace pty_widget {


	class PtyWidget : public Gtk::Widget {

		public: //-- private typedefs --//
			
			using sig_cb_t = sigc::slot<void(const std::string&)>;
			using sigh_t = sigc::signal<void(const std::string&)>;
			using comm_parser_t = 
				generic_parser::command_parser_t<PtyWidget, uint32_t>;
			using char_vec_t = comm_parser_t::char_vec_t;
			using parser_cb_t = comm_parser_t::param_func_t;


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


		public: //-- io handlers --//

			void on_output_received(const std::string& output);

			void on_input_received(uint32_t unichar);

		private: //-- private functions --//

			void push_back(uint32_t unichar); // well this is actually relatively okay


		private: //-- private members --//

			Glib::ustring buffer_;

			comm_parser_t xterm_stm_;




		private: //-- handler functions --//

			static void new_line_handler(PtyWidget& pw, const char_vec_t& cv);
			static void backspace_handler(PtyWidget& pw, const char_vec_t& cv);
			static void trap_handler(PtyWidget& pw, const char_vec_t& cv);





	};

} // namespace PtyWidget

#endif // ARPTERM_PTY_WIDGET_PTY_WIDGET_HPP

