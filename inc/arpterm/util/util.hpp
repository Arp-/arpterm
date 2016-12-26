

#ifndef ARPTERM_UTIL_HPP
#define ARPTERM_UTIL_HPP

namespace arpterm {

	namespace util {

		template <typename T, typename ...Args>
			inline std::unique_ptr<T> make_unique(Args&& ...args) {
				return std::unique_ptr<T>(new T(args...));
			}

	} // namespace util

} // namesapc arpterm

#endif // ARPTERM_UTIL_HPP
