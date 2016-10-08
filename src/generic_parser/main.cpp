

#include <iostream>
#include <utility>
#include <tuple>

#include "generic_parser/command.hpp"

//using namespace xterm_parser;

namespace xp = generic_parser;
 
void update_int(int& b) {
	printf("called update int\n");
	b = 3;
}

void macska(int& b) {
	printf("macska\n");
}

int main() {

	int a = 6;
	xp::command_parser_t<int> c(a);
	c.add_command({'a','b','c'}, &update_int);
	c.add_command({'a','b'}, &macska);

	c.parse('a');
	c.parse('b');
	c.parse('c');

	printf("%d\n",a);


	return 0;
}
