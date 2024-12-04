#define DAY 4
#define PART 1
#include "../util.h"


int check(char* buffer, size_t index, int line_len, int x, int y) {
	if (x == 0 && y == 0) {
		return 0;
	}
	int buffer_delta = y * (line_len + 1) + x;
	buffer += index;
	if (buffer[buffer_delta * 1] == 'M' && buffer[buffer_delta * 2] == 'A' && buffer[buffer_delta * 3] == 'S') {
		return 1;
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
		if (buffer[i] == 'X') {
			for (int x = -1; x <= 1; x ++) {
				for (int y = -1; y <= 1; y ++) {
					if (check(buffer, i, line_len, x, y)) {
						ret ++;
					}
				}
			}
		}
	}
	return ret;
}
