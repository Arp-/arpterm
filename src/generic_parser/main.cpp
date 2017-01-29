

#include <iostream>
#include <utility>
#include <tuple>
#include <algorithm>

#include "generic_parser/util.hpp"

namespace gp = generic_parser;
namespace gpu = generic_parser::util;

#define STRFY(X) #X
#define APPEXPR(X) STRFY(X) << ": " << (X)

template <typename T>
static void print_vec(const std::vector<T>& vec) {
	for (const auto& elem : vec) {
		std::cout << elem << ", ";
	}
	std::cout << std::endl;
}
//-----------------------------------------------------------------------------//
static void test_start_match_end_match() {
	std::array<int, 4> arr1 = { 1,2,1,5 };
	std::vector<int> arr2 =   { 1,9,9,5,5,6,7,8,5,4,3 };

	std::cout << APPEXPR(gpu::start_match(arr1, arr2, 5)) << std::endl;

	std::array<int, 4> end =   {1,2,0,0};
	std::vector<int> end_vec = {1,2};

	std::cout << APPEXPR(gpu::end_match(end, end_vec)) << std::endl;

	std::cout << APPEXPR(gpu::param_arr_len(arr1)) << std::endl;

	std::vector<int> from = { 1,2,3,4,4,5};
	std::vector<int> to;

	std::copy(from.begin()+1, from.end()-1, std::back_inserter(to));
	for (auto val : to) {
		std::cout << val << " ";
	}
	std::cout << std::endl;
}
//-----------------------------------------------------------------------------//
static void test_parse_param_vec() {
	std::array<int, 4> arr_beg = { 1,2,0,0 };
	std::array<int,4> arr_end =  { 1,2,0,0 };

	std::vector<int> vec = { 1,2, 0x31,0x32,0x3B, 0x34, 0x3A, 1,2 };
	auto&& param_vec = gpu::get_param_vec(arr_beg, arr_end, vec);
	print_vec(param_vec);
	std::vector<int> ret_vec;
	int ec = gpu::parse_param_vec(param_vec, ret_vec);
	std::cout << APPEXPR(ec) << std::endl;
	print_vec(ret_vec);



}
//-----------------------------------------------------------------------------//
int main() {

	test_parse_param_vec();



	return 0;
}
