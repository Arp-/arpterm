

#ifndef ARPTERM_TYPE_HPP
#define ARPTERM_TYPE_HPP

#include <type_traits>

namespace arpterm {

	namespace type {

		template <typename T>
			struct hard_type {

				typedef typename std::remove_reference<T>::type val_t;

				hard_type() = default;
				hard_type(const val_t& v): val(v) {}
				hard_type(const hard_type<T>& hv): val(hv.val) {}

				hard_type<T>& operator=(const val_t&) = delete;
				hard_type<T>& operator=(val_t&&) = delete;

				val_t val;
			};

		typedef hard_type<int> pty_t;

	} // namespace type

} // namespace arpterm

#endif // ARPTERM_TYPE_HPP
