
#include "test/test_util.hpp"
#include <iostream>


void 
test_util::str_hex_print(const std::string& str) {

	for (auto ch : str) {
		printf("%02X", ch & 0xff);
	}
	printf("\n");
}

bool 
test_util::str_n_cmp(
		const std::string& str1, const std::string& str2, unsigned n) {
	for (unsigned i = 0; i < n; i++) {
		if (str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}
