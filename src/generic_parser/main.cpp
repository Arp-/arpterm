

#include <iostream>
#include <utility>
#include <tuple>

#include "generic_parser/util.hpp"

namespace gp = generic_parser;
namespace gpu = generic_parser::util;

#define STRFY(X) #X
#define APPEXPR(X) STRFY(X) << ": " << (X?"TRUE":"FALSE")

 
int main() {

	std::array<int, 4> arr1 = { 1,2,0,5 };
	std::vector<int> arr2 =   { 1,9,9,5,5,6,7,8,5,4,3 };

	std::cout << APPEXPR(gpu::start_match(arr1, arr2, 5)) << std::endl;

	std::array<int, 4> end =   {1,2,3,0};
	std::vector<int> end_vec = {1,2,3,4,5,6,7,8,1,2,1,2};

	std::cout << APPEXPR(gpu::end_match(end, end_vec)) << std::endl;


	return 0;
}
