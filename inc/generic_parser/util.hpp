
#ifndef GENERIC_PARSER_UTIL_HPP
#define GENERIC_PARSER_UTIL_HPP

#include <vector>
#include <array>

#ifdef DEBUG
#include <iostream>
#endif

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

		template <typename T>
		void print_vec(const std::vector<T>& vec) {
			std::cout << "vec: ";
			for (const auto& elem : vec) {
				std::cout << (char32_t)elem << " ";
			}
			std::cout << std::endl;
		}

		template <typename T, size_t size_V>
		bool start_match(const std::array<T, size_V>& arr,
				const std::vector<T>& vec, size_t depth) {
			for (int i = 0; i < depth && i < size_V && arr[i] != 0; i++) {
				if (arr[i] == vec[i]) {
					continue;
				}
				return false;
			}
			return true;
		}

		template <typename T, size_t size_V>
		bool end_match(const std::array<T, size_V>& arr,
				const std::vector<T>& vec) {

			int j = 0;
			for (int i = size_V-1; i >= 0; i--) {
				if (arr[i] == 0) { continue; }
				const auto vec_size = vec.size();
				if (arr[i] == vec[vec_size-1-(j)]) {
					j++;
					continue;
				}
				return false;
			}
			return true;
		}

		template <typename T, size_t size_V>
		inline int param_arr_size(const std::array<T, size_V>& arr) {
			int i = 0;
			for (i = 0; i < size_V && arr[i] != 0; i++);
			return i;
		}

	} // namespace util

} // namespace xterm_parser


#endif // GENERIC_PARSER_UTIL_HPP
