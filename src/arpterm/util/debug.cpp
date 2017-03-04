
#include <iomanip>
#include "arpterm/util/debug.hpp"

namespace au = arpterm::util;

void 
au::str_hex_print(const std::string& str) {

	for (auto ch : str) {
		printf("%02X", ch & 0xff);
	}
	printf("\n");
}
