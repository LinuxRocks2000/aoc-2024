#define DAY 4
#define PART 2
#include "../util.h"


int check(char* buffer, size_t index, int line_len) {
	int bdelta_downright = line_len + 2;
	int bdelta_downleft = line_len;
	buffer += index;
	if ((buffer[bdelta_downright] == 'M' && buffer[-bdelta_downright] == 'S') || (buffer[bdelta_downright] == 'S' && buffer[-bdelta_downright] == 'M')) {
		if ((buffer[bdelta_downleft] == 'M' && buffer[-bdelta_downleft] == 'S') || (buffer[bdelta_downleft] == 'S' && buffer[-bdelta_downleft] == 'M')) {
			return 1;
		}
	}
	return 0;
}


long aoc(FILE* f) {
	char* buffer = malloc(1024 *  64);
	size_t len = fread(buffer, 1, 1024 * 64, f);
	int line_len;
	for (line_len = 0; line_len < 10240; line_len ++) {
		if (buffer[line_len] == '\n') {
			break;
		}
	}
	long ret = 0;
	for (size_t i = 0; i < len; i ++) {
		if (buffer[i] == 'A') {
			if (check(buffer, i, line_len)) {
				ret ++;
			}
		}
	}
	return ret;
}
