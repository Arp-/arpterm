

#include "catch.hpp"
#include "test/test_util.hpp"


TEST_CASE("test_util_test") {
	SECTION("simple test") { 
		REQUIRE(test_util::str_tail_n_cmp("macska", "a", 1) == true);
	}

	SECTION("fal_test_1") { 
		REQUIRE(test_util::str_tail_n_cmp("macska", "a", 2) == false);
	}

	SECTION("fal_test_2") { 
		REQUIRE(test_util::str_tail_n_cmp("a", "macska", 2) == false);
	}

	SECTION("fal_test_3") {
		REQUIRE(test_util::str_tail_n_cmp("macska", "macska", 20) == false);
	}
}
