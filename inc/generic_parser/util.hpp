
#ifndef GENERIC_PARSER_UTIL_HPP
#define GENERIC_PARSER_UTIL_HPP

namespace generic_parser {

	namespace util {

		template <typename T> 
		bool vector_compare(
				const std::vector<T>& lhs, const std::vector<T>& rhs, size_t depth) {

			for (size_t i = 0; i < depth; i++) {
				if (lhs[i] != rhs[i]) {
					return false;
				}
			}
			return true;
		}

	} // namespace util

} // namespace xterm_parser


#endif // GENERIC_PARSER_UTIL_HPP
