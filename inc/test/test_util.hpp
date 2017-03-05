
#ifndef ARPTERM_TEST_UTIL_HPP
#define ARPTERM_TEST_UTIL_HPP

#include <iomanip>

namespace test_util {

	void str_hex_print(const std::string&);

	bool str_n_cmp(
			const std::string& str1, const std::string& str2, unsigned n);

}



#endif // ARPTERM_TEST_UTIL_HPP
