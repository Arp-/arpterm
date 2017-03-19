
#include "catch.hpp"
#include <iostream>
#include "arpterm/cursor.hpp"
#include "test/test_util.hpp"

namespace a = arpterm;

static constexpr auto make_test_string() {
	return "macska\r\nteszta";
}


TEST_CASE("cursor_up_test") {
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
	}

	SECTION("move_cur_up_2") {
		size_t strlen = str.size();
		c.move_cur_up(2);
		REQUIRE(c.index() == 6);
		REQUIRE(str.size() > strlen + 6);
		REQUIRE(test_util::str_n_cmp(str, "      ", 6));
	}

	SECTION("move_cur_up_10") {
		size_t strlen = str.size();
		c.move_cur_up(10);
		REQUIRE(c.index() == 6);
		REQUIRE(str.size() > strlen + 6);
		REQUIRE(test_util::str_n_cmp(str, "      ", 6));
	}

	SECTION("prev_line_term_10_times") {
		for (int i = 0; i < 10; i++) {
			c.prev_visual_line_term();
		}
	}
}


TEST_CASE("cursor_down_test") {
	std::string&& str = make_test_string();
	a::cursor<std::string> c(str);

	SECTION("next_line_term_10_times") {
		for (int i = 0; i < 10; i++) {
			c.next_visual_line_term();
		}
		printf("str: ");
		test_util::str_hex_print(str);
		REQUIRE(test_util::str_tail_n_cmp(str, "\r\r\r\r\r\r\r\r\r\r", 10));
	}

	SECTION("move_cur_down_1") {
		c.move_cur_down(1);
		test_util::str_hex_print(str);
		REQUIRE(test_util::str_tail_n_cmp(str, "\r      ", 7));
	}

}
