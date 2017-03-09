
#include "test/test_util.hpp"
#include <iostream>


void 
test_util::str_hex_print(const std::string& str) {

	for (auto ch : str) {
		printf("%02X", ch & 0xff);
	}
	printf("\n");
}
//-----------------------------------------------------------------------------//
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
//-----------------------------------------------------------------------------//
bool
test_util::str_tail_n_cmp(
		const std::string& str1, const std::string& str2, unsigned n) {

	if (str1.size() == 0 || str2.size() == 0) { return false; }
	if (n == 0) { return true; }


	int j = str1.size()-1;
	int k = str2.size()-1;
	for (int i = 0; i < n; i++, j--,k--) {
		if (j < 0 || k < 0) { return false; }
		if (str1[j] != str2[k]) { return false; }
	}

	return true;
}

