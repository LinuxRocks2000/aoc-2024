#define DAY 3
#define PART 1
#include "../util.h"
#define BUFFER_SIZE 1024 * 1024


long aoc(FILE* f) {
	char* bytes = malloc(BUFFER_SIZE);
	size_t len = fread(bytes, 1, BUFFER_SIZE, f);
	long ret = 0;
	for (size_t i = 0; i < len; i ++) {
		long a = 0;
		long b = 0;
		char end = 0;
		sscanf(bytes + i, "mul(%d,%d%c", &a, &b, &end);
		if (end == ')' && (a + b > 0)) {
			long oldr = ret;
			ret += a * b;
			if (ret < oldr) {
				printf("DETECTED OVERFLOW\n");
			}
		}
	}
	return ret;
}
