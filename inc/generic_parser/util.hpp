
#ifndef GENERIC_PARSER_UTIL_HPP
#define GENERIC_PARSER_UTIL_HPP

#include <vector>
#include <array>

#ifdef DEBUG
#include <iostream>
#endif

namespace generic_parser {

	namespace util {

		template <typename T, size_t size_V>
		inline size_t param_arr_len(const std::array<T, size_V>& arr) {
			size_t i = 0;
			for (i = 0; i < size_V && arr[i] != 0; i++);
			return i;
		}

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
			for (size_t i = 0; i < depth && i < size_V && arr[i] != 0; i++) {
				if (arr[i] == vec[i]) {
					continue;
				}
				return false;
			}
			return true;
		}

		template <typename T, size_t size_V>
		bool end_match(const std::array<T, size_V>& arr,
				const std::vector<T>& vec, size_t depth ) {

			int j = 0;
			size_t k = 0;
			for (int i = size_V-1; i >= 0 && k < depth; i--, k++) {
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
		bool strict_match(const std::array<T, size_V>& beg, const std::vector<T>& vec,
				const std::array<T, size_V>& end) {
			const size_t beg_size = param_arr_len(beg);
			if (!start_match(beg, vec, beg_size)) {
				return false;
			}
			const auto vec_size = vec.size();
			return end_match(end,vec,vec_size);
		}

		template <typename T, size_t size_V>
		bool possible_match(const std::array<T,size_V>& beg, const std::vector<T>& vec,
				const std::array<T, size_V> end) {
			const size_t vec_size = vec.size();
			if (!start_match(beg, vec, vec_size)) {
				return false;
			}
			const size_t beg_size = param_arr_len(beg);
			for (size_t i = beg_size -1; i < vec_size; i++) {
				// continues with parameters
				if (0x30 <= vec[i] && vec[i] <= 0x3B) { 
					continue;
				// continues with end_sequence
				} else if (end_match(end,vec, vec_size -1 -i)) {
					continue;
				}

			}
		}




		template <typename T, size_t size_V>
		std::vector<T> get_param_vec(const std::array<T, size_V>& begin,
				const std::array<T, size_V>& end, const std::vector<T>& buffer) {

			size_t beg_size = param_arr_len(begin);
			size_t end_size = param_arr_len(end);

			std::vector<T> to_vec;
			auto beg_it = buffer.begin();
			auto end_it = buffer.end();
			std::copy(beg_it + beg_size, end_it - end_size, std::back_inserter(to_vec));
			return to_vec;
		}


		template <typename param_T, typename ret_T>
		int parse_param_vec(
				const std::vector<param_T>& param_buf, std::vector<ret_T>& ret_vec) {

			constexpr param_T PARAM_SEP = 0x3B;
			constexpr param_T CUSTOM_SEP = 0x3A;
			ret_T elem = 0;
			bool got_elem = false;
			for (auto ch : param_buf) {
				if (ch == PARAM_SEP && got_elem == false) {
					ret_vec.push_back(-1);
				} else if (ch == PARAM_SEP) {
					ret_vec.push_back(elem);
					elem = 0;
					got_elem = false;
				} else if (0x30 <= ch && ch <= 0x39) {
					elem *= 10;
					elem += (ch & 0x0f);
					got_elem = true;
				} else if (CUSTOM_SEP == ch) {
					std::cerr << "GOT_CUSTOM_SEPARATOR" << std::endl;
				} else {
					return -2; // INVALID CHARACTER INSIDE PARAM_SEQ
				}
			}
			// if no separator was found then maybe we red only one elment
			if (got_elem) {
				ret_vec.push_back(elem);
			}
			return 0; // PARSE_WAS OKAY
		}


	} // namespace util

} // namespace xterm_parser


#endif // GENERIC_PARSER_UTIL_HPP
