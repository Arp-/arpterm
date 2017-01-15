// Simple program that reads from stdin, and write the hexdump to
// stdout, runs until interrupted

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define FALSE (0)
#define TRUE (!FALSE)

#define LINE_BREAK 6

static void exit_handler(int param) {
	fprintf(stderr, "Caught interrupt exiting hexdump\n");
	exit(1);
}

static void to_hex_helper(char num, char* hex) {
	if ( 0 <= num && 9 >= num) {
		*hex = num + '0';
	} else if (10 <= num && 15 >= num) {
		*hex = num - 10 + 'a';
	}
}


static void to_hex(char c, char* hex) {
	char u = (c & 0xf0) >> 4;
	char l = (c & 0x0f);
	to_hex_helper(u, &hex[0]);
	to_hex_helper(l, &hex[1]);
}

int main(int argc, char* argv[]) {

	signal(SIGINT, &exit_handler);

	int ln = 0;

	while (TRUE) {
		char c = fgetc(stdin);
		if (c == EOF) {
			break;
		}
		char hex[2];
		to_hex(c, hex);
		fputc(hex[0], stdout);
		fputc(hex[1], stdout);
		fputc(' ', stdout);
		if (!(++ln % LINE_BREAK)) {
			fputc('\n', stdout);
			ln = 0;
		}
	}


	return 0;
}
