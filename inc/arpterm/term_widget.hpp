
#ifndef ARPTERM_TERM_WIDGET_HPP
#define ARPTERM_TERM_WIDGET_HPP

#include <gtkmm/widget.h>

namespace arpterm {

	class TermWidget : Gtk::Widget {

		public: //-- public functions --//

			TermWidget();

			virtual ~TermWidget();


		protected: //-- protected widget functions --//

			Gtk::SizeRequestMode get_request_mode_vfunc() const override;

			void get_preferred_width_vfunc(
					int& min_width, int& natural_width) const override;

			void get_preferred_height_for_width_vfunc(
					int width, int& min_height, int& natural_height) const override;

			void get_preferred_height_vfunc(
					int& min_height, int& natural_height) const override;

			void get_preferred_width_for_height_vfunc(
					int height, int& min_width, int& natural_width) const override;

			void on_size_allocate(Gtk::Allocation& allocation) override;

			void on_map() override;

			void on_unmap() override;

			void on_realize() override;

			void on_unrealize() override;

			bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;



		private: //-- private functions --//


	};

} // namespace arpterm


#endif // ARPTERM_TERM_WIDGET_HPP
