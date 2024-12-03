#define DAY 3
#define PART 2
#include "../util.h"
#define BUFFER_SIZE 1024 * 1024


long aoc(FILE* f) {
	char* bytes = malloc(BUFFER_SIZE);
	size_t len = fread(bytes, 1, BUFFER_SIZE, f);
	long ret = 0;
	int enabled = 1;
	for (size_t i = 0; i < len; i ++) {
		long a = 0;
		long b = 0;
		char end = 0;
		sscanf(bytes + i, "mul(%d,%d%c", &a, &b, &end);
		if (end == ')' && (a + b > 0)) {
			if (enabled) {
				long oldr = ret;
				ret += a * b;
				if (ret < oldr) {
					printf("DETECTED OVERFLOW\n");
				}
			}
		}
		if (strncmp(bytes + i, "don't()", 7) == 0) {
			enabled = 0;
		}
		if (strncmp(bytes + i, "do()", 4) == 0) {
			enabled = 1;
		}
	}
	return ret;
}
