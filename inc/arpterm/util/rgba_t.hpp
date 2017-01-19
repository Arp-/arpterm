

#ifndef APRTERM_UTIL_RGBA_T_HPP
#define APRTERM_UTIL_RGBA_T_HPP

#include <cairomm/cairomm.h>

namespace arpterm { namespace util { 

	// Red, Green, Blue, and Alpha
	struct rgba_t {
			constexpr rgba_t(double r, double g, double b, double a):
					r(r), g(g), b(b), a(a) {}
			~rgba_t() = default;
			double r;
			double g;
			double b;
			double a;
	};

	inline void set_cairo_color(const Cairo::RefPtr<Cairo::Context>& cr, const rgba_t& c) {
		cr->set_source_rgba(c.r, c.g, c.b, c.a);
	}


} } // namespace util // namespace arpterm


#endif // APRTERM_UTIL_RGBA_T_HPP
