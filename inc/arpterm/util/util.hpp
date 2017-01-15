

#ifndef ARPTERM_UTIL_HPP
#define ARPTERM_UTIL_HPP

namespace arpterm {

	namespace util {

		template <typename T, typename ...Args>
			inline std::unique_ptr<T> make_unique(Args&& ...args) {
				return std::unique_ptr<T>(new T(args...));
			}

		inline void print_hex(const char* buf, size_t len) {
			printf("0x");
			for (size_t i = 0; i < len; i++) {
				printf("%02X", buf[i] & 0xff);
			}
			printf("\n");
		}

	} // namespace util

} // namesapc arpterm

#endif // ARPTERM_UTIL_HPP
