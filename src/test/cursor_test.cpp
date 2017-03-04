
#include "catch.hpp"
#include <iostream>
#include "arpterm/cursor.hpp"

namespace a = arpterm;

static constexpr auto make_test_string() {
	return "macska\r\nteszta";
}

static void str_hex_print(const std::string& str) {

	for (auto ch : str) {
		printf("%02X", ch & 0xff);
	}
	printf("\n");
}

TEST_CASE("cursor_test") {
	std::string&& str = make_test_string();
	a::cursor<std::string> c(str);


	SECTION("index_is_zero") { 
		c.index(0);
		REQUIRE(c.column_distance() == 1);
	}

	SECTION("index_is_at_in_between") {
		c.index(5);
		REQUIRE(c.column_distance() == 6);
	}

	SECTION("index_when_at_line_begin") {
		c.index(8);
		REQUIRE(c.column_distance() == 1);
	}

	SECTION("cursor_create") {
		REQUIRE( c.index() == str.length());
	}

	SECTION("move_cur_up_1") {
		c.move_cur_up(1);
		REQUIRE(c.index() == 6);
		// in this case it shouldnot modify the strings length
	}

	SECTION("move_cur_up_2") {
		size_t strlen = str.size();
		c.move_cur_up(2);
		REQUIRE(c.index() == 6);
		REQUIRE(str.size() > strlen + 6);

	}
}
